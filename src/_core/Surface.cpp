#include <vector>
#include <array>
#include <span>
#include <algorithm>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

#include <VocalTractLabBackend/Surface.h>

#include "util.h"

namespace py = pybind11;
using namespace py::literals;

namespace vocaltractlab
{

    void initSurface(py::module &m)
    {
        py::class_<Surface> surface(m, "Surface");

        surface
            .def_readonly_static("NUM_ASSOCIATED", &Surface::NUM_ASSOCIATED_TRIANGLES)
            .def_readonly_static("MAX_TILES_X", &Surface::MAX_TILES_X)
            .def_readonly_static("MAX_TILES_Y", &Surface::MAX_TILES_Y)
            .def_readonly_static("MAX_TILE_TRIANGLES", &Surface::MAX_TILE_TRIANGLES)
            .def_readonly_static("STANDARD_TILE_WIDTH", &Surface::STANDARD_TILE_WIDTH)
            .def_readonly_static("STANDARD_TILE_HEIGHT", &Surface::STANDARD_TILE_HEIGHT)
            .def_readonly_static("STANDARD_CREASE_ANGLE_DEGREE", &Surface::STANDARD_CREASE_ANGLE_DEGREE)

            .def_readwrite("vertex", &Surface::vertex)
            .def_readwrite("triangle", &Surface::triangle)
            .def_readwrite("edge", &Surface::edge)
            .def_readwrite("sequence", &Surface::sequence)

            // Information about the tiles ************************************
            .def_property_readonly("tile", [](Surface &self) { return std::span(std::span(self.tile));}, py::return_value_policy::reference_internal)
            .def_readwrite("left_border", &Surface::leftBorder)
            .def_readwrite("right_border", &Surface::rightBorder)
            .def_readwrite("top_border", &Surface::topBorder)
            .def_readwrite("bottom_border", &Surface::bottomBorder)

            .def_readwrite("tile_width", &Surface::tileWidth)
            .def_readwrite("tile_height", &Surface::tileHeight)
            .def_readwrite("num_tiles_x", &Surface::numTilesX)
            .def_readwrite("num_tiles_y", &Surface::numTilesY)

            /// The angle that separates between smooth shading and an edge
            .def_readwrite("crease_angle", &Surface::creaseAngle_deg)

            .def(py::init<>())
            .def(py::init<int, int>(), "ribs"_a, "rib_points"_a)
            .def("init", &Surface::init, "ribs"_a, "rib_points"_a)
            .def("clear", &Surface::clear)

            /// Set the coordinates of the given vertex.
            .def("setVertex", py::overload_cast<int, int, double, double, double>(&Surface::setVertex), "ribs"_a, "rib_points"_a, "x"_a, "y"_a, "z"_a)

            /// Set the coordinates of the given vertex.
            .def("setVertex", py::overload_cast<int, int, const Point3D &>(&Surface::setVertex), "ribs"_a, "rib_points"_a, "p"_a)

            /// Get the coordinates of the given vertex.
            .def("getVertex", [](Surface &self, int rib, int ribPoint)
                 {
                double x, y, z;
                self.getVertex(rib,ribPoint,x,y,z);
                return py::make_tuple(x,y,z); }, "ribs"_a, "rib_points"_a)

            /// Get the index of the given vertex.
            .def("getVertexIndex", &Surface::getVertexIndex, "ribs"_a, "rib_points"_a)

            // Set the normal of the given vertex.
            .def("setNormal", &Surface::setNormal, "ribs"_a, "rib_points"_a, "normal"_a)

            // Get the normal of the given vertex.
            .def("getNormal", &Surface::getNormal, "ribs"_a, "rib_points"_a)
            .def("swapTriangleOrientation", &Surface::swapTriangleOrientation)
            .def("calculateNormals", &Surface::calculateNormals)
            .def("flipNormals", &Surface::flipNormals)
            .def("calculatePaintSequence", &Surface::calculatePaintSequence, "matrix"_a)
            .def("reversePaintSequence", &Surface::reversePaintSequence)

            .def("saveAsObjFile", &Surface::saveAsObjFile, "fileName"_a)

            // ****************************************************************
            // New !
            // ****************************************************************

            // Assign the triangles to the tiles.
            .def("prepareIntersections", &Surface::prepareIntersections)

            // Prepare the intersection for an individual intersection line.
            .def("prepareIntersection", &Surface::prepareIntersection, "q"_a, "v"_a)

            // Returns a list with potentially interesected triangles. This
            // function must be called after prepareIntersections().
            .def("getTriangleList", [](Surface &self, int MAX_ENTRIES)
                 {
                    // int MAX_ENTRIES
                    std::vector<int> indexList(MAX_ENTRIES);
                    int numEntries;
                    self.getTriangleList(indexList.data(),numEntries,MAX_ENTRIES);
                    return std::span(indexList.begin(),numEntries); })

            // Returns the intersection data for a single triangle.
            .def("getTriangleIntersection", [](Surface &self, int index)
                 {
            auto P0 = new Point2D, P1 = new Point2D, n = new Point2D;
            bool ret = self.getTriangleIntersection(index, *P0, *P1, *n);
            return (ret) ? py::make_tuple(P0, P1) : py::make_tuple(py::none(), py::none()); }, "index"_a)
            .def("appendToFile", &Surface::appendToFile, "file"_a)
            .def("readFromFile", &Surface::readFromFile, "file"_a, "initialize"_a);

        // ****************************************************************
        /// A vertex of the surface.
        // ****************************************************************
        py::class_<Surface::Vertex>(surface, "Vertex")
            .def_readwrite("coord", &Surface::Vertex::coord)
            .def_readwrite("rib", &Surface::Vertex::rib)
            .def_readwrite("rib_point", &Surface::Vertex::ribPoint)
            .def_readwrite("num_associates", &Surface::Vertex::numAssociates)
            .def_property_readonly("associated_triangle", as_std_span(Surface::Vertex, associatedTriangle), py::return_value_policy::reference_internal)
            .def_property_readonly("associated_corner", as_std_span(Surface::Vertex, associatedCorner), py::return_value_policy::reference_internal)
            .def_readwrite("reserved", &Surface::Vertex::reserved)
            .def_readwrite("was_tested", &Surface::Vertex::wasTested);

        // ****************************************************************
        /// A triangle defined by three vertices.
        // ****************************************************************
        py::class_<Surface::Triangle>(surface, "Triangle")
            .def_property_readonly("vertex", as_std_span(Surface::Triangle, vertex), py::return_value_policy::reference_internal)
            .def_property_readonly("edge", as_std_span(Surface::Triangle, edge), py::return_value_policy::reference_internal)
            .def_property_readonly("corner_normal", as_std_span(Surface::Triangle, cornerNormal), py::return_value_policy::reference_internal)
            .def_readwrite("plane_normal", &Surface::Triangle::planeNormal)
            .def_readwrite("area", &Surface::Triangle::area)
            .def_readwrite("distance", &Surface::Triangle::distance);

        // ****************************************************************
        /// An edge defined by two vertices.
        // ****************************************************************
        py::class_<Surface::Edge>(surface, "Edge")
            .def_property_readonly("vertex", as_std_span(Surface::Edge, vertex), py::return_value_policy::reference_internal)
            .def_readwrite("is_intersected", &Surface::Edge::isIntersected)
            .def_readwrite("was_tested", &Surface::Edge::isIntersected)
            .def_readwrite("intersection", &Surface::Edge::isIntersected);

        // ****************************************************************
        /// @brief A tile represents a rectangular part of the bounding box
        /// of the surface in the xy-plane.
        ///
        /// A tile contains the indices of all triangles that overlap the
        /// tile region to allow faster intersection point calculations.
        // ****************************************************************
        py::class_<Surface::Tile>(surface, "Tile")
            .def_readwrite("num_triangles", &Surface::Tile::numTriangles)
            .def_property_readonly("triangle", as_std_span(Surface::Tile, triangle), py::return_value_policy::reference_internal);
    }
};
