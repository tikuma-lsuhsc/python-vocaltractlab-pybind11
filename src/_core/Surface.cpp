#include <array>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

#include <VocalTractLabBackend/Surface.h>

namespace py = pybind11;
using namespace py::literals;

namespace vocaltractlab
{

    void initSurface(py::module &m)
    {
        py::class_<Surface> surface(m, "Surface");

        surface
            .readonly_static("NUM_ASSOCIATED", &Surface::NUM_ASSOCIATED_TRIANGLES)
            .readonly_static("MAX_TILES_X", &Surface::MAX_TILES_X)
            .readonly_static("MAX_TILES_Y", &Surface::MAX_TILES_Y)
            .readonly_static("MAX_TILE_TRIANGLES", &Surface::MAX_TILE_TRIANGLES)
            .readonly_static("STANDARD_TILE_WIDTH", &Surface::STANDARD_TILE_WIDTH)
            .readonly_static("STANDARD_TILE_HEIGHT", &Surface::STANDARD_TILE_HEIGHT)
            .readonly_static("STANDARD_CREASE_ANGLE_DEGREE", &Surface::STANDARD_CREASE_ANGLE_DEGREE)

            .readwrite("vertex", &Surface::vertex)
            .readwrite("triangle", &Surface::triangle)
            .readwrite("edge", &Surface::edge)
            .readwrite("sequence", &Surface::sequence)

            // Information about the tiles ************************************
            .readwrite("tile", &Surface::tile)
            .readwrite("left_border", &Surface::leftBorder)
            .readwrite("right_border", &Surface::rightBorder)
            .readwrite("top_border", &Surface::topBorder)
            .readwrite("bottom_border", &Surface::bottomBorder)

            .readwrite("tile_width", &Surface::tileWidth)
            .readwrite("tile_height", &Surface::tileHeight)
            .readwrite("num_tiles_x", &Surface::numTilesX)
            .readwrite("num_tiles_y", &Surface::numTilesY)

            /// The angle that separates between smooth shading and an edge
            .readwrite("crease_angle", &Surface::creaseAngle_deg)

            .def(py::init<>())
            .def(py::init<int, int>(), "ribs"_a, "rib_points"_a)
            .def("init", &Surface::init, "ribs"_a, "rib_points"_a)
            .def("clear", &Surface::clear)

            /// Set the coordinates of the given vertex.
            .def("setVertex", &Surface::setVertex, "ribs"_a, "rib_points"_a, "x"_a, "y"_a, "z"_a)

            /// Set the coordinates of the given vertex.
            .def("setVertex", &Surface::setVertex, "ribs"_a, "rib_points"_a, "p"_a)

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
                    py::array indexList(MAX_ENTRIES, py::cast(self));
                    int numEntries;

                    self.getTriangleList(indexList.mutable_data(),numEntries,MAX_ENTRIES);
                    return indexList; })

            // Returns the intersection data for a single triangle.
            .def("getTriangleIntersection", [](Surface &self, int index)
                 {
            auto P0 = new Point2D, P1 = new Point2D, n = new Point2D;
            bool ret = self.getTriangleIntersection(index, P0, P1, n);
            return (ret) ? py::make_tuple(P0, P1) : py::make_tuple(py::none(), py::none()); }, "index"_a)
            .def("appendToFile", &Surface::appendToFile, "file"_a)
            .def("readFromFile", &Surface::readFromFile, "file"_a, "initialize"_a)
    }
}
