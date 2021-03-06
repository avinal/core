/**************************************************************************************
Copyright 2015 Applied Research Associates, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the License
at:
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
**************************************************************************************/

#include "HowTo-BurnWoundPainStimulus.h"
#include <iostream>

// Include the various types you will be using in your code
#include <biogears/cdm/compartment/SECompartmentManager.h>
#include <biogears/cdm/engine/PhysiologyEngineTrack.h>
#include <biogears/cdm/patient/actions/SEBurnWound.h>
#include <biogears/cdm/patient/actions/SESubstanceBolus.h>
#include <biogears/cdm/patient/actions/SESubstanceCompoundInfusion.h>
#include <biogears/cdm/patient/actions/SESubstanceInfusion.h>
#include <biogears/cdm/properties/SEScalarTypes.h>
#include <biogears/cdm/substance/SESubstanceManager.h>
#include <biogears/cdm/system/physiology/SEBloodChemistrySystem.h>
#include <biogears/cdm/system/physiology/SECardiovascularSystem.h>
#include <biogears/cdm/system/physiology/SERenalSystem.h>
#include <biogears/cdm/system/physiology/SERespiratorySystem.h>
#include <biogears/cdm/utils/SEEventHandler.h>
#include <biogears/cdm/patient/SEPatient.h>
#include <biogears/engine/BioGearsPhysiologyEngine.h>

using namespace biogears;
//--------------------------------------------------------------------------------------------------
/// \brief
/// Usage for applying a burn wound to a patient
///
/// \details
/// Refer to the SEBurnWoundData class
///
//--------------------------------------------------------------------------------------------------
void HowToBurnWoundPainStimulus()
{
  double burnTBSA = 30;
  std::cout << "Provide a burn size (total body surface area, in %), followed by ENTER" << std::endl;
  std::cin >> burnTBSA;
  if (burnTBSA < 0.0) {
    std::cout << "Cannot enter negative burn size, defaulting to 20% TBSA burn" << std::endl;
    burnTBSA = 20.0;
  }
  if (burnTBSA > 100.0) {
    std::cout << "Cannot enter burn size > 100%, defaulting to 20% TBSA burn" << std::endl;
    burnTBSA = 20.0;
  }
  if (burnTBSA > 50.0) {
    std::cout << "Warn: Burns of this size typically require automatic intubation, treatment results may not be valid" << std::endl;
  }

  BurnThread burn("./HowToBurnWound.log", burnTBSA);

  int action;
  bool active = true;
  double bolusDose;
  double ringersRate;
  double ringersVolume;

  do {
    burn.GetLogger()->Info("Enter integer for action to perform:  \n\t[1] Status \n\t[2] Set Ringers Lactate Infusion Rate \n\t[3] Adminster ketamine bolus \n\t[4] Quit \n");
    std::cin >> action;
    switch (action) {
    case 1:
      burn.Status();
      break;
    case 2:
      burn.GetLogger()->Info("Enter an IV bag volume in mL, followed by ENTER : ");
      std::cin >> ringersVolume;
      burn.GetLogger()->Info("Enter an infusion rate in mL/hr, followed by ENTER : ");
      std::cin >> ringersRate;
      burn.SetRingersInfusionRate(ringersVolume, ringersRate);
      break;
    case 3:
      burn.GetLogger()->Info("Enter a ketamine bolus dose in mg, followed by ENTER : ");
      std::cin >> bolusDose;
      burn.AdministerKetamine(bolusDose);
      break;
    case 4:
      active = false;
      break;
    default:
      burn.GetLogger()->Info("Not a valid option \n");
    }
  } while (active);

}

BurnThread::BurnThread(const std::string logFile, double tbsa)
  : m_burnThread()
{
  //Create the engine and load patient state
  m_bg = CreateBioGearsEngine(logFile);
  m_bg->GetLogger()->Info(std::stringstream() << "Initiating " << tbsa << "% TBSA burn wound");
  if (!m_bg->LoadState("./states/StandardMale@0s.xml")) {
    m_bg->GetLogger()->Error("Could not load state, check the error");
    return;
  }
  //Create CSV results file and set up data that we want to be tracked (tracking done in AdvanceModelTime)
  m_bg->GetEngineTrack()->GetDataRequestManager().SetResultsFilename("HowToBurnWound.csv");
  m_bg->GetEngineTrack()->GetDataRequestManager().CreatePhysiologyDataRequest().Set("HeartRate", "1/min");
  m_bg->GetEngineTrack()->GetDataRequestManager().CreatePhysiologyDataRequest().Set("ArterialBloodPH", "unitless");
  m_bg->GetEngineTrack()->GetDataRequestManager().CreatePhysiologyDataRequest().Set("CardiacOutput", "mL/min");
  m_bg->GetEngineTrack()->GetDataRequestManager().CreatePhysiologyDataRequest().Set("InflammatoryResponse-TissueIntegrity");
  m_bg->GetEngineTrack()->GetDataRequestManager().CreatePhysiologyDataRequest().Set("MeanArterialPressure", "mmHg");
  m_bg->GetEngineTrack()->GetDataRequestManager().CreatePhysiologyDataRequest().Set("SystolicArterialPressure", "mmHg");
  m_bg->GetEngineTrack()->GetDataRequestManager().CreatePhysiologyDataRequest().Set("DiastolicArterialPressure", "mmHg");
  m_bg->GetEngineTrack()->GetDataRequestManager().CreatePhysiologyDataRequest().Set("RespirationRate", "1/min");
  m_bg->GetEngineTrack()->GetDataRequestManager().CreatePhysiologyDataRequest().Set("TidalVolume", "mL");
  m_bg->GetEngineTrack()->GetDataRequestManager().CreatePhysiologyDataRequest().Set("SystemicVascularResistance", "mmHg s/mL");
  m_bg->GetEngineTrack()->GetDataRequestManager().CreatePhysiologyDataRequest().Set("BloodVolume", "mL");
  m_bg->GetEngineTrack()->GetDataRequestManager().CreatePhysiologyDataRequest().Set("MeanUrineOutput", "mL/hr");
  m_bg->GetEngineTrack()->GetDataTrack().Probe("totalFluid_mL", m_TotalVolume_mL);
  m_bg->GetEngineTrack()->GetDataTrack().Probe("bagVolume_mL", m_ivBagVolume_mL);

  //Load substances and compounds
  SESubstanceCompound* ringers = m_bg->GetSubstanceManager().GetCompound("RingersLactate");
  SESubstanceCompound* albumex = m_bg->GetSubstanceManager().GetCompound("Albuminex_4PCT");
  SESubstance* ketamine = m_bg->GetSubstanceManager().GetSubstance("Ketamine");
  //Create infusion and bolus actions
  m_ringers = new SESubstanceCompoundInfusion(*ringers);
  m_albumex = new SESubstanceCompoundInfusion(*albumex);
  m_ivBagVolume_mL = 0.0;
  m_ketamineBolus = new SESubstanceBolus(*ketamine);

  m_burnWound = new SEBurnWound();
  m_burnWound->GetTotalBodySurfaceArea().SetValue(tbsa / 100.0);
  m_bg->ProcessAction(*m_burnWound);

  m_runThread = true;
 // m_burnThread = std::thread(&BurnThread::AdvanceTime, this);
}

BurnThread::~BurnThread()
{
  m_runThread = false;
  std::this_thread::sleep_for(std::chrono::seconds(2));
  SAFE_DELETE(m_ketamineBolus);
  SAFE_DELETE(m_ringers);
}

void BurnThread::AdministerKetamine(double& bolus)
{
  m_ketamineBolus->SetAdminRoute(CDM::enumBolusAdministration::Intravenous);
  m_ketamineBolus->GetConcentration().SetValue(1.0, MassPerVolumeUnit::mg_Per_mL);
  m_ketamineBolus->GetDose().SetValue(bolus, VolumeUnit::mL);
  m_mutex.lock();
  m_bg->ProcessAction(*m_ketamineBolus);
  m_mutex.unlock();
}

void BurnThread::SetRingersInfusionRate(double& volume, double& rate)
{
  m_ringers->GetBagVolume().SetValue(volume, VolumeUnit::mL);
  m_ringers->GetRate().SetValue(rate, VolumePerTimeUnit::mL_Per_hr);
  m_ivBagVolume_mL = volume;
  m_mutex.lock();
  m_bg->ProcessAction(*m_ringers);
  m_mutex.unlock();
}


void BurnThread::SetAlbuminInfusionRate(double& volume, double& rate)
{
  m_albumex->GetBagVolume().SetValue(volume, VolumeUnit::mL);
  m_albumex->GetRate().SetValue(rate, VolumePerTimeUnit::mL_Per_hr);
  m_ivBagVolume_mL = volume;
  m_mutex.lock();
  m_bg->ProcessAction(*m_albumex);
  m_mutex.unlock();
}

void BurnThread::AdvanceTime()
{
  while (m_runThread) {
    m_mutex.lock();
    m_bg->AdvanceModelTime(1.0, TimeUnit::s);
    if (m_ringers->HasBagVolume() && m_ringers->HasRate()) {
      m_ivBagVolume_mL += (-m_ringers->GetRate().GetValue(VolumePerTimeUnit::mL_Per_s));
      if (m_ivBagVolume_mL < 0.0) {
        m_bg->GetLogger()->Info("Ringers Lactate IV bag is empty \n");
        m_ivBagVolume_mL = 0.0;
        m_ringers->Clear();
      }
    }
    m_bg->GetEngineTrack()->TrackData(m_bg->GetSimulationTime(TimeUnit::s));
    m_mutex.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(25));
  }
}

void BurnThread::AdvanceTimeFluids()
{
    m_mutex.lock();
    m_bg->AdvanceModelTime(1.0, TimeUnit::s);
    if (m_ringers->HasBagVolume() && m_ringers->HasRate()) {
      m_TotalVolume_mL += (m_ringers->GetRate().GetValue(VolumePerTimeUnit::mL_Per_s));
      m_ivBagVolume_mL += (-m_ringers->GetRate().GetValue(VolumePerTimeUnit::mL_Per_s));
      if (m_ivBagVolume_mL < 0.0) {
        m_bg->GetLogger()->Info("Ringers Lactate IV bag is empty \n");
      }
    }
    m_bg->GetEngineTrack()->GetDataTrack().Probe("totalFluid_mL", m_TotalVolume_mL);
    m_bg->GetEngineTrack()->GetDataTrack().Probe("bagVolume_mL", m_ivBagVolume_mL);
    m_bg->GetEngineTrack()->TrackData(m_bg->GetSimulationTime(TimeUnit::s));
    m_mutex.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(25));
}

void BurnThread::AdvanceTimeFluidsAlbumin()
{
  m_mutex.lock();
  m_bg->AdvanceModelTime(1.0, TimeUnit::s);
  if (m_albumex->HasBagVolume() && m_albumex->HasRate()) {
    m_TotalVolume_mL += (m_albumex->GetRate().GetValue(VolumePerTimeUnit::mL_Per_s));
    m_ivBagVolume_mL += (-m_albumex->GetRate().GetValue(VolumePerTimeUnit::mL_Per_s));
    if (m_ivBagVolume_mL < 0.0) {
      m_bg->GetLogger()->Info("Albumex_4PCT IV bag is empty \n");
    }
  }
  m_bg->GetEngineTrack()->GetDataTrack().Probe("totalFluid_mL", m_TotalVolume_mL);
  m_bg->GetEngineTrack()->GetDataTrack().Probe("bagVolume_mL", m_ivBagVolume_mL);
  m_bg->GetEngineTrack()->TrackData(m_bg->GetSimulationTime(TimeUnit::s));
  m_mutex.unlock();
  std::this_thread::sleep_for(std::chrono::milliseconds(25));
}

void BurnThread::Status()
{
  m_mutex.lock();
  m_bg->GetLogger()->Info(std::stringstream() << "The patient suffered a burn wound " << m_bg->GetSimulationTime(TimeUnit::min) << " min ago");
  m_bg->GetLogger()->Info(std::stringstream() << "Tidal Volume : " << m_bg->GetRespiratorySystem()->GetTidalVolume(VolumeUnit::mL) << " " << VolumeUnit::mL);
  m_bg->GetLogger()->Info(std::stringstream() << "Systolic Pressure : " << m_bg->GetCardiovascularSystem()->GetSystolicArterialPressure(PressureUnit::mmHg) << " " << PressureUnit::mmHg);
  m_bg->GetLogger()->Info(std::stringstream() << "Diastolic Pressure : " << m_bg->GetCardiovascularSystem()->GetDiastolicArterialPressure(PressureUnit::mmHg) << " " << PressureUnit::mmHg);
  m_bg->GetLogger()->Info(std::stringstream() << "Heart Rate : " << m_bg->GetCardiovascularSystem()->GetHeartRate(FrequencyUnit::Per_min) << " bpm");
  m_bg->GetLogger()->Info(std::stringstream() << "Respiration Rate : " << m_bg->GetRespiratorySystem()->GetRespirationRate(FrequencyUnit::Per_min) << " bpm");
  m_bg->GetLogger()->Info(std::stringstream() << "Oxygen Saturation : " << m_bg->GetBloodChemistrySystem()->GetOxygenSaturation());
  m_bg->GetLogger()->Info(std::stringstream() << "Blood Volume: " << m_bg->GetCardiovascularSystem()->GetBloodVolume(VolumeUnit::mL) << " " << VolumeUnit::mL);
  m_bg->GetLogger()->Info(std::stringstream() << "Systemic Vascular Resistance : " << m_bg->GetCardiovascularSystem()->GetSystemicVascularResistance(FlowResistanceUnit::mmHg_s_Per_mL) << " " << FlowResistanceUnit::mmHg_s_Per_mL);
  m_bg->GetLogger()->Info(std::stringstream() << "Mean Urine Output : " << m_bg->GetRenalSystem()->GetMeanUrineOutput(VolumePerTimeUnit::mL_Per_hr) << " " << VolumePerTimeUnit::mL_Per_hr);
  if (m_ringers->HasBagVolume()) {
    m_bg->GetLogger()->Info(std::stringstream() << "Remaining LR Volume : " << m_ivBagVolume_mL << VolumeUnit::mL);
  }

  std::cout << std::endl;
  m_mutex.unlock();
}

//routine to administer fluids with a goal directed therapy for urine ourput
void BurnThread::FluidLoading()
{

  //fluidType fluid = ringers;
  //auto fluid = albumin;   //set the type of fluid here
  auto fluid = ringers;   //set the type of fluid here
  double tbsa = 30.0;
  double urineProduction = 0.0;
  int checkTime_s = 3600;
  double ringersVolume_mL = 500.0;
  double volume = 0.0;
  double titrate = 0.25;   //how much to adjust each hour 
  m_runThread = true;

  //compute urine production and max fluid requirements, per parkland formula
  const SEPatient& patient = m_bg->GetPatient();
  double weight_kg = patient.GetWeight(MassUnit::kg);
  double targetLowUrineProduction_mL_Per_Hr = 0.5 * weight_kg;
  double targetHighUrineProduction_mL_Per_Hr = 0.75 * weight_kg;   //average of around 50ml/hr
  double DayLimit_mL = 4.0 * weight_kg * tbsa;
  double initialInfustion_mL_Per_hr = (DayLimit_mL / 0.5 ) / 8.0; //half of the fluid should be loaded in the first 8 hours;
  double DayLimit_Hr = DayLimit_mL/24.0;
  double temp = 0.0;

  //set fluid infusion rate, using ringers lactate: 
  if(fluid == ringers) {
    SetRingersInfusionRate(ringersVolume_mL, initialInfustion_mL_Per_hr);
  }
  //same volume and rate
  if (fluid == albumin) {
    SetAlbuminInfusionRate(ringersVolume_mL, initialInfustion_mL_Per_hr);
  }

  while(m_runThread) {
    //check urine every hour, reset the volume while we are at it 
    if(((int)m_bg->GetSimulationTime(TimeUnit::s) + 1) % checkTime_s == 0) {
      Status();
      m_bg->GetLogger()->Info(std::stringstream() << "Checking urine production" << m_bg->GetRenalSystem()->GetMeanUrineOutput(VolumePerTimeUnit::mL_Per_hr));
      urineProduction = m_bg->GetRenalSystem()->GetMeanUrineOutput(VolumePerTimeUnit::mL_Per_hr);
      if(fluid == ringers) {
        if (urineProduction < targetLowUrineProduction_mL_Per_Hr) {
          m_bg->GetLogger()->Info(std::stringstream() << "Urine production is too low at " << urineProduction);
          m_ringers->GetRate().SetValue((m_ringers->GetRate().GetValue(VolumePerTimeUnit::mL_Per_hr))*(1 + titrate), VolumePerTimeUnit::mL_Per_hr);
          m_bg->ProcessAction(*m_ringers);
        }
        if ((m_bg->GetRenalSystem()->GetMeanUrineOutput(VolumePerTimeUnit::mL_Per_hr) > targetHighUrineProduction_mL_Per_Hr)) {
          m_bg->GetLogger()->Info(std::stringstream() << "Urine production is too high at" << m_bg->GetRenalSystem()->GetMeanUrineOutput(VolumePerTimeUnit::mL_Per_hr));
          m_ringers->GetRate().SetValue((m_ringers->GetRate().GetValue(VolumePerTimeUnit::mL_Per_hr))*(1 - titrate), VolumePerTimeUnit::mL_Per_hr);
          m_bg->ProcessAction(*m_ringers);
        }
      }
      if (fluid == albumin) {
        if (urineProduction < targetLowUrineProduction_mL_Per_Hr) {
          m_bg->GetLogger()->Info(std::stringstream() << "Urine production is too low at " << urineProduction);
          m_albumex->GetRate().SetValue((m_albumex->GetRate().GetValue(VolumePerTimeUnit::mL_Per_hr))*(1 + titrate), VolumePerTimeUnit::mL_Per_hr);
          m_bg->ProcessAction(*m_albumex);
        }
        if ((m_bg->GetRenalSystem()->GetMeanUrineOutput(VolumePerTimeUnit::mL_Per_hr) > targetHighUrineProduction_mL_Per_Hr)) {
          m_bg->GetLogger()->Info(std::stringstream() << "Urine production is too high at" << m_bg->GetRenalSystem()->GetMeanUrineOutput(VolumePerTimeUnit::mL_Per_hr));
          m_albumex->GetRate().SetValue((m_albumex->GetRate().GetValue(VolumePerTimeUnit::mL_Per_hr))*(1 - titrate), VolumePerTimeUnit::mL_Per_hr);
          m_bg->ProcessAction(*m_albumex);
        }
      }

    }
    // make sure that the bag is full
    if(fluid == ringers) {
      if (m_ivBagVolume_mL < 1.0) {
        m_ringers->GetBagVolume().SetValue(ringersVolume_mL, VolumeUnit::mL);
        m_bg->GetLogger()->Info("ringers IV bag is low, refilling bag \n");
        m_bg->ProcessAction(*m_ringers);
        m_ivBagVolume_mL = ringersVolume_mL;   //tracking purposes
      }
    }

    if (fluid == albumin) {
      if (m_ivBagVolume_mL < 1.0) {
        m_albumex->GetBagVolume().SetValue(ringersVolume_mL, VolumeUnit::mL);
        m_bg->GetLogger()->Info("albumin IV bag is low, refilling bag \n");
        m_bg->ProcessAction(*m_albumex);
        m_ivBagVolume_mL = ringersVolume_mL;   //tracking purposes
      }
    }
   
    //exit checks: 
    if(m_TotalVolume_mL > DayLimit_mL) {
      m_bg->GetLogger()->Info(std::stringstream() << "We have given too many fluids, per guidelines: " << m_TotalVolume_mL);
      m_runThread = false;
    }

    if (m_bg->GetSimulationTime(TimeUnit::hr) > 48.0) {
      m_bg->GetLogger()->Info(std::stringstream() << "This simulation has gone on too long" );
      m_runThread = false;
    }

    //advance time
    if(fluid == ringers) {
      AdvanceTimeFluids();
    }

    if (fluid == albumin) {
      AdvanceTimeFluidsAlbumin();
    }



  }
}