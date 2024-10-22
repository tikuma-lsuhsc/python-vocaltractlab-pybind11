#include <array>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

#include <VocalTractLabBackend/TriangularGlottis.h>

namespace py = pybind11;
using namespace py::literals;

namespace vocaltractlab
{

    void initTriangularGlottis(py::module &m)
    {
        py::class_<TriangularGlottis> glottis(m, "TriangularGlottis");
        
        glottis.def(py::init<>())
        .def("get_tension_parameter",&TriangularGlottis::getTensionParameter, "f0"_a)
        .def("get_length_and_thickness",&TriangularGlottis::getLengthAndThickness,"Q"_a, "length"_a, "thickness"_a)
        .def("get_open_close_dimensions", &TriangularGlottis::getOpenCloseDimensions,"open_length"_a, "contact_length"_a, "mean_open_width"_a, "mean_contact_z"_a)
        .def("get_contact_area",&TriangularGlottis::getContactArea, "back_x"_a, "front_x"_a, "length"_a, "thickness"_a);

        py::enum_<TriangularGlottis::ControlParamIndex>(glottis, "ControlParamIndex")
            .value("FREQUENCY", TriangularGlottis::ControlParamIndex::FREQUENCY)
            .value("PRESSURE", TriangularGlottis::ControlParamIndex::PRESSURE)
            .value("REST_DISP_1", TriangularGlottis::ControlParamIndex::REST_DISP_1)
            .value("REST_DISP_2", TriangularGlottis::ControlParamIndex::REST_DISP_2)
            .value("ARY_AREA", TriangularGlottis::ControlParamIndex::ARY_AREA)
            .value("ASPIRATION_STRENGTH", TriangularGlottis::ControlParamIndex::ASPIRATION_STRENGTH)
            .value("NUM_CONTROL_PARAMS", TriangularGlottis::ControlParamIndex::NUM_CONTROL_PARAMS)
            .export_values();

        py::enum_<TriangularGlottis::StaticParamIndex>(glottis, "StaticParamIndex")
            .value("REST_LENGTH", TriangularGlottis::StaticParamIndex::REST_LENGTH)
            .value("REST_THICKNESS_1", TriangularGlottis::StaticParamIndex::REST_THICKNESS_1)
            .value("REST_THICKNESS_2", TriangularGlottis::StaticParamIndex::REST_THICKNESS_2)
            .value("MASS_1", TriangularGlottis::StaticParamIndex::MASS_1)
            .value("MASS_2", TriangularGlottis::StaticParamIndex::MASS_2)
            .value("DAMPING_RATIO_1", TriangularGlottis::StaticParamIndex::DAMPING_RATIO_1)
            .value("DAMPING_RATIO_2", TriangularGlottis::StaticParamIndex::DAMPING_RATIO_2)
            .value("SPRING_K_1", TriangularGlottis::StaticParamIndex::SPRING_K_1)
            .value("SPRING_K_2", TriangularGlottis::StaticParamIndex::SPRING_K_2)
            .value("CONTACT_SPRING_K_1", TriangularGlottis::StaticParamIndex::CONTACT_SPRING_K_1)
            .value("CONTACT_SPRING_K_2", TriangularGlottis::StaticParamIndex::CONTACT_SPRING_K_2)
            .value("COUPLING_SPRING_K", TriangularGlottis::StaticParamIndex::COUPLING_SPRING_K)
            .value("INLET_LENGTH", TriangularGlottis::StaticParamIndex::INLET_LENGTH)
            .value("OUTLET_LENGTH", TriangularGlottis::StaticParamIndex::OUTLET_LENGTH)
            .value("NATURAL_F0", TriangularGlottis::StaticParamIndex::NATURAL_F0)
            .value("F0_DIV_Q", TriangularGlottis::StaticParamIndex::F0_DIV_Q)
            .value("NUM_STATIC_PARAMS", TriangularGlottis::StaticParamIndex::NUM_STATIC_PARAMS)
            .export_values();

        py::enum_<TriangularGlottis::DerivedParamIndex>(glottis, "DerivedParamIndex")
            .value("RELATIVE_DISP_1", TriangularGlottis::DerivedParamIndex::RELATIVE_DISP_1)
            .value("RELATIVE_DISP_2", TriangularGlottis::DerivedParamIndex::RELATIVE_DISP_2)
            .value("ABSOLUTE_DISP_1", TriangularGlottis::DerivedParamIndex::ABSOLUTE_DISP_1)
            .value("ABSOLUTE_DISP_2", TriangularGlottis::DerivedParamIndex::ABSOLUTE_DISP_2)
            .value("CURRENT_LENGTH", TriangularGlottis::DerivedParamIndex::CURRENT_LENGTH)
            .value("CURRENT_THICKNESS_1", TriangularGlottis::DerivedParamIndex::CURRENT_THICKNESS_1)
            .value("CURRENT_THICKNESS_2", TriangularGlottis::DerivedParamIndex::CURRENT_THICKNESS_2)
            .value("CURRENT_AREA_1", TriangularGlottis::DerivedParamIndex::CURRENT_AREA_1)
            .value("CURRENT_AREA_2", TriangularGlottis::DerivedParamIndex::CURRENT_AREA_2)
            .value("CURRENT_TENSION", TriangularGlottis::DerivedParamIndex::CURRENT_TENSION)
            .value("CONTACT_AREA", TriangularGlottis::DerivedParamIndex::CONTACT_AREA)
            .value("NUM_DERIVED_PARAMS", TriangularGlottis::DerivedParamIndex::NUM_DERIVED_PARAMS)
            .export_values();
    }
}
