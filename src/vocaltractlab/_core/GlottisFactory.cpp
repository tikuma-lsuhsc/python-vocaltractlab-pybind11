#include <array>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

#include <VocalTractLabBackend/GlottisFactory.h>

namespace py = pybind11;
using namespace py::literals;

namespace vocaltractlab
{

    void initGlottisFactory(py::module &m)
    {

        py::enum_<GlottisModel>(m, "GlottisModel")
            .value("GEOMETRIC_GLOTTIS", GlottisModel::GEOMETRIC_GLOTTIS)
            .value("TWO_MASS_MODEL", GlottisModel::TWO_MASS_MODEL)
            .value("TRIANGULAR_GLOTTIS", TRIANGULAR_GLOTTIS)
            .value("NUM_GLOTTIS_MODELS", GlottisModel::NUM_GLOTTIS_MODELS)
            .export_values();

        py::module_ factory(m, "glottis_factory");
        factory.attr("glottis_name_to_enum") = GlottisFactory::glottis_name_to_enum;

        /// @brief Create a Glottis-derived object based on an XML representation.
        /// @param xml An XmlNode object containing the <glottis_model> tag
        /// @return A Glottis-derived object initialized with the data
        /// from the XML representation. The type depends on the "type"
        /// attribute in the XML representation.
        // Glottis* makeGlottis(XmlNode& xml);
        /// @brief Create a default Glottis-derived object
        /// @param type The type of Glottis to create (see GlottisModel for
        /// options). Uses the default constructor of the respective object.
        /// @return A default-initialized Glottis-derived object of type "type".
        factory.def("make_glottis", py::overload_cast<GlottisModel>(&GlottisFactory::makeGlottis), "type"_a)
            /// @brief Create a Glottis-derived object of a specific type using
            ///	and initialize it using data in an XML representation.
            /// @param type The type of Glottis to create (see GlottisModel for
            /// options).
            /// @param xml An XmlNode object containing the <glottis_model> tag
            /// @return A Glottis-derived object of type "type", initialized using
            ///	the data from the XML representation.
            // Glottis* makeGlottis(GlottisModel type, XmlNode& xml);
            /// @brief Create a default Glottis-derived object
            /// @param type The type of Glottis to create (see string_to_enum for
            /// options). Uses the default constructor of the respective object.
            /// @return A default-initialized Glottis-derived object of type "type".
            .def("make_glottis", py::overload_cast<const std::string &>(&GlottisFactory::makeGlottis), "type"_a);
        /// @brief Create a Glottis-derived object of a specific type using
        ///	and initialize it using data in an XML representation.
        /// @param type The type of Glottis to create (see string_to_enum for
        /// options).
        /// @param xml An XmlNode object containing the <glottis_model> tag
        /// @return A Glottis-derived object of type "type", initialized using
        ///	the data from the XML representation.
        // Glottis* makeGlottis(const std::string& type, XmlNode& xml);;
    }
}
