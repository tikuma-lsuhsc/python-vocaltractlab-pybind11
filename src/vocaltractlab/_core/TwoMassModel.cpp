#include <array>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

#include <VocalTractLabBackend/TwoMassModel.h>

namespace py = pybind11;
using namespace py::literals;

namespace vocaltractlab
{

    void initTwoMassModel(py::module &m)
    {
        py::class_<TwoMassModel> glottis(m, "TwoMassModel");

        glottis.def(py::init<>())
            .def("get_tension_parameter", &TwoMassModel::getTensionParameter, "f0"_a)
            .def("get_length_and_thickness", &TwoMassModel::getLengthAndThickness, "Q"_a, "length"_a, "thickness"_a);

        py::enum_<TwoMassModel::ControlParamIndex>(glottis, "ControlParamIndex")
            .value("FREQUENCY", TwoMassModel::ControlParamIndex::FREQUENCY)
            .value("PRESSURE", TwoMassModel::ControlParamIndex::PRESSURE)
            .value("REST_DISP_1", TwoMassModel::ControlParamIndex::REST_DISP_1)
            .value("REST_DISP_2", TwoMassModel::ControlParamIndex::REST_DISP_2)
            .value("ARY_AREA", TwoMassModel::ControlParamIndex::ARY_AREA)
            .value("DAMPING_FACTOR", TwoMassModel::ControlParamIndex::DAMPING_FACTOR)
            .value("NUM_CONTROL_PARAMS", TwoMassModel::ControlParamIndex::NUM_CONTROL_PARAMS)
            .export_values();

        py::enum_<TwoMassModel::StaticParamIndex>(glottis, "StaticParamIndex")
            .value("REST_LENGTH", TwoMassModel::StaticParamIndex::REST_LENGTH)
            .value("REST_THICKNESS_1", TwoMassModel::StaticParamIndex::REST_THICKNESS_1)
            .value("REST_THICKNESS_2", TwoMassModel::StaticParamIndex::REST_THICKNESS_2)
            .value("MASS_1", TwoMassModel::StaticParamIndex::MASS_1)
            .value("MASS_2", TwoMassModel::StaticParamIndex::MASS_2)
            .value("DAMPING_RATIO_1", TwoMassModel::StaticParamIndex::DAMPING_RATIO_1)
            .value("DAMPING_RATIO_2", TwoMassModel::StaticParamIndex::DAMPING_RATIO_2)
            .value("SPRING_K_1", TwoMassModel::StaticParamIndex::SPRING_K_1)
            .value("SPRING_K_2", TwoMassModel::StaticParamIndex::SPRING_K_2)
            .value("SPRING_ETA_1", TwoMassModel::StaticParamIndex::SPRING_ETA_1)
            .value("SPRING_ETA_2", TwoMassModel::StaticParamIndex::SPRING_ETA_2)
            .value("CONTACT_SPRING_K_1", TwoMassModel::StaticParamIndex::CONTACT_SPRING_K_1)
            .value("CONTACT_SPRING_K_2", TwoMassModel::StaticParamIndex::CONTACT_SPRING_K_2)
            .value("CONTACT_SPRING_ETA_2", TwoMassModel::StaticParamIndex::CONTACT_SPRING_ETA_2)
            .value("COUPLING_SPRING_K", TwoMassModel::StaticParamIndex::COUPLING_SPRING_K)
            .value("CRITICAL_WIDTH", TwoMassModel::StaticParamIndex::CRITICAL_WIDTH)
            .value("NATURAL_F0", TwoMassModel::StaticParamIndex::NATURAL_F0)
            .value("F0_DIV_Q", TwoMassModel::StaticParamIndex::F0_DIV_Q)
            .value("CHINK_LENGTH", TwoMassModel::StaticParamIndex::CHINK_LENGTH)
            .value("NUM_STATIC_PARAMS", TwoMassModel::StaticParamIndex::NUM_STATIC_PARAMS)
            .export_values();

        py::enum_<TwoMassModel::DerivedParamIndex>(glottis, "DerivedParamIndex")
            .value("RELATIVE_DISP_1", TwoMassModel::DerivedParamIndex::RELATIVE_DISP_1)
            .value("RELATIVE_DISP_2", TwoMassModel::DerivedParamIndex::RELATIVE_DISP_2)
            .value("ABSOLUTE_DISP_1", TwoMassModel::DerivedParamIndex::ABSOLUTE_DISP_1)
            .value("ABSOLUTE_DISP_2", TwoMassModel::DerivedParamIndex::ABSOLUTE_DISP_2)
            .value("CURRENT_LENGTH", TwoMassModel::DerivedParamIndex::CURRENT_LENGTH)
            .value("CURRENT_THICKNESS_1", TwoMassModel::DerivedParamIndex::CURRENT_THICKNESS_1)
            .value("CURRENT_THICKNESS_2", TwoMassModel::DerivedParamIndex::CURRENT_THICKNESS_2)
            .value("CURRENT_AREA_1", TwoMassModel::DerivedParamIndex::CURRENT_AREA_1)
            .value("CURRENT_AREA_2", TwoMassModel::DerivedParamIndex::CURRENT_AREA_2)
            .value("CHINK_WIDTH", TwoMassModel::DerivedParamIndex::CHINK_WIDTH)
            .value("CURRENT_TENSION", TwoMassModel::DerivedParamIndex::CURRENT_TENSION)
            .value("NUM_DERIVED_PARAMS", TwoMassModel::DerivedParamIndex::NUM_DERIVED_PARAMS)
            .export_values();
    }
}
