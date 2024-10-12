#include <array>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <VocalTractLabBackend/AnatomyParams.h>

namespace py = pybind11;
using namespace py::literals;

namespace vocaltractlab
{

    void initAnatomyParams(py::module &m)
    {
        py::class_<AnatomyParams> anatomy_params(m, "AnatomyParams");

        anatomy_params.def(py::init<>())
            .def("restrict_params", &AnatomyParams::restrictParams)
            .def("calc_from_age", &AnatomyParams::calcFromAge, "age_month"_a, "is_male"_a)
            .def("get_from", &AnatomyParams::getFrom, "vocal_tract"_a)
            .def("set_for", &AnatomyParams::setFor, "vocal_tract"_a)
            .def("adjust_tongue_root_calculation", &AnatomyParams::adjustTongueRootCalculation, "target_vocal_tract"_a)
            .def("load_reference_vocal_tract", &AnatomyParams::loadReferenceVocalTract, "file_name"_a)
            .def("transform_x", &AnatomyParams::transformX, "orig_anatomy"_a, "orig_x"_a)
            .def("transform_y", py::overload_cast<AnatomyParams *, double>(&AnatomyParams::transformY), "orig_anatomy"_a, "orig_y"_a)
            .def("transform_y", py::overload_cast<AnatomyParams *, double, double>(&AnatomyParams::transformY), "orig_anatomy"_a, "orig_x"_a, "orig_y"_a)
            .def("adapt_articulation", [](AnatomyParams &self, py::array_t<double, py::array::c_style | py::array::forcecast> old_params)
                 {
                     const size_t sz = AnatomyParams::AnatomyParameters::NUM_ANATOMY_PARAMS;
                     std::array<double, sz> new_params;

                     py::buffer_info old_info = old_params.request();
                     if (old_info.ndim != 1 || old_info.shape[0] != sz)
                         throw py::value_error("old_params must be 13-elements long.");

                     self.adaptArticulation(static_cast<double *>(old_info.ptr), new_params.data());

                     return py::array(new_params.size(), new_params.data());
                 },
                 "old_params"_a, py::return_value_policy::take_ownership);

        py::enum_<AnatomyParams::AnatomyParameters>(anatomy_params, "Kind")
            .value("LIP_WIDTH", AnatomyParams::AnatomyParameters::LIP_WIDTH)
            .value("MANDIBLE_HEIGHT", AnatomyParams::AnatomyParameters::MANDIBLE_HEIGHT)
            .value("LOWER_MOLARS_HEIGHT", AnatomyParams::AnatomyParameters::LOWER_MOLARS_HEIGHT)
            .value("UPPER_MOLARS_HEIGHT", AnatomyParams::AnatomyParameters::UPPER_MOLARS_HEIGHT)
            .value("PALATE_HEIGHT", AnatomyParams::AnatomyParameters::PALATE_HEIGHT)
            .value("PALATE_DEPTH", AnatomyParams::AnatomyParameters::PALATE_DEPTH)
            .value("HARD_PALATE_LENGTH", AnatomyParams::AnatomyParameters::HARD_PALATE_LENGTH)
            .value("SOFT_PALATE_LENGTH", AnatomyParams::AnatomyParameters::SOFT_PALATE_LENGTH)
            .value("PHARYNX_LENGTH", AnatomyParams::AnatomyParameters::PHARYNX_LENGTH)
            .value("LARYNX_LENGTH", AnatomyParams::AnatomyParameters::LARYNX_LENGTH)
            .value("LARYNX_WIDTH", AnatomyParams::AnatomyParameters::LARYNX_WIDTH)
            .value("VOCAL_FOLD_LENGTH", AnatomyParams::AnatomyParameters::VOCAL_FOLD_LENGTH)
            .value("ORAL_PHARYNGEAL_ANGLE", AnatomyParams::AnatomyParameters::ORAL_PHARYNGEAL_ANGLE)
            .value("NUM_ANATOMY_PARAMS", AnatomyParams::AnatomyParameters::NUM_ANATOMY_PARAMS)
            .export_values();

        py::class_<AnatomyParams::Param>(anatomy_params, "AnatomyParams")
            .def_readwrite("name", &AnatomyParams::Param::name)
            .def_readwrite("abbr", &AnatomyParams::Param::abbr)
            .def_readwrite("unit", &AnatomyParams::Param::unit)
            .def_readwrite("min", &AnatomyParams::Param::min)
            .def_readwrite("max", &AnatomyParams::Param::max)
            .def_readwrite("x", &AnatomyParams::Param::x);
    }
}
