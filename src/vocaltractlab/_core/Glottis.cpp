#include <array>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

#include <VocalTractLabBackend/Glottis.h>

namespace py = pybind11;
using namespace py::literals;

namespace vocaltractlab
{

    void initGlottis(py::module &m)
    {
        py::class_<Glottis> glottis(m, "Glottis");
        glottis.def_property_readonly_static("FREQUENCY", [](py::object /* self */)
                                             { return Glottis::FREQUENCY; })
            .def_property_readonly_static("PRESSURE", [](py::object /* self */)
                                          { return Glottis::PRESSURE; })
            .def_property_readonly_static("MAX_CONTROL_PARAMS", [](py::object /* self */)
                                          { return Glottis::MAX_CONTROL_PARAMS; })
            .def_property_readonly_static("DEFAULT_ASPIRATION_STRENGTH_DB", [](py::object /* self */)
                                          { return Glottis::DEFAULT_ASPIRATION_STRENGTH_DB; })
            .def_readwrite("static_param", &Glottis::staticParam)
            .def_readwrite("control_param", &Glottis::controlParam)
            .def_readwrite("derived_param", &Glottis::derivedParam)
            .def_readwrite("shape", &Glottis::shape)
            .def_readwrite("saved_state", &Glottis::savedState)
            .def("get_name", &Glottis::getName)
            .def("reset_motion", &Glottis::resetMotion)
            .def("inc_time", &Glottis::incTime, "time_increment"_a, "pressure"_a)
            .def("calc_geometry", &Glottis::calcGeometry)
            .def("get_tube_data", &Glottis::getTubeData, "length"_a, "area"_a)
            .def("get_aperture_param_index", &Glottis::getApertureParamIndex)
            .def("get_aspiration_strength_db", &Glottis::getAspirationStrength_dB)
            .def("get_shape", &Glottis::getShape, "name"_a)
            .def("get_shape_index", &Glottis::getShapeIndex, "name"_a)
            .def("has_unsaved_changes", &Glottis::hasUnsavedChanges)
            .def("clear_unsaved_changes", &Glottis ::clearUnsavedChanges)
            .def("restrict_params", &Glottis::restrictParams, "parameters"_a)
            .def("store_control_params", &Glottis::storeControlParams)
            .def("load_control_params", &Glottis::restoreControlParams);

        py::class_<Glottis::Parameter>(glottis, "Parameter")
            .def_readwrite("name", &Glottis::Parameter::name)
            .def_readwrite("description", &Glottis::Parameter::description)
            .def_readwrite("cgs_unit", &Glottis::Parameter::cgsUnit)
            .def_readwrite("factor", &Glottis::Parameter::factor)
            .def_readwrite("user_unit", &Glottis::Parameter::userUnit)
            .def_readwrite("min", &Glottis::Parameter::min)
            .def_readwrite("max", &Glottis::Parameter::max)
            .def_readwrite("neutral", &Glottis::Parameter::neutral)
            .def_readwrite("x", &Glottis::Parameter::x);

        py::class_<Glottis::Shape>(glottis, "Shape")
            .def_readwrite("name", &Glottis::Shape::name)
            .def_readwrite("control_param", &Glottis::Shape::controlParam);

        py::class_<Glottis::SavedState>(glottis, "SavedState")
            .def_readwrite("static_param", &Glottis::SavedState::staticParam)
            .def_readwrite("shape", &Glottis::SavedState::shape);
    }
}
