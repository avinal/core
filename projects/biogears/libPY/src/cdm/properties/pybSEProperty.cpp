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

#include <string>

#include <biogears/cdm/properties/SEProperty.h>

namespace py = pybind11;
using biogears::SEProperty;

class SEPropertyTrampoline : public biogears::SEProperty {
public:
  /* Inherit the constructors */
  using SEProperty::SEProperty;

  void Invalidate() override
  {
    PYBIND11_OVERRIDE_PURE(
      void,
      biogears::SEProperty,
      Invalidate);
  }

  bool IsValid() const override
  {
    PYBIND11_OVERRIDE_PURE(
      bool,
      biogears::SEProperty,
      IsValid);
  }
};

void define_pybSEProperty(pybind11::module_& m)
{
  pybind11::class_<biogears::SEProperty, SEPropertyTrampoline>(m, "SEProperty")
    .def(py::init<>())
    .def("Clear", &biogears::SEProperty::Clear)
    .def("Invalidate", &biogears::SEProperty::Invalidate)
    .def("IsValid", &biogears::SEProperty::IsValid)
    .def("Load", &biogears::SEProperty::Load);

#ifdef VERSION_INFO
  m.attr("__version__") == VERSION_INFO
#else
  m.attr("__version__") = "dev";
#endif
}
