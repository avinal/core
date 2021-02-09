#include <pybind11/pybind11.h>

#include <string>

#include <biogears/cdm/patient/actions/SEOverride.h>
#include <biogears/cdm/properties/SEScalarTypes.h>

namespace py = pybind11;

void define_pybSEOverride(py::module_ &m)
{

  py::class_<biogears::SEOverride, biogears::SEPatientAction>(m, "SEOverride")
    .def(py::init<>())
    .def("TypeTag", &biogears::SEOverride::TypeTag)
    .def("classname", py::overload_cast<>(&biogears::SEOverride::classname, py::const_))
    .def("Clear", py::overload_cast<>(&biogears::SEOverride::Clear))
    .def("IsValid", py::overload_cast<>(&biogears::SEOverride::IsValid, py::const_))
    .def("IsActive", py::overload_cast<>(&biogears::SEOverride::IsActive, py::const_))
    .def("Load", &biogears::SEOverride::Load)
    .def("Unload", py::overload_cast<>(&biogears::SEOverride::Unload, py::const_))
    .def("GetOverrideState", &biogears::SEOverride::GetOverrideState)
    .def("SetOverrideState", &biogears::SEOverride::SetOverrideState)
    .def("HasOverrideState", &biogears::SEOverride::HasOverrideState)
    .def("InvalidateOverrideState", &biogears::SEOverride::InvalidateOverrideState)
    .def("GetOverrideConformance", &biogears::SEOverride::GetOverrideConformance)
    .def("SetOverrideConformance", &biogears::SEOverride::SetOverrideConformance)
    .def("HasOverrideConformance", &biogears::SEOverride::HasOverrideConformance)
    .def("InvalidateOverrideConformance", &biogears::SEOverride::InvalidateOverrideConformance)
    .def("HasArterialPHOverride", &biogears::SEOverride::HasArterialPHOverride)
    .def("GetArterialPHOverride", py::overload_cast<>(&biogears::SEOverride::GetArterialPHOverride))
    .def("GetArterialPHOverride", py::overload_cast<>(&biogears::SEOverride::GetArterialPHOverride, py::const_))
    .def("HasVenousPHOverride", &biogears::SEOverride::HasVenousPHOverride)
    .def("GetVenousPHOverride", py::overload_cast<>(&biogears::SEOverride::GetVenousPHOverride))
    .def("GetVenousPHOverride", py::overload_cast<>(&biogears::SEOverride::GetVenousPHOverride, py::const_))
    .def("HasCO2SaturationOverride", &biogears::SEOverride::HasCO2SaturationOverride)
    .def("GetCO2SaturationOverride", py::overload_cast<>(&biogears::SEOverride::GetCO2SaturationOverride))
    .def("GetCO2SaturationOverride", py::overload_cast<>(&biogears::SEOverride::GetCO2SaturationOverride, py::const_))
    .def("HasCOSaturationOverride", &biogears::SEOverride::HasCOSaturationOverride)
    .def("GetCOSaturationOverride", py::overload_cast<>(&biogears::SEOverride::GetCOSaturationOverride))
    .def("GetCOSaturationOverride", py::overload_cast<>(&biogears::SEOverride::GetCOSaturationOverride, py::const_))
    .def("HasO2SaturationOverride", &biogears::SEOverride::HasO2SaturationOverride)
    .def("GetO2SaturationOverride", py::overload_cast<>(&biogears::SEOverride::GetO2SaturationOverride))
    .def("GetO2SaturationOverride", py::overload_cast<>(&biogears::SEOverride::GetO2SaturationOverride, py::const_))
    .def("HasPhosphateOverride", &biogears::SEOverride::HasPhosphateOverride)
    .def("GetPhosphateOverride", py::overload_cast<>(&biogears::SEOverride::GetPhosphateOverride))
    .def("GetPhosphateOverride", py::overload_cast<const biogears::AmountPerVolumeUnit&>(&biogears::SEOverride::GetPhosphateOverride, py::const_))
    .def("HasWBCCountOverride", &biogears::SEOverride::HasWBCCountOverride)
    .def("GetWBCCountOverride", py::overload_cast<>(&biogears::SEOverride::GetWBCCountOverride))
    .def("GetWBCCountOverride", py::overload_cast<const biogears::AmountPerVolumeUnit&>(&biogears::SEOverride::GetWBCCountOverride, py::const_))
    .def("HasTotalBilirubinOverride", &biogears::SEOverride::HasTotalBilirubinOverride)
    .def("GetTotalBilirubinOverride", py::overload_cast<>(&biogears::SEOverride::GetTotalBilirubinOverride))
    .def("GetTotalBilirubinOverride", py::overload_cast<const biogears::MassPerVolumeUnit&>(&biogears::SEOverride::GetTotalBilirubinOverride, py::const_))
    .def("HasCalciumConcentrationOverride", &biogears::SEOverride::HasCalciumConcentrationOverride)
    .def("GetCalciumConcentrationOverride", py::overload_cast<>(&biogears::SEOverride::GetCalciumConcentrationOverride))
    .def("GetCalciumConcentrationOverride", py::overload_cast<const biogears::MassPerVolumeUnit&>(&biogears::SEOverride::GetCalciumConcentrationOverride, py::const_))
    .def("HasGlucoseConcentrationOverride", &biogears::SEOverride::HasGlucoseConcentrationOverride)
    .def("GetGlucoseConcentrationOverride", py::overload_cast<>(&biogears::SEOverride::GetGlucoseConcentrationOverride))
    .def("GetGlucoseConcentrationOverride", py::overload_cast<const biogears::MassPerVolumeUnit&>(&biogears::SEOverride::GetGlucoseConcentrationOverride, py::const_))
    .def("HasLactateConcentrationOverride", &biogears::SEOverride::HasLactateConcentrationOverride)
    .def("GetLactateConcentrationOverride", py::overload_cast<>(&biogears::SEOverride::GetLactateConcentrationOverride))
    .def("GetLactateConcentrationOverride", py::overload_cast<const biogears::MassPerVolumeUnit&>(&biogears::SEOverride::GetLactateConcentrationOverride, py::const_))
    .def("HasPotassiumConcentrationOverride", &biogears::SEOverride::HasPotassiumConcentrationOverride)
    .def("GetPotassiumConcentrationOverride", py::overload_cast<>(&biogears::SEOverride::GetPotassiumConcentrationOverride))
    .def("GetPotassiumConcentrationOverride", py::overload_cast<const biogears::MassPerVolumeUnit&>(&biogears::SEOverride::GetPotassiumConcentrationOverride, py::const_))
    .def("HasSodiumConcentrationOverride", &biogears::SEOverride::HasSodiumConcentrationOverride)
    .def("GetSodiumConcentrationOverride", py::overload_cast<>(&biogears::SEOverride::GetSodiumConcentrationOverride))
    .def("GetSodiumConcentrationOverride", py::overload_cast<const biogears::MassPerVolumeUnit&>(&biogears::SEOverride::GetSodiumConcentrationOverride, py::const_))
    .def("HasBloodChemistryOverride", &biogears::SEOverride::HasBloodChemistryOverride)
    .def("HasBloodVolumeOverride", &biogears::SEOverride::HasBloodVolumeOverride)
    .def("GetBloodVolumeOverride", py::overload_cast<>(&biogears::SEOverride::GetBloodVolumeOverride))
    .def("GetBloodVolumeOverride", py::overload_cast<const biogears::VolumeUnit&>(&biogears::SEOverride::GetBloodVolumeOverride, py::const_))
    .def("HasCardiacOutputOverride", &biogears::SEOverride::HasCardiacOutputOverride)
    .def("GetCardiacOutputOverride", py::overload_cast<>(&biogears::SEOverride::GetCardiacOutputOverride))
    .def("GetCardiacOutputOverride", py::overload_cast<const biogears::VolumePerTimeUnit&>(&biogears::SEOverride::GetCardiacOutputOverride, py::const_))
    .def("HasDiastolicArterialPressureOverride", &biogears::SEOverride::HasDiastolicArterialPressureOverride)
    .def("GetDiastolicArterialPressureOverride", py::overload_cast<>(&biogears::SEOverride::GetDiastolicArterialPressureOverride))
    .def("GetDiastolicArterialPressureOverride", py::overload_cast<const biogears::PressureUnit&>(&biogears::SEOverride::GetDiastolicArterialPressureOverride, py::const_))
    .def("HasMAPOverride", &biogears::SEOverride::HasMAPOverride)
    .def("GetMAPOverride", py::overload_cast<>(&biogears::SEOverride::GetMAPOverride))
    .def("GetMAPOverride", py::overload_cast<const biogears::PressureUnit&>(&biogears::SEOverride::GetMAPOverride, py::const_))
    .def("HasHeartRateOverride", &biogears::SEOverride::HasHeartRateOverride)
    .def("GetHeartRateOverride", py::overload_cast<>(&biogears::SEOverride::GetHeartRateOverride))
    .def("GetHeartRateOverride", py::overload_cast<const biogears::FrequencyUnit&>(&biogears::SEOverride::GetHeartRateOverride, py::const_))
    .def("HasHeartStrokeVolumeOverride", &biogears::SEOverride::HasHeartStrokeVolumeOverride)
    .def("GetHeartStrokeVolumeOverride", py::overload_cast<>(&biogears::SEOverride::GetHeartStrokeVolumeOverride))
    .def("GetHeartStrokeVolumeOverride", py::overload_cast<const biogears::VolumeUnit&>(&biogears::SEOverride::GetHeartStrokeVolumeOverride, py::const_))
    .def("HasSystolicArterialPressureOverride", &biogears::SEOverride::HasSystolicArterialPressureOverride)
    .def("GetSystolicArterialPressureOverride", py::overload_cast<>(&biogears::SEOverride::GetSystolicArterialPressureOverride))
    .def("GetSystolicArterialPressureOverride", py::overload_cast<const biogears::PressureUnit&>(&biogears::SEOverride::GetSystolicArterialPressureOverride, py::const_))
    .def("HasCardiovascularOverride", &biogears::SEOverride::HasCardiovascularOverride)
    .def("HasInsulinSynthesisRateOverride", &biogears::SEOverride::HasInsulinSynthesisRateOverride)
    .def("GetInsulinSynthesisRateOverride", py::overload_cast<>(&biogears::SEOverride::GetInsulinSynthesisRateOverride))
    .def("GetInsulinSynthesisRateOverride", py::overload_cast<const biogears::AmountPerTimeUnit&>(&biogears::SEOverride::GetInsulinSynthesisRateOverride, py::const_))
    .def("HasGlucagonSynthesisRateOverride", &biogears::SEOverride::HasGlucagonSynthesisRateOverride)
    .def("GetGlucagonSynthesisRateOverride", py::overload_cast<>(&biogears::SEOverride::GetGlucagonSynthesisRateOverride))
    .def("GetGlucagonSynthesisRateOverride", py::overload_cast<const biogears::AmountPerTimeUnit&>(&biogears::SEOverride::GetGlucagonSynthesisRateOverride, py::const_))
    .def("HasEndocrineOverride", &biogears::SEOverride::HasEndocrineOverride)
    .def("HasAchievedExerciseLevelOverride", &biogears::SEOverride::HasAchievedExerciseLevelOverride)
    .def("GetAchievedExerciseLevelOverride", py::overload_cast<>(&biogears::SEOverride::GetAchievedExerciseLevelOverride))
    .def("GetAchievedExerciseLevelOverride", py::overload_cast<>(&biogears::SEOverride::GetAchievedExerciseLevelOverride, py::const_))
    .def("HasCoreTemperatureOverride", &biogears::SEOverride::HasCoreTemperatureOverride)
    .def("GetCoreTemperatureOverride", py::overload_cast<>(&biogears::SEOverride::GetCoreTemperatureOverride))
    .def("GetCoreTemperatureOverride", py::overload_cast<const biogears::TemperatureUnit&>(&biogears::SEOverride::GetCoreTemperatureOverride, py::const_))
    .def("HasCreatinineProductionRateOverride", &biogears::SEOverride::HasCreatinineProductionRateOverride)
    .def("GetCreatinineProductionRateOverride", py::overload_cast<>(&biogears::SEOverride::GetCreatinineProductionRateOverride))
    .def("GetCreatinineProductionRateOverride", py::overload_cast<const biogears::AmountPerTimeUnit&>(&biogears::SEOverride::GetCreatinineProductionRateOverride, py::const_))
    .def("HasExerciseMeanArterialPressureDeltaOverride", &biogears::SEOverride::HasExerciseMeanArterialPressureDeltaOverride)
    .def("GetExerciseMeanArterialPressureDeltaOverride", py::overload_cast<>(&biogears::SEOverride::GetExerciseMeanArterialPressureDeltaOverride))
    .def("GetExerciseMeanArterialPressureDeltaOverride", py::overload_cast<const biogears::PressureUnit&>(&biogears::SEOverride::GetExerciseMeanArterialPressureDeltaOverride, py::const_))
    .def("HasFatigueLevelOverride", &biogears::SEOverride::HasFatigueLevelOverride)
    .def("GetFatigueLevelOverride", py::overload_cast<>(&biogears::SEOverride::GetFatigueLevelOverride))
    .def("GetFatigueLevelOverride", py::overload_cast<>(&biogears::SEOverride::GetFatigueLevelOverride, py::const_))
    .def("HasLactateProductionRateOverride", &biogears::SEOverride::HasLactateProductionRateOverride)
    .def("GetLactateProductionRateOverride", py::overload_cast<>(&biogears::SEOverride::GetLactateProductionRateOverride))
    .def("GetLactateProductionRateOverride", py::overload_cast<const biogears::AmountPerTimeUnit&>(&biogears::SEOverride::GetLactateProductionRateOverride, py::const_))
    .def("HasSkinTemperatureOverride", &biogears::SEOverride::HasSkinTemperatureOverride)
    .def("GetSkinTemperatureOverride", py::overload_cast<>(&biogears::SEOverride::GetSkinTemperatureOverride))
    .def("GetSkinTemperatureOverride", py::overload_cast<const biogears::TemperatureUnit&>(&biogears::SEOverride::GetSkinTemperatureOverride, py::const_))
    .def("HasSweatRateOverride", &biogears::SEOverride::HasSweatRateOverride)
    .def("GetSweatRateOverride", py::overload_cast<>(&biogears::SEOverride::GetSweatRateOverride))
    .def("GetSweatRateOverride", py::overload_cast<const biogears::MassPerTimeUnit&>(&biogears::SEOverride::GetSweatRateOverride, py::const_))
    .def("HasTotalMetabolicOverride", &biogears::SEOverride::HasTotalMetabolicOverride)
    .def("GetTotalMetabolicOverride", py::overload_cast<>(&biogears::SEOverride::GetTotalMetabolicOverride))
    .def("GetTotalMetabolicOverride", py::overload_cast<const biogears::PowerUnit&>(&biogears::SEOverride::GetTotalMetabolicOverride, py::const_))
    .def("HasTotalWorkRateLevelOverride", &biogears::SEOverride::HasTotalWorkRateLevelOverride)
    .def("GetTotalWorkRateLevelOverride", py::overload_cast<>(&biogears::SEOverride::GetTotalWorkRateLevelOverride))
    .def("GetTotalWorkRateLevelOverride", py::overload_cast<>(&biogears::SEOverride::GetTotalWorkRateLevelOverride, py::const_))
    .def("HasSodiumLostToSweatOverride", &biogears::SEOverride::HasSodiumLostToSweatOverride)
    .def("GetSodiumLostToSweatOverride", py::overload_cast<>(&biogears::SEOverride::GetSodiumLostToSweatOverride))
    .def("GetSodiumLostToSweatOverride", py::overload_cast<const biogears::MassUnit&>(&biogears::SEOverride::GetSodiumLostToSweatOverride, py::const_))
    .def("HasPotassiumLostToSweatOverride", &biogears::SEOverride::HasPotassiumLostToSweatOverride)
    .def("GetPotassiumLostToSweatOverride", py::overload_cast<>(&biogears::SEOverride::GetPotassiumLostToSweatOverride))
    .def("GetPotassiumLostToSweatOverride", py::overload_cast<const biogears::MassUnit&>(&biogears::SEOverride::GetPotassiumLostToSweatOverride, py::const_))
    .def("HasChlorideLostToSweatOverride", &biogears::SEOverride::HasChlorideLostToSweatOverride)
    .def("GetChlorideLostToSweatOverride", py::overload_cast<>(&biogears::SEOverride::GetChlorideLostToSweatOverride))
    .def("GetChlorideLostToSweatOverride", py::overload_cast<const biogears::MassUnit&>(&biogears::SEOverride::GetChlorideLostToSweatOverride, py::const_))
    .def("HasEnergyOverride", &biogears::SEOverride::HasEnergyOverride)
    .def("HasLeftAfferentArterioleResistanceOverride", &biogears::SEOverride::HasLeftAfferentArterioleResistanceOverride)
    .def("GetLeftAfferentArterioleResistanceOverride", py::overload_cast<>(&biogears::SEOverride::GetLeftAfferentArterioleResistanceOverride))
    .def("GetLeftAfferentArterioleResistanceOverride", py::overload_cast<const biogears::FlowResistanceUnit&>(&biogears::SEOverride::GetLeftAfferentArterioleResistanceOverride, py::const_))
    .def("HasLeftGlomerularFiltrationRateOverride", &biogears::SEOverride::HasLeftGlomerularFiltrationRateOverride)
    .def("GetLeftGlomerularFiltrationRateOverride", py::overload_cast<>(&biogears::SEOverride::GetLeftGlomerularFiltrationRateOverride))
    .def("GetLeftGlomerularFiltrationRateOverride", py::overload_cast<const biogears::VolumePerTimeUnit&>(&biogears::SEOverride::GetLeftGlomerularFiltrationRateOverride, py::const_))
    .def("HasLeftReaborptionRateOverride", &biogears::SEOverride::HasLeftReaborptionRateOverride)
    .def("GetLeftReaborptionRateOverride", py::overload_cast<>(&biogears::SEOverride::GetLeftReaborptionRateOverride))
    .def("GetLeftReaborptionRateOverride", py::overload_cast<const biogears::VolumePerTimeUnit&>(&biogears::SEOverride::GetLeftReaborptionRateOverride, py::const_))
    .def("HasRenalBloodFlowOverride", &biogears::SEOverride::HasRenalBloodFlowOverride)
    .def("GetRenalBloodFlowOverride", py::overload_cast<>(&biogears::SEOverride::GetRenalBloodFlowOverride))
    .def("GetRenalBloodFlowOverride", py::overload_cast<const biogears::VolumePerTimeUnit&>(&biogears::SEOverride::GetRenalBloodFlowOverride, py::const_))
    .def("HasRenalPlasmaFlowOverride", &biogears::SEOverride::HasRenalPlasmaFlowOverride)
    .def("GetRenalPlasmaFlowOverride", py::overload_cast<>(&biogears::SEOverride::GetRenalPlasmaFlowOverride))
    .def("GetRenalPlasmaFlowOverride", py::overload_cast<const biogears::VolumePerTimeUnit&>(&biogears::SEOverride::GetRenalPlasmaFlowOverride, py::const_))
    .def("HasRightAfferentArterioleResistanceOverride", &biogears::SEOverride::HasRightAfferentArterioleResistanceOverride)
    .def("GetRightAfferentArterioleResistanceOverride", py::overload_cast<>(&biogears::SEOverride::GetRightAfferentArterioleResistanceOverride))
    .def("GetRightAfferentArterioleResistanceOverride", py::overload_cast<const biogears::FlowResistanceUnit&>(&biogears::SEOverride::GetRightAfferentArterioleResistanceOverride, py::const_))
    .def("HasRightGlomerularFiltrationRateOverride", &biogears::SEOverride::HasRightGlomerularFiltrationRateOverride)
    .def("GetRightGlomerularFiltrationRateOverride", py::overload_cast<>(&biogears::SEOverride::GetRightGlomerularFiltrationRateOverride))
    .def("GetRightGlomerularFiltrationRateOverride", py::overload_cast<const biogears::VolumePerTimeUnit&>(&biogears::SEOverride::GetRightGlomerularFiltrationRateOverride, py::const_))
    .def("HasRightReaborptionRateOverride", &biogears::SEOverride::HasRightReaborptionRateOverride)
    .def("GetRightReaborptionRateOverride", py::overload_cast<>(&biogears::SEOverride::GetRightReaborptionRateOverride))
    .def("GetRightReaborptionRateOverride", py::overload_cast<const biogears::VolumePerTimeUnit&>(&biogears::SEOverride::GetRightReaborptionRateOverride, py::const_))
    .def("HasUrinationRateOverride", &biogears::SEOverride::HasUrinationRateOverride)
    .def("GetUrinationRateOverride", py::overload_cast<>(&biogears::SEOverride::GetUrinationRateOverride))
    .def("GetUrinationRateOverride", py::overload_cast<const biogears::VolumePerTimeUnit&>(&biogears::SEOverride::GetUrinationRateOverride, py::const_))
    .def("HasUrineProductionRateOverride", &biogears::SEOverride::HasUrineProductionRateOverride)
    .def("GetUrineProductionRateOverride", py::overload_cast<>(&biogears::SEOverride::GetUrineProductionRateOverride))
    .def("GetUrineProductionRateOverride", py::overload_cast<const biogears::VolumePerTimeUnit&>(&biogears::SEOverride::GetUrineProductionRateOverride, py::const_))
    .def("HasUrineOsmolalityOverride", &biogears::SEOverride::HasUrineOsmolalityOverride)
    .def("GetUrineOsmolalityOverride", py::overload_cast<>(&biogears::SEOverride::GetUrineOsmolalityOverride))
    .def("GetUrineOsmolalityOverride", py::overload_cast<const biogears::OsmolalityUnit&>(&biogears::SEOverride::GetUrineOsmolalityOverride, py::const_))
    .def("HasUrineVolumeOverride", &biogears::SEOverride::HasUrineVolumeOverride)
    .def("GetUrineVolumeOverride", py::overload_cast<>(&biogears::SEOverride::GetUrineVolumeOverride))
    .def("GetUrineVolumeOverride", py::overload_cast<const biogears::VolumeUnit&>(&biogears::SEOverride::GetUrineVolumeOverride, py::const_))
    .def("HasUrineUreaNitrogenConcentrationOverride", &biogears::SEOverride::HasUrineUreaNitrogenConcentrationOverride)
    .def("GetUrineUreaNitrogenConcentrationOverride", py::overload_cast<>(&biogears::SEOverride::GetUrineUreaNitrogenConcentrationOverride))
    .def("GetUrineUreaNitrogenConcentrationOverride", py::overload_cast<const biogears::MassPerVolumeUnit&>(&biogears::SEOverride::GetUrineUreaNitrogenConcentrationOverride, py::const_))
    .def("HasRenalOverride", &biogears::SEOverride::HasRenalOverride)
    .def("HasExpiratoryFlowOverride", &biogears::SEOverride::HasExpiratoryFlowOverride)
    .def("GetExpiratoryFlowOverride", py::overload_cast<>(&biogears::SEOverride::GetExpiratoryFlowOverride))
    .def("GetExpiratoryFlowOverride", py::overload_cast<const biogears::VolumePerTimeUnit&>(&biogears::SEOverride::GetExpiratoryFlowOverride, py::const_))
    .def("HasInspiratoryFlowOverride", &biogears::SEOverride::HasInspiratoryFlowOverride)
    .def("GetInspiratoryFlowOverride", py::overload_cast<>(&biogears::SEOverride::GetInspiratoryFlowOverride))
    .def("GetInspiratoryFlowOverride", py::overload_cast<const biogears::VolumePerTimeUnit&>(&biogears::SEOverride::GetInspiratoryFlowOverride, py::const_))
    .def("HasPulmonaryComplianceOverride", &biogears::SEOverride::HasPulmonaryComplianceOverride)
    .def("GetPulmonaryComplianceOverride", py::overload_cast<>(&biogears::SEOverride::GetPulmonaryComplianceOverride))
    .def("GetPulmonaryComplianceOverride", py::overload_cast<const biogears::FlowComplianceUnit&>(&biogears::SEOverride::GetPulmonaryComplianceOverride, py::const_))
    .def("HasPulmonaryResistanceOverride", &biogears::SEOverride::HasPulmonaryResistanceOverride)
    .def("GetPulmonaryResistanceOverride", py::overload_cast<>(&biogears::SEOverride::GetPulmonaryResistanceOverride))
    .def("GetPulmonaryResistanceOverride", py::overload_cast<const biogears::FlowResistanceUnit&>(&biogears::SEOverride::GetPulmonaryResistanceOverride, py::const_))
    .def("HasRespirationRateOverride", &biogears::SEOverride::HasRespirationRateOverride)
    .def("GetRespirationRateOverride", py::overload_cast<>(&biogears::SEOverride::GetRespirationRateOverride))
    .def("GetRespirationRateOverride", py::overload_cast<const biogears::FrequencyUnit&>(&biogears::SEOverride::GetRespirationRateOverride, py::const_))
    .def("HasTidalVolumeOverride", &biogears::SEOverride::HasTidalVolumeOverride)
    .def("GetTidalVolumeOverride", py::overload_cast<>(&biogears::SEOverride::GetTidalVolumeOverride))
    .def("GetTidalVolumeOverride", py::overload_cast<const biogears::VolumeUnit&>(&biogears::SEOverride::GetTidalVolumeOverride, py::const_))
    .def("HasTargetPulmonaryVentilationOverride", &biogears::SEOverride::HasTargetPulmonaryVentilationOverride)
    .def("GetTargetPulmonaryVentilationOverride", py::overload_cast<>(&biogears::SEOverride::GetTargetPulmonaryVentilationOverride))
    .def("GetTargetPulmonaryVentilationOverride", py::overload_cast<const biogears::VolumePerTimeUnit&>(&biogears::SEOverride::GetTargetPulmonaryVentilationOverride, py::const_))
    .def("HasTotalAlveolarVentilationOverride", &biogears::SEOverride::HasTotalAlveolarVentilationOverride)
    .def("GetTotalAlveolarVentilationOverride", py::overload_cast<>(&biogears::SEOverride::GetTotalAlveolarVentilationOverride))
    .def("GetTotalAlveolarVentilationOverride", py::overload_cast<const biogears::VolumePerTimeUnit&>(&biogears::SEOverride::GetTotalAlveolarVentilationOverride, py::const_))
    .def("HasTotalLungVolumeOverride", &biogears::SEOverride::HasTotalLungVolumeOverride)
    .def("GetTotalLungVolumeOverride", py::overload_cast<>(&biogears::SEOverride::GetTotalLungVolumeOverride))
    .def("GetTotalLungVolumeOverride", py::overload_cast<const biogears::VolumeUnit&>(&biogears::SEOverride::GetTotalLungVolumeOverride, py::const_))
    .def("HasTotalPulmonaryVentilationOverride", &biogears::SEOverride::HasTotalPulmonaryVentilationOverride)
    .def("GetTotalPulmonaryVentilationOverride", py::overload_cast<>(&biogears::SEOverride::GetTotalPulmonaryVentilationOverride))
    .def("GetTotalPulmonaryVentilationOverride", py::overload_cast<const biogears::VolumePerTimeUnit&>(&biogears::SEOverride::GetTotalPulmonaryVentilationOverride, py::const_))
    .def("HasRespiratoryOverride", &biogears::SEOverride::HasRespiratoryOverride)
    .def("HasExtravascularFluidVolumeOverride", &biogears::SEOverride::HasExtravascularFluidVolumeOverride)
    .def("GetExtravascularFluidVolumeOverride", py::overload_cast<>(&biogears::SEOverride::GetExtravascularFluidVolumeOverride))
    .def("GetExtravascularFluidVolumeOverride", py::overload_cast<const biogears::VolumeUnit&>(&biogears::SEOverride::GetExtravascularFluidVolumeOverride, py::const_))
    .def("HasIntracellularFluidVolumeOverride", &biogears::SEOverride::HasIntracellularFluidVolumeOverride)
    .def("GetIntracellularFluidVolumeOverride", py::overload_cast<>(&biogears::SEOverride::GetIntracellularFluidVolumeOverride))
    .def("GetIntracellularFluidVolumeOverride", py::overload_cast<const biogears::VolumeUnit&>(&biogears::SEOverride::GetIntracellularFluidVolumeOverride, py::const_))
    .def("HasLiverGlycogenOverride", &biogears::SEOverride::HasLiverGlycogenOverride)
    .def("GetLiverGlycogenOverride", py::overload_cast<>(&biogears::SEOverride::GetLiverGlycogenOverride))
    .def("GetLiverGlycogenOverride", py::overload_cast<const biogears::MassUnit&>(&biogears::SEOverride::GetLiverGlycogenOverride, py::const_))
    .def("HasMuscleGlycogenOverride", &biogears::SEOverride::HasMuscleGlycogenOverride)
    .def("GetMuscleGlycogenOverride", py::overload_cast<>(&biogears::SEOverride::GetMuscleGlycogenOverride))
    .def("GetMuscleGlycogenOverride", py::overload_cast<const biogears::MassUnit&>(&biogears::SEOverride::GetMuscleGlycogenOverride, py::const_))
    .def("HasStoredProteinOverride", &biogears::SEOverride::HasStoredProteinOverride)
    .def("GetStoredProteinOverride", py::overload_cast<>(&biogears::SEOverride::GetStoredProteinOverride))
    .def("GetStoredProteinOverride", py::overload_cast<const biogears::MassUnit&>(&biogears::SEOverride::GetStoredProteinOverride, py::const_))
    .def("HasStoredFatOverride", &biogears::SEOverride::HasStoredFatOverride)
    .def("GetStoredFatOverride", py::overload_cast<>(&biogears::SEOverride::GetStoredFatOverride))
    .def("GetStoredFatOverride", py::overload_cast<const biogears::MassUnit&>(&biogears::SEOverride::GetStoredFatOverride, py::const_))
    .def("HasTissueOverride", &biogears::SEOverride::HasTissueOverride)

    .def("ToString", py::overload_cast<std::ostream&>(&biogears::SEOverride::ToString, py::const_));

#ifdef VERSION_INFO
  m.attr("__version__") = VERSION_INFO;
#else
  m.attr("__version__") = "dev";
#endif
}
