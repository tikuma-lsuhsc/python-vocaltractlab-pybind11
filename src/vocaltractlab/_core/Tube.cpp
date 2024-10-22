#include <algorithm>
#include <array>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <span>
#include <vector>

#include <VocalTractLabBackend/Tube.h>

#include "util.h"

namespace py = pybind11;
using namespace py::literals;

namespace vocaltractlab {

void initTube(py::module &m) {
	py::class_<Tube> tube(m, "Tube");

	// Each tube section is in the region of one of these articulators.
	// This information is needed for the synthesis of fricatives.
	py::enum_<Tube::Articulator>(tube, "Articulator")
	        .value("TONGUE", Tube::Articulator::TONGUE)
	        .value("LOWER_INCISORS", Tube::Articulator::LOWER_INCISORS)
	        .value("LOWER_LIP", Tube::Articulator::LOWER_LIP)
	        .value("OTHER_ARTICULATOR", Tube::Articulator::OTHER_ARTICULATOR)
	        .value("NUM_ARTICULATORS", Tube::Articulator::NUM_ARTICULATORS)
	        .export_values();

	// Maybe later add a "shape factor" as defined by Dang, Honda, Suzuki (JASA, 1994)
	// to model elliptical sections (shape factor = 1 for a circle).
	py::class_<Tube::Section>(tube, "Section")
	        .def_readwrite("pos_cm", &Tube::Section::pos_cm)
	        .def_readwrite("area_cm2", &Tube::Section::area_cm2)
	        .def_readwrite("length_cm", &Tube::Section::length_cm)
	        .def_readwrite("volume_cm3", &Tube::Section::volume_cm3)
	        .def_readwrite("wallMass_cgs", &Tube::Section::wallMass_cgs)
	        .def_readwrite("wallStiffness_cgs", &Tube::Section::wallStiffness_cgs)
	        .def_readwrite("wallResistance_cgs", &Tube::Section::wallResistance_cgs)
	        .def_readwrite("articulator", &Tube::Section::articulator);

	tube.def_readonly_static("NUM_TRACHEA_SECTIONS", &Tube::NUM_TRACHEA_SECTIONS)
	        .def_readonly_static("NUM_GLOTTIS_SECTIONS", &Tube::NUM_GLOTTIS_SECTIONS)
	        .def_readonly_static("NUM_PHARYNX_SECTIONS", &Tube::NUM_PHARYNX_SECTIONS)
	        .def_readonly_static("NUM_MOUTH_SECTIONS", &Tube::NUM_MOUTH_SECTIONS)
	        .def_readonly_static("NUM_PHARYNX_MOUTH_SECTIONS",
	                             &Tube::NUM_PHARYNX_MOUTH_SECTIONS)
	        .def_readonly_static("NUM_NOSE_SECTIONS", &Tube::NUM_NOSE_SECTIONS)
	        .def_readonly_static("NUM_SINUS_SECTIONS", &Tube::NUM_SINUS_SECTIONS)
	        .def_readonly_static("NUM_FOSSA_SECTIONS", &Tube::NUM_FOSSA_SECTIONS)
	        .def_readonly_static("NUM_SECTIONS", &Tube::NUM_SECTIONS)
	        .def_readonly_static("FIRST_TRACHEA_SECTION", &Tube::FIRST_TRACHEA_SECTION)
	        .def_readonly_static("FIRST_GLOTTIS_SECTION", &Tube::FIRST_GLOTTIS_SECTION)
	        .def_readonly_static("LOWER_GLOTTIS_SECTION", &Tube::LOWER_GLOTTIS_SECTION)
	        .def_readonly_static("UPPER_GLOTTIS_SECTION", &Tube::UPPER_GLOTTIS_SECTION)
	        .def_readonly_static("FIRST_PHARYNX_SECTION", &Tube::FIRST_PHARYNX_SECTION)
	        .def_readonly_static("FIRST_MOUTH_SECTION", &Tube::FIRST_MOUTH_SECTION)
	        .def_readonly_static("FIRST_NOSE_SECTION", &Tube::FIRST_NOSE_SECTION)
	        .def_readonly_static("FIRST_FOSSA_SECTION", &Tube::FIRST_FOSSA_SECTION)
	        .def_readonly_static("FIRST_SINUS_SECTION", &Tube::FIRST_SINUS_SECTION)

	        .def_readonly_static("LAST_TRACHEA_SECTION", &Tube::LAST_TRACHEA_SECTION)
	        .def_readonly_static("LAST_PHARYNX_SECTION", &Tube::LAST_PHARYNX_SECTION)
	        .def_readonly_static("LAST_MOUTH_SECTION", &Tube::LAST_MOUTH_SECTION)
	        .def_readonly_static("LAST_NOSE_SECTION", &Tube::LAST_NOSE_SECTION)
	        .def_readonly_static("LAST_FOSSA_SECTION", &Tube::LAST_FOSSA_SECTION)
	        .def_readonly_static("LAST_SINUS_SECTION", &Tube::LAST_SINUS_SECTION)

	        .def_readonly_static(
	                "FOSSA_COUPLING_SECTION",
	                &Tube::FOSSA_COUPLING_SECTION) // Piriform fossa coupling section
	        .def_property_readonly_static("SINUS_COUPLING_SECTION",
	                                      as_std_span(Tube, SINUS_COUPLING_SECTION),
	                                      py::return_value_policy::reference_internal)

	        .def_readonly_static("STANDARD_WALL_MASS_CGS",
	                             &Tube::STANDARD_WALL_MASS_CGS)
	        .def_readonly_static("STANDARD_WALL_RESISTANCE_CGS",
	                             &Tube::STANDARD_WALL_RESISTANCE_CGS)
	        .def_readonly_static("STANDARD_WALL_STIFFNESS_CGS",
	                             &Tube::STANDARD_WALL_STIFFNESS_CGS)

	        .def_readonly_static("MIN_AREA_CM2", &Tube::MIN_AREA_CM2)
	        .def_readonly_static("DEFAULT_ASPIRATION_STRENGTH_DB",
	                             &Tube::DEFAULT_ASPIRATION_STRENGTH_DB)

	        .def_readonly_static("DEFAULT_SUBGLOTTAL_CAVITY_LENGTH_CM",
	                             &Tube::DEFAULT_SUBGLOTTAL_CAVITY_LENGTH_CM)
	        .def_readonly_static("DEFAULT_NASAL_CAVITY_LENGTH_CM",
	                             &Tube::DEFAULT_NASAL_CAVITY_LENGTH_CM)
	        .def_readonly_static("DEFAULT_PIRIFORM_FOSSA_LENGTH_CM",
	                             &Tube::DEFAULT_PIRIFORM_FOSSA_LENGTH_CM)
	        .def_readonly_static("DEFAULT_PIRIFORM_FOSSA_VOLUME_CM3",
	                             &Tube::DEFAULT_PIRIFORM_FOSSA_VOLUME_CM3)

	        .def_property_readonly_static("ARTICULATOR_LETTER",
	                                      as_std_span(Tube, ARTICULATOR_LETTER),
	                                      py::return_value_policy::reference_internal)

	        .def_property_readonly("tracheaSection", as_std_span(Tube, tracheaSection),
	                               py::return_value_policy::reference_internal)
	        .def_property_readonly("glottisSection", as_std_span(Tube, glottisSection),
	                               py::return_value_policy::reference_internal)
	        .def_property_readonly("pharynxMouthSection",
	                               as_std_span(Tube, pharynxMouthSection),
	                               py::return_value_policy::reference_internal)
	        .def_property_readonly("noseSection", as_std_span(Tube, noseSection),
	                               py::return_value_policy::reference_internal)
	        .def_property_readonly("sinusSection", as_std_span(Tube, sinusSection),
	                               py::return_value_policy::reference_internal)
	        .def_property_readonly("fossaSection", as_std_span(Tube, fossaSection),
	                               py::return_value_policy::reference_internal)

	        /// List of pointers to ALL tube sections of the model
	        // TODO: Section *section[NUM_SECTIONS];

	        /// Position of the incisors.
	        .def_readwrite("teethPosition_cm", &Tube::teethPosition_cm)

	        /// Aspiration strength at the glottis.
	        .def_readwrite("aspirationStrength_dB", &Tube::aspirationStrength_dB)

	        /// Elevation of the tongue tip side (corresponding to the TS3
	        /// parameter of the vocal tract model).
	        .def_readwrite("tongueTipSideElevation", &Tube::tongueTipSideElevation)

	        .def(py::init<>())
	        .def("initSubglottalCavity", &Tube::initSubglottalCavity,
	             "length_cm"_a = Tube::DEFAULT_SUBGLOTTAL_CAVITY_LENGTH_CM)
	        .def("initNasalCavity", &Tube::initNasalCavity,
	             "length_cm"_a = Tube::DEFAULT_NASAL_CAVITY_LENGTH_CM)
	        .def("initPiriformFossa", &Tube::initPiriformFossa,
	             "length_cm"_a = Tube::DEFAULT_PIRIFORM_FOSSA_LENGTH_CM,
	             "volume_cm3"_a = Tube::DEFAULT_PIRIFORM_FOSSA_VOLUME_CM3)

	        .def("resetDynamicPart", &Tube::resetDynamicPart)

	        .def(
	                "setPharynxMouthGeometry",
	                [](Tube &self,
	                   const std::span<double, Tube::NUM_PHARYNX_MOUTH_SECTIONS>
	                           &length_cm,
	                   const std::span<double, Tube::NUM_PHARYNX_MOUTH_SECTIONS>
	                           &area_cm2,
	                   const std::span<Tube::Articulator,
	                                   Tube::NUM_PHARYNX_MOUTH_SECTIONS>
	                           articulator,
	                   const double incisorPos_cm,
	                   const double tongueTipSideElevation) {
		                self.setPharynxMouthGeometry(length_cm.data(), area_cm2.data(),
		                                             articulator.data(), incisorPos_cm,
		                                             tongueTipSideElevation);
	                },
	                "length_cm"_a, "area_cm2"_a, "articulator"_a, "incisorPos_cm"_a,
	                "tongueTipSideElevation"_a)
	        .def(
	                "setGlottisGeometry",
	                [](Tube &self,
	                   const std::span<double, Tube::NUM_GLOTTIS_SECTIONS> &length_cm,
	                   const std::span<double, Tube::NUM_GLOTTIS_SECTIONS> &area_cm2) {
		                self.setGlottisGeometry(length_cm.data(), area_cm2.data());
	                },
	                "length_cm"_a, "area_cm2"_a)
	        .def("setGlottisArea", &Tube::setGlottisArea, "area_cm2"_a)
	        .def("setVelumOpening", &Tube::setVelumOpening, "area_cm2"_a)
	        .def("setAspirationStrength", &Tube::setAspirationStrength,
	             "aspirationStrength_dB"_a)

	        .def("interpolate", &Tube::interpolate, "leftTube"_a, "rightTube"_a,
	             "ratio"_a)

	        .def("getVelumOpening_cm2", &Tube::getVelumOpening_cm2)

	        .def("getStaticTubeDimensions",
	             [](Tube &self) {
		             double subglottalCavityLength_cm, nasalCavityLength_cm,
		                     piriformFossaLength_cm, piriformFossaVolume_cm3;
		             self.getStaticTubeDimensions(
		                     subglottalCavityLength_cm, nasalCavityLength_cm,
		                     piriformFossaLength_cm, piriformFossaVolume_cm3);
		             return py::make_tuple(subglottalCavityLength_cm,
		                                   nasalCavityLength_cm, piriformFossaLength_cm,
		                                   piriformFossaVolume_cm3);
	             })

	        .def("calcPositions", &Tube::calcPositions)
	        .def("print", &Tube::print)

	        .def("__eq__", &Tube::operator==)
	        .def("__ne__", &Tube::operator!=);
}
} // namespace vocaltractlab
