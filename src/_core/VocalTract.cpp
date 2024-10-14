#include <array>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <fmt/format.h>

#include <VocalTractLabBackend/VocalTract.h>

using namespace fmt::literals;
namespace py = pybind11;

void initGlottis(py::module &m)
{
  py::class_<VocalTract> vocal_tract(m, "VocalTract");

  vocal_tract.def_readonly_static("NUM_EPIGLOTTIS_RIBS", &VocalTract::NUM_EPIGLOTTIS_RIBS)
      .def_readonly_static("NUM_EPIGLOTTIS_POINTS", &VocalTract::NUM_EPIGLOTTIS_POINTS)
      .def_readonly_static("NUM_UVULA_RIBS", &VocalTract::NUM_UVULA_RIBS)
      .def_readonly_static("NUM_UVULA_POINTS", &VocalTract::NUM_UVULA_POINTS)
      .def_readonly_static("NUM_LARYNX_RIBS", &VocalTract::NUM_LARYNX_RIBS)
      .def_readonly_static("NUM_PHARYNX_RIBS", &VocalTract::NUM_PHARYNX_RIBS)
      .def_readonly_static("NUM_VELUM_RIBS", &VocalTract::NUM_VELUM_RIBS)
      .def_readonly_static("NUM_PALATE_RIBS", &VocalTract::NUM_PALATE_RIBS)
      .def_readonly_static("NUM_JAW_RIBS", &VocalTract::NUM_JAW_RIBS)
      .def_readonly_static("NUM_THROAT_RIBS", &VocalTract::NUM_THROAT_RIBS)
      .def_readonly_static("NUM_UPPER_COVER_RIBS", &VocalTract::NUM_UPPER_COVER_RIBS)
      .def_readonly_static("NUM_UPPER_COVER_POINTS", &VocalTract::NUM_UPPER_COVER_POINTS)
      .def_readonly_static("NUM_LOWER_COVER_RIBS", &VocalTract::NUM_LOWER_COVER_RIBS)
      .def_readonly_static("NUM_LOWER_COVER_POINTS", &VocalTract::NUM_LOWER_COVER_POINTS)
      .def_readonly_static("NUM_DYNAMIC_TONGUE_RIBS", &VocalTract::NUM_DYNAMIC_TONGUE_RIBS)
      .def_readonly_static("NUM_STATIC_TONGUE_RIBS", &VocalTract::NUM_STATIC_TONGUE_RIBS)
      .def_readonly_static("NUM_TONGUE_RIBS", &VocalTract::NUM_TONGUE_RIBS)
      .def_readonly_static("NUM_TONGUE_POINTS", &VocalTract::NUM_TONGUE_POINTS)
      .def_readonly_static("MAX_TONGUE_RIBS_GLOBAL", &VocalTract::MAX_TONGUE_RIBS_GLOBAL)
      .def_readonly_static("NUM_TEETH_RIBS", &VocalTract::NUM_TEETH_RIBS)
      .def_readonly_static("NUM_TEETH_POINTS", &VocalTract::NUM_TEETH_POINTS)
      .def_readonly_static("NUM_LIP_RIBS", &VocalTract::NUM_LIP_RIBS)
      .def_readonly_static("NUM_INNER_LIP_POINTS", &VocalTract::NUM_INNER_LIP_POINTS)
      .def_readonly_static("NUM_OUTER_LIP_POINTS", &VocalTract::NUM_OUTER_LIP_POINTS)
      .def_readonly_static("NUM_LIP_POINTS", &VocalTract::NUM_LIP_POINTS)
      .def_readonly_static("NUM_FILL_RIBS", &VocalTract::NUM_FILL_RIBS)
      .def_readonly_static("NUM_FILL_POINTS", &VocalTract::NUM_FILL_POINTS)
      .def_readonly_static("NUM_RADIATION_RIBS", &VocalTract::NUM_RADIATION_RIBS)
      .def_readonly_static("NUM_RADIATION_POINTS", &VocalTract::NUM_RADIATION_POINTS)

      // ****************************************************************
      // Constants for the cross-sections.
      // ****************************************************************
      .def_readonly_static("NUM_PROFILE_SAMPLES", &VocalTract::NUM_PROFILE_SAMPLES)
      .def_readonly_static("PROFILE_LENGTH", &VocalTract::PROFILE_LENGTH)
      .def_readonly_static("PROFILE_SAMPLE_LENGTH", &VocalTract::PROFILE_SAMPLE_LENGTH)
      .def_readonly_static("INVALID_PROFILE_SAMPLE", &VocalTract::INVALID_PROFILE_SAMPLE)
      .def_readonly_static("MIN_PROFILE_VALUE", &VocalTract::MIN_PROFILE_VALUE)
      .def_readonly_static("MAX_PROFILE_VALUE", &VocalTract::MAX_PROFILE_VALUE)
      .def_readonly_static("EXTREME_PROFILE_VALUE", &VocalTract::EXTREME_PROFILE_VALUE)

      // ****************************************************************
      // Other constants.
      // ****************************************************************
      .def_readonly_static("NUM_CENTERLINE_POINTS_EXPONENT", &VocalTract::NUM_CENTERLINE_POINTS_EXPONENT)
      .def_readonly_static("NUM_CENTERLINE_POINTS", &VocalTract::NUM_CENTERLINE_POINTS)
      .def_readonly_static("NUM_TUBE_SECTIONS", &VocalTract::NUM_TUBE_SECTIONS)
      .def_readonly_static("NUM_PHARYNX_SECTIONS", &VocalTract::NUM_PHARYNX_SECTIONS)
      .def_readonly_static("PIRIFORM_FOSSA_SECTION", &VocalTract::PIRIFORM_FOSSA_SECTION)

      // ****************************************************************
      // Variables.
      // ****************************************************************

      // .def_readwrite("surface", &VocalTract::surface)
      .def_property_readonly("surface", [](VocalTract &self)
                              { return py::array(self.NUM_SURFACES, self.surface, py::cast(self)); }, py::return_value_policy::reference_internal)
      // .def_readwrite("param", &VocalTract::param)
      .def_property_readonly("param", [](VocalTract &self)
                              { return py::array(self.NUM_PARAMS, self.param, py::cast(self)); }, py::return_value_policy::reference_internal)
      .def_readwrite("shapes", &VocalTract::shapes)
      .def_readwrite("emaPoints", &VocalTract::emaPoints)

      .def_readwrite("tongueRib", &VocalTract::tongueRib)

      // Guiding lines for the lip corners.
      .def_readwrite("tongueRib", &VocalTract::tongueRib)
      .def_readwrite("tongueRib", &VocalTract::tongueRib)
      .def_readwrite("tongueRib", &VocalTract::tongueRib)

      // Center line, cross sections, and tube sections.
      .def_readwrite("centerLineLength", &VocalTract::centerLineLength)
      // .def_readwrite("roughCenterLine", &VocalTract::roughCenterLine)
      .def_property_readonly("rough_center_line", [](VocalTract &self)
                              { return py::array(self.NUM_CENTERLINE_POINTS, self.roughCenterLine, py::cast(self)); }, py::return_value_policy::reference_internal)
      // .def_readwrite("centerLine", &VocalTract::centerLine)
      .def_property_readonly("center_line", [](VocalTract &self)
                              { return py::array(self.NUM_CENTERLINE_POINTS, self.centerLine, py::cast(self)); }, py::return_value_policy::reference_internal)
      // .def_readwrite("crossSection", &VocalTract::crossSection)
      .def_property_readonly("cross_section", [](VocalTract &self)
                              { return py::array(self.NUM_CENTERLINE_POINTS, self.crossSection, py::cast(self)); }, py::return_value_policy::reference_internal)
      // .def_readwrite("tubeSection", &VocalTract::tubeSection)
      .def_property_readonly("tube_section", [](VocalTract &self)
                              { return py::array(self.NUM_TUBE_SECTIONS, self.tubeSection, py::cast(self)); }, py::return_value_policy::reference_internal)

      // Position and opening of the velo-pharyngal port
      .def_readwrite("nasalPortPos_cm", &VocalTract::nasalPortPos_cm)
      .def_readwrite("nasalPortArea_cm2", &VocalTract::nasalPortArea_cm2)

      // Position of the incisors along the center line.
      .def_readwrite("incisorPos_cm", &VocalTract::incisorPos_cm)

      // Picewise linear approximations of the outer teeth edges
      // .def_readwrite("upperGumsInnerEdge", &VocalTract::upperGumsInnerEdge)
      .def_property_readonly("upper_gums_inner_edge", [](VocalTract &self)
                              { return py::array(self.NUM_JAW_RIBS, self.upperGumsInnerEdge, py::cast(self)); }, py::return_value_policy::reference_internal)
      // .def_readwrite("upperGumsOuterEdge", &VocalTract::upperGumsOuterEdge)
      .def_property_readonly("upper_gums_outer_edge", [](VocalTract &self)
                              { return py::array(self.NUM_JAW_RIBS, self.upperGumsOuterEdge, py::cast(self)); }, py::return_value_policy::reference_internal)
      // .def_readwrite("lowerGumsInnerEdge", &VocalTract::lowerGumsInnerEdge)
      .def_property_readonly("lower_gums_inner_edge", [](VocalTract &self)
                              { return py::array(self.NUM_JAW_RIBS, self.lowerGumsInnerEdge, py::cast(self)); }, py::return_value_policy::reference_internal)
      // .def_readwrite("lowerGumsOuterEdge", &VocalTract::lowerGumsOuterEdge)
      .def_property_readonly("lower_gums_outer_edge", [](VocalTract &self)
                              { return py::array(self.NUM_JAW_RIBS, self.lowerGumsOuterEdge, py::cast(self)); }, py::return_value_policy::reference_internal)
      // .def_readwrite("lowerGumsInnerEdgeOrig", &VocalTract::lowerGumsInnerEdgeOrig)
      .def_property_readonly("lower_gums_inner_edge_orig", [](VocalTract &self)
                              { return py::array(self.NUM_JAW_RIBS, self.lowerGumsInnerEdgeOrig, py::cast(self)); }, py::return_value_policy::reference_internal)
      // .def_readwrite("lowerGumsOuterEdgeOrig", &VocalTract::lowerGumsOuterEdgeOrig)
      .def_property_readonly("lower_gums_outer_edge_orig", [](VocalTract &self)
                              { return py::array(self.NUM_JAW_RIBS, self.lowerGumsOuterEdgeOrig, py::cast(self)); }, py::return_value_policy::reference_internal)

      // ****************************************************************
      // Initialization.
      // ****************************************************************
      .def(py::init<>())
      // .def(py::init<XmlNode&>())
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

      // // ****************************************************************
      // // Calculate the surfaces, center line, and area functions
      // // ****************************************************************

      // void (double *controlParams);
      .def("set_params", &VocalTract::setParams)
      .def("calculate_all", &VocalTract::calculateAll)

      // // ****************************************************************
      // // Calculate all geometric surfaces.
      // // ****************************************************************

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
      .def("tongue_side_param_to_elevation_cm", &VocalTract::tongueSideParamToElevation_cm)
      // double (double paramValue);
      .def("tongue_side_param_to_min_area_cm2", &VocalTract::tongueSideParamToMinArea_cm2)
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
      .def("insert_lower_cover_profile_line", [](VocalTract &self, Point2D P0, Point2D P1, int surfaceIndex,
                                                 py::array_t<double, py::array::c_style> upperProfile,
                                                 py::array_t<double, py::array::c_style> lowerProfile)
           {
            std::array<int, VocalTract::NUM_PROFILE_SAMPLES> upperProfileSurface;
            std::array<int, VocalTract::NUM_PROFILE_SAMPLES> lowerProfileSurface;

            py::buffer_info upper_info = upperProfile.request();
            if (upper_info.ndim != 1 || upper_info.shape[0] != VocalTract::NUM_PROFILE_SAMPLES)
              throw py::value_error("upper_profile must be 13-elements long.");

            py::buffer_info lower_info = lowerProfile.request();
            if (lower_info.ndim != 1 || lower_info.shape[0] != VocalTract::NUM_PROFILE_SAMPLES)
              throw py::value_error("upper_profile must be 13-elements long.");

             self.insertLowerCoverProfileLine(P0, P1, surfaceIndex, static_cast<double *>(upper_info.ptr), 
             upperProfileSurface.data(), static_cast<double *>(lower_info.ptr), lowerProfileSurface.data()); })

      .def("get_cross_section", [](VocalTract &self, std::array<double, VocalTract::NUM_PROFILE_SAMPLES> &upperProfile, std::array<double, VocalTract::NUM_PROFILE_SAMPLES> &lowerProfile)
           {
        auto section = new VocalTract::CrossSection();
        self.getCrossSection(upperProfile.data(),lowerProfile.data(),section);
        return section; }, "upper_profile"_a, "lower_profile"_a, py::return_value_policy::take_ownership)

      // bool (const string &fileName);
      .def("export_cross_sections", &VocalTract::exportCrossSections, "file_name"_a)
      // bool (const string &fileName, bool addCenterLine, bool addCutVectors);
      // .def("export_tract_contour_svg", &VocalTract::exportTractContourSvg)
      // void (ostream &os, Surface *s, int rib, int firstRibPoint, int lastRibPoint);
      // .def("add_rib_points_svg", &VocalTract::addRibPointsSvg)
      // void (ostream &os, Surface *s, int firstRib, int lastRib, int ribPoint);
      // .def("add_ribs_svg", &VocalTract::addRibsSvg)

      // ****************************************************************
      // Calculate the piecewise constant area function.
      // ****************************************************************
      .def("cross_sections_to_tube_sections", &VocalTract::crossSectionsToTubeSections)

      // ****************************************************************
      // Functions mainly for calls from outside this class.
      // ****************************************************************

      .def("get_shape_index", &VocalTract::getShapeIndex, "name"_a)
      .def("is_vowel_shape_name", &VocalTract::isVowelShapeName, "name"_a)
      .def("get_pharynx_back_x", &VocalTract::getPharynxBackX, "y"_a)
      .def("get_tube", [](VocalTract &self)
           {
              auto tube = new Tube();
              self.getTube(tube);
              return tube; }, "q"_a, py::return_value_policy::take_ownership)
      .def("get_center_line_pos", [](VocalTract &self, Point2D Q)
           {
              int bestIndex;
              double bestT;
              double closestPos = self.getCenterLinePos(Q,bestIndex,bestT);
              return py::make_tuple(closestPos, bestIndex, bestT); }, "q"_a, py::return_value_policy::take_ownership)
      .def("get_cut_vector", [](VocalTract &self, double pos)
           {
            auto P = new Point2D(); 
            auto v = new Point2D();
            self.getCutVector(pos, *P, *v);
            return py::make_tuple(P, v); }, "pos"_a, py::return_value_policy::take_ownership)
      .def("restrict_param", &VocalTract::restrictParam, "index"_a)
      .def("has_unsaved_changes", &VocalTract::hasUnsavedChanges)
      .def("clear_unsaved_changes", &VocalTract::clearUnsavedChanges)

      .def("store_control_params", &VocalTract::storeControlParams)
      .def("restore_control_params", &VocalTract::restoreControlParams);

  // ****************************************************************
  // Identifier for the different surfaces.
  // ****************************************************************

  // enum SurfaceIndex
  // {
  //   UPPER_TEETH, LOWER_TEETH,
  //   UPPER_COVER, LOWER_COVER,
  //   UPPER_LIP, LOWER_LIP,
  //   PALATE, MANDIBLE, LOWER_TEETH_ORIGINAL,
  //   LOW_VELUM, MID_VELUM, HIGH_VELUM,
  //   NARROW_LARYNX_FRONT, NARROW_LARYNX_BACK,
  //   WIDE_LARYNX_FRONT, WIDE_LARYNX_BACK,
  //   TONGUE,
  //   UPPER_COVER_TWOSIDE,
  //   LOWER_COVER_TWOSIDE,
  //   UPPER_TEETH_TWOSIDE,
  //   LOWER_TEETH_TWOSIDE,
  //   UPPER_LIP_TWOSIDE,
  //   LOWER_LIP_TWOSIDE,
  //   LEFT_COVER,        ///< Fill surface between the upper and lower teeth
  //   RIGHT_COVER,       ///< Fill surface between the upper and lower teeth
  //   UVULA_ORIGINAL,
  //   UVULA,
  //   UVULA_TWOSIDE,
  //   EPIGLOTTIS_ORIGINAL,
  //   EPIGLOTTIS,
  //   EPIGLOTTIS_TWOSIDE,
  //   RADIATION,
  //   NUM_SURFACES
  // };

  // // ****************************************************************
  // // Time-variant vocal tract parameters.
  // // ****************************************************************

  // struct Param
  // {
  //   double x;         ///< Parameter value set by the user or defined as target
  //   double limitedX;  ///< Parameter value limited by biomechanical constraints
  //   double min;
  //   double max;
  //   double neutral;
  //   string description; ///< Long name, e.g. "Horizontal tongue body position"
  //   string name;      ///< Abbreviation, e.g. "TCX"
  //   string unit;
  // };

  // // ****************************************************************

  // enum ParamIndex
  // {
  //   HX, HY, JX, JA,
  //   LP, LD, VS, VO,
  //   TCX, TCY, TTX, TTY,
  //   TBX, TBY, TRX, TRY,
  //   TS1, TS2, TS3,
  //   NUM_PARAMS
  // };

  // // ****************************************************************
  // // Anatomical, articulation-invariant vocal tract shape parameters.
  // // ****************************************************************

  // struct Anatomy
  // {
  //   Point3D palatePoints[NUM_PALATE_RIBS];
  //   double palateAngle_deg[NUM_PALATE_RIBS];
  //   double palateHeight_cm[NUM_PALATE_RIBS];
  //   double upperTeethHeight_cm[NUM_PALATE_RIBS];
  //   double upperTeethWidthTop_cm[NUM_PALATE_RIBS];
  //   double upperTeethWidthBottom_cm[NUM_PALATE_RIBS];

  //   Point2D jawFulcrum;
  //   Point2D jawRestPos;
  //   double toothRootLength_cm;
  //   Point3D jawPoints[NUM_JAW_RIBS];
  //   double jawAngle_deg[NUM_JAW_RIBS];
  //   double jawHeight_cm[NUM_JAW_RIBS];
  //   double lowerTeethHeight_cm[NUM_JAW_RIBS];
  //   double lowerTeethWidthTop_cm[NUM_JAW_RIBS];
  //   double lowerTeethWidthBottom_cm[NUM_JAW_RIBS];

  //   double tongueTipRadius_cm;
  //   double tongueCenterRadiusX_cm;
  //   double tongueCenterRadiusY_cm;
  //   bool automaticTongueRootCalc;
  //   double tongueRootTrxSlope;
  //   double tongueRootTrxIntercept;
  //   double tongueRootTrySlope;
  //   double tongueRootTryIntercept;

  //   double lipsWidth_cm;

  //   double uvulaWidth_cm;
  //   double uvulaHeight_cm;
  //   double uvulaDepth_cm;
  //   Point2D velumLowPoints[NUM_VELUM_RIBS-1];
  //   Point2D velumMidPoints[NUM_VELUM_RIBS-1];
  //   Point2D velumHighPoints[NUM_VELUM_RIBS-1];
  //   double maxNasalPortArea_cm2;

  //   Point2D pharynxFulcrum;
  //   double pharynxRotationAngle_deg;
  //   double pharynxTopRibY_cm;
  //   double pharynxUpperDepth_cm;
  //   double pharynxLowerDepth_cm;
  //   double pharynxBackWidth_cm;

  //   double epiglottisWidth_cm;
  //   double epiglottisHeight_cm;
  //   double epiglottisDepth_cm;
  //   double epiglottisAngle_deg;

  //   double larynxUpperDepth_cm;
  //   double larynxLowerDepth_cm;
  //   Point2D larynxWidePoints[8];
  //   Point2D larynxNarrowPoints[8];

  //   double piriformFossaLength_cm;
  //   double piriformFossaVolume_cm3;
  //   double subglottalCavityLength_cm;
  //   double nasalCavityLength_cm;

  //   // Factors controlling the intrinsic, direction-dependent
  //   // velocities of the articulators (i.e. parameters).
  //   double positiveVelocityFactor[NUM_PARAMS];
  //   double negativeVelocityFactor[NUM_PARAMS];
  // } anatomy;

  // // ****************************************************************
  // // A vocal tract shape or configuration, for example for the
  // // vowels [i], [a], [u].
  // // ****************************************************************

  // struct Shape
  // {
  //   string name;
  //   double param[NUM_PARAMS];    ///< Parameter value
  // };

  // // ****************************************************************
  // // A line point on the center line between glottis and lips.
  // // ****************************************************************

  // struct CenterLinePoint
  // {
  //   Point2D point;
  //   Point2D normal;
  //   double pos;
  //   double min, max;
  //   double reserved;
  // };

  // // ****************************************************************
  // // Specification of a tongue rib.
  // // ****************************************************************

  // struct TongueRib
  // {
  //   // The following variables must be set.
  //   Point2D point;
  //   double leftSideHeight;
  //   double rightSideHeight;

  //   // The following variables are for internal use only.
  //   Point2D left, right;
  //   Point2D normal;
  //   double minX, maxX;
  //   double minY, maxY;
  // };

  // // ****************************************************************

  // struct CrossSection
  // {
  //   double area;
  //   double circ;
  //   double pos;
  //   Tube::Articulator articulator;
  // };

  // // ****************************************************************

  // struct TubeSection
  // {
  //   double area;
  //   double circ;
  //   double pos;
  //   double length;
  //   Tube::Articulator articulator;
  // };

  // // ****************************************************************
  // // EMA points.
  // // ****************************************************************

  // enum EmaSurface
  // {
  //   EMA_SURFACE_TONGUE,
  //   EMA_SURFACE_UPPER_COVER,
  //   EMA_SURFACE_LOWER_COVER,
  //   EMA_SURFACE_UPPER_LIP,
  //   EMA_SURFACE_LOWER_LIP,
  //   NUM_EMA_SURFACES
  // };

  // struct EmaPoint
  // {
  //   string name;
  //   // EMA points are always in the midsagittal plane on the surface.
  //   EmaSurface emaSurface;
  //   int vertexIndex;
  // };

  //     py::enum_<VocalTract::AnatomyParameters>(vocal_tract, "Kind")
  //         .value("LIP_WIDTH", VocalTract::AnatomyParameters::LIP_WIDTH)
  //         .value("LIP_WIDTH", VocalTract::AnatomyParameters::MANDIBLE_HEIGHT)
  //         .value("LIP_WIDTH", VocalTract::AnatomyParameters::LOWER_MOLARS_HEIGHT)
  //         .value("LIP_WIDTH", VocalTract::AnatomyParameters::UPPER_MOLARS_HEIGHT)
  //         .value("LIP_WIDTH", VocalTract::AnatomyParameters::PALATE_HEIGHT)
  //         .value("LIP_WIDTH", VocalTract::AnatomyParameters::PALATE_DEPTH)
  //         .value("LIP_WIDTH", VocalTract::AnatomyParameters::HARD_PALATE_LENGTH)
  //         .value("LIP_WIDTH", VocalTract::AnatomyParameters::SOFT_PALATE_LENGTH)
  //         .value("LIP_WIDTH", VocalTract::AnatomyParameters::PHARYNX_LENGTH)
  //         .value("LIP_WIDTH", VocalTract::AnatomyParameters::LARYNX_LENGTH)
  //         .value("LIP_WIDTH", VocalTract::AnatomyParameters::LARYNX_WIDTH)
  //         .value("LIP_WIDTH", VocalTract::AnatomyParameters::VOCAL_FOLD_LENGTH)
  //         .value("LIP_WIDTH", VocalTract::AnatomyParameters::ORAL_PHARYNGEAL_ANGLE)
  //         .value("LIP_WIDTH", VocalTract::AnatomyParameters::NUM_ANATOMY_PARAMS)
  //         .export_values();

  // py::class_<VocalTract::Param>(vocal_tract, "VocalTract")
  //     .def_readwrite("name", &VocalTract::Param::name)
  //     .def_readwrite("abbr", &VocalTract::Param::abbr)
  //     .def_readwrite("unit", &VocalTract::Param::unit)
  //     .def_readwrite("min", &VocalTract::Param::min)
  //     .def_readwrite("max", &VocalTract::Param::max)
  //     .def_readwrite("x", &VocalTract::Param::x);
}
