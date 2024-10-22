#include <fmt/format.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

#include <VocalTractLabBackend/VocalTract.h>

#include "util.h"

namespace py = pybind11;
using namespace py::literals;

void initGlottis(py::module &m) {
	py::class_<VocalTract> vocal_tract(m, "VocalTract");

	vocal_tract
	        .def_readonly_static("NUM_EPIGLOTTIS_RIBS",
	                             &VocalTract::NUM_EPIGLOTTIS_RIBS)
	        .def_readonly_static("NUM_EPIGLOTTIS_POINTS",
	                             &VocalTract::NUM_EPIGLOTTIS_POINTS)
	        .def_readonly_static("NUM_UVULA_RIBS", &VocalTract::NUM_UVULA_RIBS)
	        .def_readonly_static("NUM_UVULA_POINTS", &VocalTract::NUM_UVULA_POINTS)
	        .def_readonly_static("NUM_LARYNX_RIBS", &VocalTract::NUM_LARYNX_RIBS)
	        .def_readonly_static("NUM_PHARYNX_RIBS", &VocalTract::NUM_PHARYNX_RIBS)
	        .def_readonly_static("NUM_VELUM_RIBS", &VocalTract::NUM_VELUM_RIBS)
	        .def_readonly_static("NUM_PALATE_RIBS", &VocalTract::NUM_PALATE_RIBS)
	        .def_readonly_static("NUM_JAW_RIBS", &VocalTract::NUM_JAW_RIBS)
	        .def_readonly_static("NUM_THROAT_RIBS", &VocalTract::NUM_THROAT_RIBS)
	        .def_readonly_static("NUM_UPPER_COVER_RIBS",
	                             &VocalTract::NUM_UPPER_COVER_RIBS)
	        .def_readonly_static("NUM_UPPER_COVER_POINTS",
	                             &VocalTract::NUM_UPPER_COVER_POINTS)
	        .def_readonly_static("NUM_LOWER_COVER_RIBS",
	                             &VocalTract::NUM_LOWER_COVER_RIBS)
	        .def_readonly_static("NUM_LOWER_COVER_POINTS",
	                             &VocalTract::NUM_LOWER_COVER_POINTS)
	        .def_readonly_static("NUM_DYNAMIC_TONGUE_RIBS",
	                             &VocalTract::NUM_DYNAMIC_TONGUE_RIBS)
	        .def_readonly_static("NUM_STATIC_TONGUE_RIBS",
	                             &VocalTract::NUM_STATIC_TONGUE_RIBS)
	        .def_readonly_static("NUM_TONGUE_RIBS", &VocalTract::NUM_TONGUE_RIBS)
	        .def_readonly_static("NUM_TONGUE_POINTS", &VocalTract::NUM_TONGUE_POINTS)
	        .def_readonly_static("MAX_TONGUE_RIBS_GLOBAL",
	                             &VocalTract::MAX_TONGUE_RIBS_GLOBAL)
	        .def_readonly_static("NUM_TEETH_RIBS", &VocalTract::NUM_TEETH_RIBS)
	        .def_readonly_static("NUM_TEETH_POINTS", &VocalTract::NUM_TEETH_POINTS)
	        .def_readonly_static("NUM_LIP_RIBS", &VocalTract::NUM_LIP_RIBS)
	        .def_readonly_static("NUM_INNER_LIP_POINTS",
	                             &VocalTract::NUM_INNER_LIP_POINTS)
	        .def_readonly_static("NUM_OUTER_LIP_POINTS",
	                             &VocalTract::NUM_OUTER_LIP_POINTS)
	        .def_readonly_static("NUM_LIP_POINTS", &VocalTract::NUM_LIP_POINTS)
	        .def_readonly_static("NUM_FILL_RIBS", &VocalTract::NUM_FILL_RIBS)
	        .def_readonly_static("NUM_FILL_POINTS", &VocalTract::NUM_FILL_POINTS)
	        .def_readonly_static("NUM_RADIATION_RIBS", &VocalTract::NUM_RADIATION_RIBS)
	        .def_readonly_static("NUM_RADIATION_POINTS",
	                             &VocalTract::NUM_RADIATION_POINTS)

	        // ****************************************************************
	        // Constants for the cross-sections.
	        // ****************************************************************
	        .def_readonly_static("NUM_PROFILE_SAMPLES",
	                             &VocalTract::NUM_PROFILE_SAMPLES)
	        .def_readonly_static("PROFILE_LENGTH", &VocalTract::PROFILE_LENGTH)
	        .def_readonly_static("PROFILE_SAMPLE_LENGTH",
	                             &VocalTract::PROFILE_SAMPLE_LENGTH)
	        .def_readonly_static("INVALID_PROFILE_SAMPLE",
	                             &VocalTract::INVALID_PROFILE_SAMPLE)
	        .def_readonly_static("MIN_PROFILE_VALUE", &VocalTract::MIN_PROFILE_VALUE)
	        .def_readonly_static("MAX_PROFILE_VALUE", &VocalTract::MAX_PROFILE_VALUE)
	        .def_readonly_static("EXTREME_PROFILE_VALUE",
	                             &VocalTract::EXTREME_PROFILE_VALUE)

	        // ****************************************************************
	        // Other constants.
	        // ****************************************************************
	        .def_readonly_static("NUM_CENTERLINE_POINTS_EXPONENT",
	                             &VocalTract::NUM_CENTERLINE_POINTS_EXPONENT)
	        .def_readonly_static("NUM_CENTERLINE_POINTS",
	                             &VocalTract::NUM_CENTERLINE_POINTS)
	        .def_readonly_static("NUM_TUBE_SECTIONS", &VocalTract::NUM_TUBE_SECTIONS)
	        .def_readonly_static("NUM_PHARYNX_SECTIONS",
	                             &VocalTract::NUM_PHARYNX_SECTIONS)
	        .def_readonly_static("PIRIFORM_FOSSA_SECTION",
	                             &VocalTract::PIRIFORM_FOSSA_SECTION)

	        // ****************************************************************
	        // Variables.
	        // ****************************************************************

	        // .def_readwrite("surface", &VocalTract::surface)
	        .def_property_readonly("surface", as_std_span(VocalTract, surface),
	                               py::return_value_policy::reference_internal)
	        // .def_readwrite("param", &VocalTract::param)
	        .def_property_readonly("param", as_std_span(VocalTract, param),
	                               py::return_value_policy::reference_internal)
	        .def_readwrite("shapes", &VocalTract::shapes)
	        .def_readwrite("ema_points", &VocalTract::emaPoints)

	        .def_property_readonly("tongue_rib", as_std_span(VocalTract, tongueRib),
	                               py::return_value_policy::reference_internal)

	        // Guiding lines for the lip corners.
	        .def_readwrite("wide_lip_corner_path", &VocalTract::wideLipCornerPath)
	        .def_readwrite("narrow_lip_corner_path", &VocalTract::narrowLipCornerPath)
	        .def_readwrite("lip_corner_path", &VocalTract::lipCornerPath)

	        // Center line, cross sections, and tube sections.
	        .def_readwrite("center_line_length", &VocalTract::centerLineLength)
	        // .def_readwrite("roughCenterLine", &VocalTract::roughCenterLine)
	        .def_property_readonly("rough_center_line",
	                               as_std_span(VocalTract, roughCenterLine),
	                               py::return_value_policy::reference_internal)
	        // .def_readwrite("centerLine", &VocalTract::centerLine)
	        .def_property_readonly("center_line", as_std_span(VocalTract, centerLine),
	                               py::return_value_policy::reference_internal)
	        // .def_readwrite("crossSection", &VocalTract::crossSection)
	        .def_property_readonly(
	                "cross_section",
	                [](VocalTract &self) {
		                return py::array(self.NUM_CENTERLINE_POINTS, self.crossSection,
		                                 py::cast(self));
	                },
	                py::return_value_policy::reference_internal)
	        // .def_readwrite("tubeSection", &VocalTract::tubeSection)
	        .def_property_readonly(
	                "tube_section",
	                [](VocalTract &self) {
		                return py::array(self.NUM_TUBE_SECTIONS, self.tubeSection,
		                                 py::cast(self));
	                },
	                py::return_value_policy::reference_internal)

	        // Position and opening of the velo-pharyngal port
	        .def_readwrite("nasal_port_pos_cm", &VocalTract::nasalPortPos_cm)
	        .def_readwrite("nasal_port_area_cm2", &VocalTract::nasalPortArea_cm2)

	        // Position of the incisors along the center line.
	        .def_readwrite("incisor_pos_cm", &VocalTract::incisorPos_cm)

	        // Picewise linear approximations of the outer teeth edges
	        // .def_readwrite("upperGumsInnerEdge", &VocalTract::upperGumsInnerEdge)
	        .def_property_readonly("upper_gums_inner_edge",
	                               as_std_span(VocalTract, upperGumsInnerEdge),
	                               py::return_value_policy::reference_internal)
	        // .def_readwrite("upperGumsOuterEdge", &VocalTract::upperGumsOuterEdge)
	        .def_property_readonly("upper_gums_outer_edge",
	                               as_std_span(VocalTract, upperGumsOuterEdge),
	                               py::return_value_policy::reference_internal)
	        // .def_readwrite("lowerGumsInnerEdge", &VocalTract::lowerGumsInnerEdge)
	        .def_property_readonly("lower_gums_inner_edge",
	                               as_std_span(VocalTract, lowerGumsInnerEdge),
	                               py::return_value_policy::reference_internal)
	        // .def_readwrite("lowerGumsOuterEdge", &VocalTract::lowerGumsOuterEdge)
	        .def_property_readonly("lower_gums_outer_edge",
	                               as_std_span(VocalTract, lowerGumsOuterEdge),
	                               py::return_value_policy::reference_internal)
	        // .def_readwrite("lowerGumsInnerEdgeOrig", &VocalTract::lowerGumsInnerEdgeOrig)
	        .def_property_readonly("lower_gums_inner_edge_orig",
	                               as_std_span(VocalTract, lowerGumsInnerEdgeOrig),
	                               py::return_value_policy::reference_internal)
	        // .def_readwrite("lowerGumsOuterEdgeOrig", &VocalTract::lowerGumsOuterEdgeOrig)
	        .def_property_readonly("lower_gums_outer_edge_orig",
	                               as_std_span(VocalTract, lowerGumsOuterEdgeOrig),
	                               py::return_value_policy::reference_internal)

	        // ****************************************************************
	        // Initialization.
	        // ****************************************************************
	        .def(py::init<>())
	        .def(py::init<XmlNode &>())
	        .def("init", &VocalTract::init)
	        .def("init_surface_grids", &VocalTract::initSurfaceGrids)
	        .def("init_reference_surfaces", &VocalTract::initReferenceSurfaces)
	        .def("init_larynx", &VocalTract::initLarynx)
	        .def("init_jaws", &VocalTract::initJaws)
	        .def("init_velum", &VocalTract::initVelum)
	        .def("set_default_ema_points", &VocalTract::setDefaultEmaPoints)
	        // Point3D (int index);
	        .def("get_ema_point_coord", &VocalTract::getEmaPointCoord)
	        // void (int emaSurface, int *min, int *max);
	        .def("get_ema_surface_vertex_range", &VocalTract::getEmaSurfaceVertexRange)

	        // ****************************************************************
	        // Reading and writing of anatomy and shapes from/to xml-files.
	        // ****************************************************************

	        // void (XmlNode *anatomyNode);
	        // .def("read_anatomy_xml", &VocalTract::readAnatomyXml)
	        // void (XmlNode *shapeListNode);
	        // .def("read_shapes_xml", &VocalTract::readShapesXml)
	        // void (XmlNode& node);
	        // .def("read_from_xml", &VocalTract::readFromXml)
	        // void (const string &speakerFileName);
	        // .def("read_from_xml", &VocalTract::readFromXml)
	        // void (std::ostream &os, int indent) const;
	        // .def("write_anatomy_xml", &VocalTract::writeAnatomyXml)
	        // void (std::ostream &os, int indent) const;
	        // .def("write_shapes_xml", &VocalTract::writeShapesXml)
	        // void (std::ostream &os, int indent) const;
	        // .def("write_to_xml", &VocalTract::writeToXml)

	        // bool (const string &fileName, bool saveBothSides = true);
	        .def("save_as_obj_file", &VocalTract::saveAsObjFile)

	        // friend std::ostream& operator<<(std::ostream& os, const VocalTract& obj)
	        // {
	        //     obj.writeToXml(os, 0);
	        //     return os;
	        // }

	        // ****************************************************************
	        // Calculate the surfaces, center line, and area functions
	        // ****************************************************************

	        // void (double *controlParams);
	        .def("set_params", &VocalTract::setParams)
	        .def("calculate_all", &VocalTract::calculateAll)

	        // ****************************************************************
	        // Calculate all geometric surfaces.
	        // ****************************************************************

	        .def("calc_surfaces", &VocalTract::calcSurfaces)
	        .def("calc_lips", &VocalTract::calcLips)
	        // void (Point3D &onset, Point3D &corner, Point3D &F0, Point3D &F1, double &yClose);
	        .def("get_important_lip_points", &VocalTract::getImportantLipPoints)
	        // void (Point3D lipCorner);
	        .def("calc_radiation", &VocalTract::calcRadiation)
	        // void (Point2D &H, Point2D &T);
	        .def("get_hyoid_tongue_tangent", &VocalTract::getHyoidTongueTangent)
	        .def("calc_tongue", &VocalTract::calcTongue)
	        // double (double paramValue);
	        .def("tongue_side_param_to_elevation_cm",
	             &VocalTract::tongueSideParamToElevation_cm)
	        // double (double paramValue);
	        .def("tongue_side_param_to_min_area_cm2",
	             &VocalTract::tongueSideParamToMinArea_cm2)
	        .def("restrict_tongue_params", &VocalTract::restrictTongueParams)
	        // Point2D (Point2D C, double rx, double ry, LineStrip2D &border, Point2D A);
	        .def("limit_ellipse_pos", &VocalTract::limitEllipsePos)
	        .def("calc_tongue_ribs", &VocalTract::calcTongueRibs)
	        // void (int rigid, int flexible);
	        .def("verify_tongue_rib_normal", &VocalTract::verifyTongueRibNormal)

	        // ****************************************************************
	        // Calculate the acoustic center line of the vocal tract.
	        // ****************************************************************

	        .def("calc_center_line", &VocalTract::calcCenterLine)
	        // void (int left, int center, int right);
	        .def("verify_center_line_normal", &VocalTract::verifyCenterLineNormal)

	        // ****************************************************************
	        // Calculate the piecewise linear area function.
	        // ****************************************************************

	        // void ();
	        .def("calc_cross_sections", &VocalTract::calcCrossSections)
	        // void (Point2D P, Point2D v, double *upperProfile, double *lowerProfile,
	        //   bool considerTongue, Tube::Articulator &articulator, bool debug = false);
	        .def("get_cross_profiles", &VocalTract::getCrossProfiles)
	        // void (Point2D P0, Point2D P1, int surfaceIndex,
	        //   double *upperProfile, int *upperProfileSurface);
	        .def("insert_upper_profile_line", &VocalTract::insertUpperProfileLine)
	        // void (Point2D P0, Point2D P1, int surfaceIndex,
	        //   double *lowerProfile, int *lowerProfileSurface);
	        .def("insert_lower_profile_line", &VocalTract::insertLowerProfileLine)
	        // void (Point2D P0, Point2D P1, int surfaceIndex,
	        //   double *upperProfile, int *upperProfileSurface, double *lowerProfile, int *lowerProfileSurface);
	        .def("insert_lower_cover_profile_line",
	             [](VocalTract &self, Point2D P0, Point2D P1, int surfaceIndex,
	                py::array_t<double, py::array::c_style> upperProfile,
	                py::array_t<double, py::array::c_style> lowerProfile) {
		             std::array<int, VocalTract::NUM_PROFILE_SAMPLES>
		                     upperProfileSurface;
		             std::array<int, VocalTract::NUM_PROFILE_SAMPLES>
		                     lowerProfileSurface;

		             py::buffer_info upper_info = upperProfile.request();
		             if (upper_info.ndim != 1 ||
		                 upper_info.shape[0] != VocalTract::NUM_PROFILE_SAMPLES)
			             throw py::value_error(
			                     "upper_profile must be 13-elements long.");

		             py::buffer_info lower_info = lowerProfile.request();
		             if (lower_info.ndim != 1 ||
		                 lower_info.shape[0] != VocalTract::NUM_PROFILE_SAMPLES)
			             throw py::value_error(
			                     "upper_profile must be 13-elements long.");

		             self.insertLowerCoverProfileLine(
		                     P0, P1, surfaceIndex,
		                     static_cast<double *>(upper_info.ptr),
		                     upperProfileSurface.data(),
		                     static_cast<double *>(lower_info.ptr),
		                     lowerProfileSurface.data());
	             })

	        .def(
	                "get_cross_section",
	                [](VocalTract &self) {
		                std::array<double, VocalTract::NUM_PROFILE_SAMPLES>
		                        upperProfile;
		                std::array<double, VocalTract::NUM_PROFILE_SAMPLES>
		                        lowerProfile;
		                VocalTract::CrossSection section;
		                self.getCrossSection(upperProfile.data(), lowerProfile.data(),
		                                     &section);
		                return py::make_tuple(section, upperProfile, lowerProfile);
	                },
	                py::return_value_policy::take_ownership)

	        .def("export_cross_sections", &VocalTract::exportCrossSections,
	             "file_name"_a)
	        .def("export_tract_contour_svg", &VocalTract::exportTractContourSvg,
	             "file_name"_a, "add_center_line"_a, "add_cut_vectors"_a)
	        // void (ostream &os, Surface *s, int rib, int firstRibPoint, int lastRibPoint);
	        // .def("add_rib_points_svg", &VocalTract::addRibPointsSvg)
	        // void (ostream &os, Surface *s, int firstRib, int lastRib, int ribPoint);
	        // .def("add_ribs_svg", &VocalTract::addRibsSvg)

	        // ****************************************************************
	        // Calculate the piecewise constant area function.
	        // ****************************************************************
	        .def("cross_sections_to_tube_sections",
	             &VocalTract::crossSectionsToTubeSections)

	        // ****************************************************************
	        // Functions mainly for calls from outside this class.
	        // ****************************************************************

	        .def("get_shape_index", &VocalTract::getShapeIndex, "name"_a)
	        .def("is_vowel_shape_name", &VocalTract::isVowelShapeName, "name"_a)
	        .def("get_pharynx_back_x", &VocalTract::getPharynxBackX, "y"_a)
	        .def("get_tube",
	             [](VocalTract &self) {
		             Tube tube;
		             self.getTube(&tube);
		             return tube;
	             })
	        .def(
	                "get_center_line_pos",
	                [](VocalTract &self, Point2D Q) {
		                int bestIndex;
		                double bestT;
		                double closestPos = self.getCenterLinePos(Q, bestIndex, bestT);
		                return py::make_tuple(closestPos, bestIndex, bestT);
	                },
	                "q"_a, py::return_value_policy::take_ownership)
	        .def(
	                "get_cut_vector",
	                [](VocalTract &self, double pos) {
		                auto P = new Point2D();
		                auto v = new Point2D();
		                self.getCutVector(pos, *P, *v);
		                return py::make_tuple(P, v);
	                },
	                "pos"_a, py::return_value_policy::take_ownership)
	        .def("restrict_param", &VocalTract::restrictParam, "index"_a)
	        .def("has_unsaved_changes", &VocalTract::hasUnsavedChanges)
	        .def("clear_unsaved_changes", &VocalTract::clearUnsavedChanges)

	        .def("store_control_params", &VocalTract::storeControlParams)
	        .def("restore_control_params", &VocalTract::restoreControlParams);

	// ****************************************************************
	// Identifier for the different surfaces.
	// ****************************************************************
	py::enum_<VocalTract::SurfaceIndex>(vocal_tract, "SurfaceIndex")
	        .value("UPPER_TEETH", VocalTract::SurfaceIndex::UPPER_TEETH)
	        .value("LOWER_TEETH", VocalTract::SurfaceIndex::LOWER_TEETH)
	        .value("UPPER_COVER", VocalTract::SurfaceIndex::UPPER_COVER)
	        .value("LOWER_COVER", VocalTract::SurfaceIndex::LOWER_COVER)
	        .value("UPPER_LIP", VocalTract::SurfaceIndex::UPPER_LIP)
	        .value("LOWER_LIP", VocalTract::SurfaceIndex::LOWER_LIP)
	        .value("PALATE", VocalTract::SurfaceIndex::PALATE)
	        .value("MANDIBLE", VocalTract::SurfaceIndex::MANDIBLE)
	        .value("LOWER_TEETH_ORIGINAL",
	               VocalTract::SurfaceIndex::LOWER_TEETH_ORIGINAL)
	        .value("LOW_VELUM", VocalTract::SurfaceIndex::LOW_VELUM)
	        .value("MID_VELUM", VocalTract::SurfaceIndex::MID_VELUM)
	        .value("HIGH_VELUM", VocalTract::SurfaceIndex::HIGH_VELUM)
	        .value("NARROW_LARYNX_FRONT", VocalTract::SurfaceIndex::NARROW_LARYNX_FRONT)
	        .value("NARROW_LARYNX_BACK", VocalTract::SurfaceIndex::NARROW_LARYNX_BACK)
	        .value("WIDE_LARYNX_FRONT", VocalTract::SurfaceIndex::WIDE_LARYNX_FRONT)
	        .value("WIDE_LARYNX_BACK", VocalTract::SurfaceIndex::WIDE_LARYNX_BACK)
	        .value("TONGUE", VocalTract::SurfaceIndex::TONGUE)
	        .value("UPPER_COVER_TWOSIDE", VocalTract::SurfaceIndex::UPPER_COVER_TWOSIDE)
	        .value("LOWER_COVER_TWOSIDE", VocalTract::SurfaceIndex::LOWER_COVER_TWOSIDE)
	        .value("UPPER_TEETH_TWOSIDE", VocalTract::SurfaceIndex::UPPER_TEETH_TWOSIDE)
	        .value("LOWER_TEETH_TWOSIDE", VocalTract::SurfaceIndex::LOWER_TEETH_TWOSIDE)
	        .value("UPPER_LIP_TWOSIDE", VocalTract::SurfaceIndex::UPPER_LIP_TWOSIDE)
	        .value("LOWER_LIP_TWOSIDE", VocalTract::SurfaceIndex::LOWER_LIP_TWOSIDE)
	        .value("LEFT_COVER", VocalTract::SurfaceIndex::LEFT_COVER)
	        .value("RIGHT_COVER", VocalTract::SurfaceIndex::RIGHT_COVER)
	        .value("UVULA_ORIGINAL", VocalTract::SurfaceIndex::UVULA_ORIGINAL)
	        .value("UVULA", VocalTract::SurfaceIndex::UVULA)
	        .value("UVULA_TWOSIDE", VocalTract::SurfaceIndex::UVULA_TWOSIDE)
	        .value("EPIGLOTTIS_ORIGINAL", VocalTract::SurfaceIndex::EPIGLOTTIS_ORIGINAL)
	        .value("EPIGLOTTIS", VocalTract::SurfaceIndex::EPIGLOTTIS)
	        .value("EPIGLOTTIS_TWOSIDE", VocalTract::SurfaceIndex::EPIGLOTTIS_TWOSIDE)
	        .value("RADIATION", VocalTract::SurfaceIndex::RADIATION)
	        .value("NUM_SURFACES", VocalTract::SurfaceIndex::NUM_SURFACES)
	        .export_values();

	// // ****************************************************************
	// // Time-variant vocal tract parameters.
	// // ****************************************************************
	py::class_<VocalTract::Param>(vocal_tract, "Param")
	        .def_readwrite("x", &VocalTract::Param::x)
	        .def_readwrite("limitedX", &VocalTract::Param::limitedX)
	        .def_readwrite("min", &VocalTract::Param::min)
	        .def_readwrite("max", &VocalTract::Param::max)
	        .def_readwrite("neutral", &VocalTract::Param::neutral)
	        .def_readwrite("description", &VocalTract::Param::description)
	        .def_readwrite("name", &VocalTract::Param::name)
	        .def_readwrite("unit", &VocalTract::Param::unit);

	// // ****************************************************************
	py::enum_<VocalTract::ParamIndex>(vocal_tract, "ParamIndex")
	        .value("HX,", VocalTract::ParamIndex::HX)
	        .value("HY,", VocalTract::ParamIndex::HY)
	        .value("JX,", VocalTract::ParamIndex::JX)
	        .value("JA,", VocalTract::ParamIndex::JA)
	        .value("LP,", VocalTract::ParamIndex::LP)
	        .value("LD,", VocalTract::ParamIndex::LD)
	        .value("VS,", VocalTract::ParamIndex::VS)
	        .value("VO,", VocalTract::ParamIndex::VO)
	        .value("TCX,", VocalTract::ParamIndex::TCX)
	        .value("TCY,", VocalTract::ParamIndex::TCY)
	        .value("TTX,", VocalTract::ParamIndex::TTX)
	        .value("TTY,", VocalTract::ParamIndex::TTY)
	        .value("TBX,", VocalTract::ParamIndex::TBX)
	        .value("TBY,", VocalTract::ParamIndex::TBY)
	        .value("TRX,", VocalTract::ParamIndex::TRX)
	        .value("TRY,", VocalTract::ParamIndex::TRY)
	        .value("TS1,", VocalTract::ParamIndex::TS1)
	        .value("TS2,", VocalTract::ParamIndex::TS2)
	        .value("TS3,", VocalTract::ParamIndex::TS3)
	        .value("NUM_PARAMS", VocalTract::ParamIndex::NUM_PARAMS)
	        .export_values();

	// // ****************************************************************
	// // Anatomical, articulation-invariant vocal tract shape parameters.
	// // ****************************************************************
	py::class_<VocalTract::Anatomy>(vocal_tract, "Anatomy")

	        .def_property_readonly("palate_points",
	                               as_std_span(VocalTract::Anatomy, palatePoints))
	        .def_property_readonly("palate_angle_deg",
	                               as_std_span(VocalTract::Anatomy, palateAngle_deg))
	        .def_property_readonly("palate_height_cm",
	                               as_std_span(VocalTract::Anatomy, palateHeight_cm))
	        .def_property_readonly(
	                "upper_teeth_height_cm",
	                as_std_span(VocalTract::Anatomy, upperTeethHeight_cm))
	        .def_property_readonly(
	                "upper_teeth_width_top_cm",
	                as_std_span(VocalTract::Anatomy, upperTeethWidthTop_cm))
	        .def_property_readonly(
	                "upper_teeth_width_bottom_cm",
	                as_std_span(VocalTract::Anatomy, upperTeethWidthBottom_cm))

	        .def_readwrite("jaw_fulcrum", &VocalTract::Anatomy::jawFulcrum)
	        .def_readwrite("jaw_rest_pos", &VocalTract::Anatomy::jawRestPos)
	        .def_readwrite("tooth_root_length_cm",
	                       &VocalTract::Anatomy::toothRootLength_cm)
	        .def_property_readonly("jaw_points",
	                               as_std_span(VocalTract::Anatomy, jawPoints))
	        .def_property_readonly("jaw_angle_deg",
	                               as_std_span(VocalTract::Anatomy, jawAngle_deg))
	        .def_property_readonly("jaw_height_cm",
	                               as_std_span(VocalTract::Anatomy, jawHeight_cm))
	        .def_property_readonly(
	                "lower_teeth_height_cm",
	                as_std_span(VocalTract::Anatomy, lowerTeethHeight_cm))
	        .def_property_readonly(
	                "lower_teeth_width_top_cm",
	                as_std_span(VocalTract::Anatomy, lowerTeethWidthTop_cm))
	        .def_property_readonly(
	                "lower_teeth_width_bottom_cm",
	                as_std_span(VocalTract::Anatomy, lowerTeethWidthBottom_cm))

	        .def_readwrite("tongue_tip_radius_cm",
	                       &VocalTract::Anatomy::tongueTipRadius_cm)
	        .def_readwrite("tongue_center_radius_x_cm",
	                       &VocalTract::Anatomy::tongueCenterRadiusX_cm)
	        .def_readwrite("tongue_center_radius_y_cm",
	                       &VocalTract::Anatomy::tongueCenterRadiusY_cm)
	        .def_readwrite("automatic_tongue_root_calc",
	                       &VocalTract::Anatomy::automaticTongueRootCalc)
	        .def_readwrite("tongue_root_trx_slope",
	                       &VocalTract::Anatomy::tongueRootTrxSlope)
	        .def_readwrite("tongue_root_trx_intercept",
	                       &VocalTract::Anatomy::tongueRootTrxIntercept)
	        .def_readwrite("tongue_root_try_slope",
	                       &VocalTract::Anatomy::tongueRootTrySlope)
	        .def_readwrite("tongue_root_try_intercept",
	                       &VocalTract::Anatomy::tongueRootTryIntercept)

	        .def_readwrite("lips_width_cm", &VocalTract::Anatomy::lipsWidth_cm)

	        .def_readwrite("uvula_width_cm", &VocalTract::Anatomy::uvulaWidth_cm)
	        .def_readwrite("uvula_height_cm", &VocalTract::Anatomy::uvulaHeight_cm)
	        .def_readwrite("uvula_depth_cm", &VocalTract::Anatomy::uvulaDepth_cm)
	        .def_property_readonly("velum_low_points",
	                               as_std_span(VocalTract::Anatomy, velumLowPoints))
	        .def_property_readonly("velum_mid_points",
	                               as_std_span(VocalTract::Anatomy, velumMidPoints))
	        .def_property_readonly("velum_high_points",
	                               as_std_span(VocalTract::Anatomy, velumHighPoints))
	        .def_readwrite("max_nasal_port_area_cm2",
	                       &VocalTract::Anatomy::maxNasalPortArea_cm2)

	        .def_readwrite("pharynx_fulcrum", &VocalTract::Anatomy::pharynxFulcrum)
	        .def_readwrite("pharynx_rotation_angle_deg",
	                       &VocalTract::Anatomy::pharynxRotationAngle_deg)
	        .def_readwrite("pharynx_top_rib_y_cm", &VocalTract::Anatomy::pharynxTopRibY_cm)
	        .def_readwrite("pharynx_upper_depth_cm",
	                       &VocalTract::Anatomy::pharynxUpperDepth_cm)
	        .def_readwrite("pharynx_lower_depth_cm",
	                       &VocalTract::Anatomy::pharynxLowerDepth_cm)
	        .def_readwrite("pharynx_back_width_cm",
	                       &VocalTract::Anatomy::pharynxBackWidth_cm)

	        .def_readwrite("epiglottis_width_cm",
	                       &VocalTract::Anatomy::epiglottisWidth_cm)
	        .def_readwrite("epiglottis_height_cm",
	                       &VocalTract::Anatomy::epiglottisHeight_cm)
	        .def_readwrite("epiglottis_depth_cm",
	                       &VocalTract::Anatomy::epiglottisDepth_cm)
	        .def_readwrite("epiglottis_angle_deg",
	                       &VocalTract::Anatomy::epiglottisAngle_deg)

	        .def_readwrite("larynx_upper_depth_cm",
	                       &VocalTract::Anatomy::larynxUpperDepth_cm)
	        .def_readwrite("larynx_lower_depth_cm",
	                       &VocalTract::Anatomy::larynxLowerDepth_cm)
	        .def_property_readonly("larynx_wide_points",
	                               as_std_span(VocalTract::Anatomy, larynxWidePoints))
	        .def_property_readonly("larynx_narrow_points",
	                               as_std_span(VocalTract::Anatomy, larynxNarrowPoints))

	        .def_readwrite("piriform_fossa_length_cm",
	                       &VocalTract::Anatomy::piriformFossaLength_cm)
	        .def_readwrite("piriform_fossa_volume_cm3",
	                       &VocalTract::Anatomy::piriformFossaVolume_cm3)
	        .def_readwrite("subglottal_cavity_length_cm",
	                       &VocalTract::Anatomy::subglottalCavityLength_cm)
	        .def_readwrite("nasal_cavity_length_cm",
	                       &VocalTract::Anatomy::nasalCavityLength_cm)

	        // Factors controlling the intrinsic, direction-dependent
	        // velocities of the articulators (i.e. parameters).
	        .def_property_readonly(
	                "positive_velocity_factor",
	                as_std_span(VocalTract::Anatomy, positiveVelocityFactor))
	        .def_property_readonly(
	                "negative_velocity_factor",
	                as_std_span(VocalTract::Anatomy, negativeVelocityFactor));

	// ****************************************************************
	// A vocal tract shape or configuration, for example for the
	// vowels [i], [a], [u].
	// ****************************************************************
	py::class_<VocalTract::Shape>(vocal_tract, "Shape")
	        .def_readwrite("name", &VocalTract::Shape::name)
	        .def_property_readonly("param", as_std_span(VocalTract::Shape, param));

	// ****************************************************************
	// A line point on the center line between glottis and lips.
	// ****************************************************************
	py::class_<VocalTract::CenterLinePoint>(vocal_tract, "CenterLinePoint")

	        .def_readwrite("point", &VocalTract::CenterLinePoint::point)
	        .def_readwrite("normal", &VocalTract::CenterLinePoint::normal)
	        .def_readwrite("pos", &VocalTract::CenterLinePoint::pos)
	        .def_readwrite("min", &VocalTract::CenterLinePoint::min)
	        .def_readwrite("max", &VocalTract::CenterLinePoint::max)
	        .def_readwrite("reserved", &VocalTract::CenterLinePoint::reserved);

	// ****************************************************************
	// Specification of a tongue rib.
	// ****************************************************************
	py::class_<VocalTract::TongueRib>(vocal_tract, "TongueRib")

	        // The following variables must be set.
	        .def_readwrite("point", &VocalTract::TongueRib::point)
	        .def_readwrite("left_side_height", &VocalTract::TongueRib::leftSideHeight)
	        .def_readwrite("right_side_height", &VocalTract::TongueRib::rightSideHeight)

	        // The following variables are for internal use only.
	        .def_readwrite("left", &VocalTract::TongueRib::left)
	        .def_readwrite("right", &VocalTract::TongueRib::right)
	        .def_readwrite("normal", &VocalTract::TongueRib::normal)
	        .def_readwrite("minX", &VocalTract::TongueRib::minX)
	        .def_readwrite("maxX", &VocalTract::TongueRib::maxX)
	        .def_readwrite("minY", &VocalTract::TongueRib::minY)
	        .def_readwrite("maxY", &VocalTract::TongueRib::maxY);

	// ****************************************************************
	py::class_<VocalTract::CrossSection>(vocal_tract, "CrossSection")

	        .def_readwrite("area", &VocalTract::CrossSection::area)
	        .def_readwrite("circ", &VocalTract::CrossSection::circ)
	        .def_readwrite("pos", &VocalTract::CrossSection::pos)
	        .def_readwrite("articulator", &VocalTract::CrossSection::articulator);

	// ****************************************************************
	py::class_<VocalTract::TubeSection>(vocal_tract, "TubeSection")

	        .def_readwrite("area", &VocalTract::TubeSection::area)
	        .def_readwrite("circ", &VocalTract::TubeSection::circ)
	        .def_readwrite("pos", &VocalTract::TubeSection::pos)
	        .def_readwrite("length", &VocalTract::TubeSection::length)
	        .def_readwrite("articulator", &VocalTract::TubeSection::articulator);

	// ****************************************************************
	// EMA points.
	// ****************************************************************

	py::enum_<VocalTract::EmaSurface>(vocal_tract, "EmaSurface")
	        .value("EMA_SURFACE_TONGUE,", VocalTract::EmaSurface::EMA_SURFACE_TONGUE)
	        .value("EMA_SURFACE_UPPER_COVER,",
	               VocalTract::EmaSurface::EMA_SURFACE_UPPER_COVER)
	        .value("EMA_SURFACE_LOWER_COVER,",
	               VocalTract::EmaSurface::EMA_SURFACE_LOWER_COVER)
	        .value("EMA_SURFACE_UPPER_LIP,",
	               VocalTract::EmaSurface::EMA_SURFACE_UPPER_LIP)
	        .value("EMA_SURFACE_LOWER_LIP,",
	               VocalTract::EmaSurface::EMA_SURFACE_LOWER_LIP)
	        .value("NUM_EMA_SURFACES", VocalTract::EmaSurface::NUM_EMA_SURFACES)
	        .export_values();

	py::class_<VocalTract::EmaPoint>(vocal_tract, "EmaPoint")

	        .def_readwrite("name", &VocalTract::EmaPoint::name)
	        .def_readwrite("ema_surface", &VocalTract::EmaPoint::emaSurface)
	        .def_readwrite("vertex_index", &VocalTract::EmaPoint::vertexIndex);
}
