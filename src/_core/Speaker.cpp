#include <array>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

#include <VocalTractLabBackend/Speaker.h>

namespace py = pybind11;
using namespace py::literals;

namespace vocaltractlab
{

    void initSpeaker(py::module &m)
    {
        py::class_<Speaker>(m, "Speaker")
            // Construct an empty Speaker object
            .def(py::init<>())
            // Construct a Speaker from existing information
            .def(py::init<VocalTract *, const std::vector<Glottis *> &, size_t>(),
                 "vocal_tract"_a, "glottis_models"_a, "selected_glottis"_a = 0)
            // Construct a Speaker from a file
            .def(py::init<const std::string &>(), "filepath"_a)
            /// @brief Add a glottis model to the speaker
            /// @param newModel The model to add. Must be some sort of Glottis-derived object.
            /// @return The number of the speaker's glottis models (after the addition)
            .def("add_glottis_model", &Speaker::addGlottisModel, "new_model"_a)
            /// @brief Get the speaker's glottis models
            /// @return A vector containing pointers to Glottis-derived objects.
            .def("get_glottis_models", &Speaker::getGlottisModels)
            /// @brief Get the currently selected glottis model.
            /// @return The index in the vector of glottis models (see getGlottisModels())
            /// of the currently selected glottis model
            .def("get_selected_glottis", &Speaker::getSelectedGlottis)
            /// @brief Set the speaker's glottis models.
            /// @param newModels A vector containing pointers to Glottis-derived objects.
            /// Speaker does not assume ownership of the pointers and thus never deletes them!
            .def("set_glottis_models", &Speaker::setGlottisModels, "new_models"_a)
            /// @brief Set the currently selected glottis.
            /// @param idx The index of the currently selected glottis w.r.t. the vector of
            ///	glottis models (see getGlottisModels()).
            .def("set_selected_glottis", &Speaker::setSelectedGlottis, "idx"_a)
            /// @brief Set the speaker's vocal tract models.
            /// @param newModel A pointer to a VocalTract object. Speaker does not assume
            /// ownership of the pointer and thus never deletes it!
            .def("set_vocal_tract", &Speaker::setVocalTract, "new_model"_a)
            /// @brief  Get the speaker's vocal tract.
            /// @return A pointer to the speaker's vocal tract.
            .def("get_vocal_tract", &Speaker::getVocalTract)
            /// @brief Read the Speaker information from an XML file.
            /// @param path Path to the XML file.
            .def("read", &Speaker::read, "filepath"_a)
            /// @brief Save the Speaker information to an XML file.
            /// @param path Path to the XML file.
            .def("save", py::overload_cast<const std::string&>(&Speaker::save, py::const_), "filepath"_a);
    }
}
