/**************************************************************************************
Copyright 2015 Applied Research Associates, Inc.
Licensed under the Apache License, Version 2.0 (the License); you may not use
this file except in compliance with the License. You may obtain a copy of the License
at:
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under

the License is distributed on an AS IS BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
**************************************************************************************/
#include <pybind11/pybind11.h>      
#include <pybind11/operators.h>

#include <string>

#include <biogears/cdm/properties/SEScalarNeg1To1.h>

namespace py = pybind11;

using biogears::SEScalar;
using biogears::SEScalarNeg1To1;

void define_pybSEScalarNeg1To1(pybind11::module_ &m)
{

  pybind11::class_<biogears::SEScalarNeg1To1>(m, "SEScalarNeg1To1")
    .def(py::init<>())
  
    .def("Unload", py::overload_cast<>(&SEScalarNeg1To1::Unload, py::const_))
    .def("ToString", py::overload_cast<std::ostream&>(&SEScalarNeg1To1::ToString, py::const_))
    .def("GetValue", py::overload_cast<>(&SEScalar::GetValue, py::const_))
    .def("GetValue", py::overload_cast<const biogears::NoUnit&>(&SEScalarNeg1To1::GetValue, py::const_))
    .def("SetValue", py::overload_cast<double>(&SEScalar::SetValue))
    .def("SetValue", py::overload_cast<double, const biogears::NoUnit&>(&SEScalarNeg1To1::SetValue))

    .def("Increment",&SEScalarNeg1To1::Increment)
    .def("IncrementValue", &SEScalarNeg1To1::IncrementValue)
    .def("Decrement", &SEScalarNeg1To1::Decrement)
    .def("DecrementValue", &SEScalarNeg1To1::DecrementValue)    
    .def("Multiple", &SEScalarNeg1To1::MultiplyValue)
    .def("MultiplyValue", &SEScalarNeg1To1::Multiply)
    .def("DivideValue", &SEScalarNeg1To1::DivideValue)
    .def("Divide", &SEScalarNeg1To1::Divide)

    //.def("Equals", &SEScalarNeg1To1::Equals, py::const_)

    .def(py::self < py::self)
    .def(py::self <= py::self)
    .def(py::self > py::self)
    .def(py::self >= py::self)
    .def(py::self == py::self)
    .def(py::self != py::self)
    .def(py::self + py::self)
    .def(py::self += py::self)
    .def(py::self - py::self)
    .def(py::self -= py::self)
    .def(py::self * py::self)
    .def(py::self *= py::self)
    .def(py::self /= py::self)
    .def(py::self / py::self)
    ;

#ifdef VERSION_INFO
  m.attr("__version__") == VERSION_INFO
#else
  m.attr("__version__") = "dev";
#endif
}
