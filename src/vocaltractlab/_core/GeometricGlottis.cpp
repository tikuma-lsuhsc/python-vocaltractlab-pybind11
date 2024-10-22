#include <array>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

#include <VocalTractLabBackend/GeometricGlottis.h>

namespace py = pybind11;
using namespace py::literals;

namespace vocaltractlab
{

    void initGeometricGlottis(py::module &m)
    {
        py::class_<GeometricGlottis> glottis(m, "GeometricGlottis");
        glottis
            .def(py::init<>());

        py::enum_<GeometricGlottis::ControlParamIndex>(glottis, "ControlParamIndex")
            .value("FREQUENCY", GeometricGlottis::ControlParamIndex::FREQUENCY)
            .value("PRESSURE", GeometricGlottis::ControlParamIndex::PRESSURE)
            .value("LOWER_END_X", GeometricGlottis::ControlParamIndex::LOWER_END_X)
            .value("UPPER_END_X", GeometricGlottis::ControlParamIndex::UPPER_END_X)
            .value("CHINK_AREA", GeometricGlottis::ControlParamIndex::CHINK_AREA)
            .value("PHASE_LAG", GeometricGlottis::ControlParamIndex::PHASE_LAG)
            .value("RELATIVE_AMPLITUDE", GeometricGlottis::ControlParamIndex::RELATIVE_AMPLITUDE)
            .value("DOUBLE_PULSING", GeometricGlottis::ControlParamIndex::DOUBLE_PULSING)
            .value("PULSE_SKEWNESS", GeometricGlottis::ControlParamIndex::PULSE_SKEWNESS)
            .value("FLUTTER", GeometricGlottis::ControlParamIndex::FLUTTER)
            .value("ASPIRATION_STRENGTH", GeometricGlottis::ControlParamIndex::ASPIRATION_STRENGTH)
            .value("NUM_CONTROL_PARAMS", GeometricGlottis::ControlParamIndex::NUM_CONTROL_PARAMS)
            .export_values();

        py::enum_<GeometricGlottis::StaticParamIndex>(glottis, "StaticParamIndex")
            .value("REST_THICKNESS", GeometricGlottis::StaticParamIndex::REST_THICKNESS)
            .value("REST_LENGTH", GeometricGlottis::StaticParamIndex::REST_LENGTH)
            .value("REST_F0", GeometricGlottis::StaticParamIndex::REST_F0)
            .value("CHINK_LENGTH", GeometricGlottis::StaticParamIndex::CHINK_LENGTH)
            .value("NUM_STATIC_PARAMS", GeometricGlottis::StaticParamIndex::NUM_STATIC_PARAMS)
            .export_values();

        py::enum_<GeometricGlottis::DerivedParamIndex>(glottis, "DerivedParamIndex")
            .value("LENGTH", GeometricGlottis::DerivedParamIndex::LENGTH)
            .value("THICKNESS", GeometricGlottis::DerivedParamIndex::THICKNESS)
            .value("AMPLITUDE", GeometricGlottis::DerivedParamIndex::AMPLITUDE)
            .value("LOWER_CORD_X", GeometricGlottis::DerivedParamIndex::LOWER_CORD_X)
            .value("UPPER_CORD_X", GeometricGlottis::DerivedParamIndex::UPPER_CORD_X)
            .value("LOWER_AREA", GeometricGlottis::DerivedParamIndex::LOWER_AREA)
            .value("UPPER_AREA", GeometricGlottis::DerivedParamIndex::UPPER_AREA)
            .value("CHINK_WIDTH", GeometricGlottis::DerivedParamIndex::CHINK_WIDTH)
            .value("NUM_DERIVED_PARAMS", GeometricGlottis::DerivedParamIndex::NUM_DERIVED_PARAMS)
            .export_values();
    }
}
