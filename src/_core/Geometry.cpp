#include <array>
#include <fmt/core.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <VocalTractLabBackend/Geometry.h>

namespace py = pybind11;
using namespace py::literals;

namespace vocaltractlab {

std::string formatPoint2D(const Point2D &self) {
	return fmt::format("Point2D(x={}, y={})", self.x, self.y);
}
std::string formatPoint3D(const Point3D &self) {
	return fmt::format("Point3D(x={}, y={}, z={})", self.x, self.y, self.z);
}
std::string formatVector2D(const Vector2D &self) {
	return fmt::format("Vector2D(p={}, v={})", formatPoint2D(self.P),
	                   formatPoint2D(self.v));
}
std::string formatLine2D(const Line2D &self) {
	return fmt::format("Line2D(p0={}, p1={})", formatPoint2D(self.P[0]),
	                   formatPoint2D(self.P[1]));
}
std::string formatLine3D(const Line3D &self) {
	return fmt::format("Line3D(p0={}, p1={})", formatPoint3D(self.P[0]),
	                   formatPoint3D(self.P[1]));
}
std::string formatCircle(const Circle &self) {
	return fmt::format("Circle(c={}, r={})", formatPoint2D(self.M), self.r);
}
std::string formatEllipse2D(const Ellipse2D &self) {
	return fmt::format("Ellipse2D(m={}, half_width={}, half_height={})",
	                   formatPoint2D(self.M), self.halfWidth, self.halfHeight);
}

void initGeometry(py::module &m) {
	py::class_<Point2D>(m, "Point2D")
	        .def(py::init<>())
	        .def(py::init<double, double>(), "x"_a, "y"_a)
	        .def("set", &Point2D::set, "x"_a, "y"_a)
	        .def("is_right_from", &Point2D::isRightFrom, "v"_a)
	        .def("is_left_from", &Point2D::isLeftFrom, "v"_a)
	        .def("to_point3d", &Point2D::toPoint3D)
	        .def("lean_on", &Point2D::leanOn, "v"_a, "a"_a)
	        .def("normalize", &Point2D::normalize)
	        .def("turn_right", &Point2D::turnRight)
	        .def("turn_left", &Point2D::turnLeft)
	        .def("turn", &Point2D::turn, "angle"_a)
	        .def("get_distance_from", &Point2D::getDistanceFrom, "v"_a)
	        .def("magnitude", &Point2D::magnitude)
	        .def("square_magnitude", &Point2D::squareMagnitude)
	        //   Point2D& operator= (const Point2D &Q) { x = Q.x; y = Q.y; return *this; }
	        .def("__iadd__", &Point2D::operator+=)
	        .def("__isub__", &Point2D::operator-=)
	        .def("__imul__", &Point2D::operator*=)
	        .def("__itruediv__", &Point2D::operator/=)
	        .def_readwrite("x", &Point2D::x)
	        .def_readwrite("y", &Point2D::y)
	        .def("__ne__",
	             py::overload_cast<const Point2D &, const Point2D &>(operator!=))
	        .def("__eq__",
	             py::overload_cast<const Point2D &, const Point2D &>(operator==))
	        .def("__add__",
	             py::overload_cast<const Point2D &, const Point2D &>(operator+))
	        .def("__sub__",
	             py::overload_cast<const Point2D &, const Point2D &>(operator-))
	        .def("__mul__", py::overload_cast<const Point2D &, double>(operator*))
	        .def("__rmul__", [](const Point2D &self, double a) { return a * self; })
	        .def("__truediv__", py::overload_cast<const Point2D &, double>(operator/))
	        .def("__neg__", py::overload_cast<const Point2D &>(operator-))
	        .def("scalar_product",
	             py::overload_cast<const Point2D &, const Point2D &>(scalarProduct),
	             "q"_a)
	        .def("__matmul__",
	             py::overload_cast<const Point2D &, const Point2D &>(scalarProduct),
	             "q"_a)
	        .def("__repr__", &formatPoint2D);

	// ****************************************************************************
	// A 3D point.
	// ****************************************************************************
	py::class_<Point3D>(m, "Point3D")
	        .def(py::init<>())
	        .def(py::init<double, double, double>(), "x"_a, "y"_a, "z"_a)
	        .def("set", &Point3D::set, "x"_a, "y"_a, "z"_a)
	        .def("is_right_from", &Point3D::isRightFrom, "v"_a)
	        .def("to_point2d", &Point3D::toPoint2D)
	        .def("normalize", &Point3D::normalize)
	        .def("magnitude", &Point3D::magnitude)
	        //   Point3D& operator= (const Point3D &Q)
	        .def("__iadd__", &Point3D::operator+=)
	        .def("__isub__", &Point3D::operator-=)
	        .def("__imul__", &Point3D::operator*=)
	        .def("__itruediv__", &Point3D::operator/=)
	        .def_readwrite("x", &Point3D::x)
	        .def_readwrite("y", &Point3D::y)
	        .def_readwrite("z", &Point3D::z)
	        .def("__ne__",
	             py::overload_cast<const Point3D &, const Point3D &>(operator!=))
	        .def("__eq__",
	             py::overload_cast<const Point3D &, const Point3D &>(operator==))
	        .def("__add__",
	             py::overload_cast<const Point3D &, const Point3D &>(operator+))
	        .def("__sub__",
	             py::overload_cast<const Point3D &, const Point3D &>(operator-))
	        .def("__mul__", py::overload_cast<const Point3D &, double>(operator*))
	        .def("__rmul__", [](const Point3D &self, double a) { return a * self; })
	        .def("__truediv__", py::overload_cast<const Point3D &, double>(operator/))
	        .def("__neg__", py::overload_cast<const Point3D &>(operator-))
	        .def("scalar_product",
	             py::overload_cast<const Point3D &, const Point3D &>(scalarProduct),
	             "q"_a)
	        .def("__matmul__",
	             py::overload_cast<const Point3D &, const Point3D &>(scalarProduct))
	        .def("cross_product",
	             py::overload_cast<const Point3D &, const Point3D &>(crossProduct),
	             "q"_a)
	        .def("__repr__", &formatPoint3D);


	// ****************************************************************************
	// A 2D vector with a basis point and a vector.
	// ****************************************************************************
	py::class_<Vector2D>(m, "Vector2D")
	        .def(py::init<>())
	        .def(py::init<Point2D, Point2D>(), "p"_a, "v"_a)
	        .def("set", &Vector2D::set, "p"_a, "v"_a)
	        .def(
	                "get_interaction",
	                [](Vector2D &self, Vector2D &V) {
		                double t;
		                auto p = self.getIntersection(V, t);
		                return py::make_tuple(p, t);
	                },
	                "v"_a)
	        .def(
	                "get_interaction",
	                [](Vector2D &self, Line2D &L) {
		                double t;
		                bool ok;
		                Point2D p = self.getIntersection(L, t, ok);
		                return py::make_tuple(p, t, ok);
	                },
	                "line"_a)
	        .def(
	                "get_interaction",
	                [](Vector2D &self, Line3D &L) {
		                double t;
		                bool ok;
		                Point3D p = self.getIntersection(L, t, ok);
		                return py::make_tuple(p, t, ok);
	                },
	                "line"_a)
	        .def("normalize", &Vector2D::normalize)
	        .def("get_point", &Vector2D::getPoint)
	        .def("get_length", &Vector2D::getLength)
	        .def("is_not_null", &Vector2D::isNotNull)
	        .def_readwrite("p", &Vector2D::P)
	        .def_readwrite("v", &Vector2D::v)
	        .def("__repr__", &formatVector2D);
	;

	// ****************************************************************************
	// A 2D line defined by two points.
	// ****************************************************************************
	py::class_<Line2D>(m, "Line2D")
	        .def(py::init<>())
	        .def(py::init<Point2D, Point2D>(), "p0"_a, "p1"_a)
	        .def("set", &Line2D::set, "p0"_a, "p1"_a)
	        .def(
	                "get_interaction",
	                [](Line2D &self, Vector2D &V) {
		                double t;
		                bool ok;
		                Point2D p = self.getIntersection(V, t, ok);
		                return py::make_tuple(p, t, ok);
	                },
	                "vector"_a)
	        .def(
	                "get_interaction",
	                [](Line2D &self, Line2D &L) {
		                double t;
		                bool ok;
		                Point2D p = self.getIntersection(L, t, ok);
		                return py::make_tuple(p, t, ok);
	                },
	                "line"_a)
	        .def("get_point", &Line2D::getPoint)
	        .def("get_length", &Line2D::getLength)
	        .def("encloses", &Line2D::encloses)
	        .def_property_readonly(
	                "end_points_",
	                [](Line2D &self) {
		                return py::array(py::dtype("object"), 2, self.P,
		                                 py::cast(self));
	                },
	                py::return_value_policy::reference_internal)
	        .def("__repr__", &formatLine2D);


	// ****************************************************************************
	// A 3D line defined by two points.
	// ****************************************************************************
	py::class_<Line3D>(m, "Line3D")
	        .def(py::init<>())
	        .def(py::init<Point3D, Point3D>(), "p0"_a, "p1"_a)
	        .def("set", &Line3D::set, "p0"_a, "p1"_a)
	        .def(
	                "get_interaction",
	                [](Line3D &self, Vector2D &V) {
		                double t;
		                bool ok;
		                Point3D p = self.getIntersection(V, t, ok);
		                return py::make_tuple(p, t, ok);
	                },
	                "vector"_a)
	        .def("get_point", &Line3D::getPoint)
	        .def("get_length", &Line3D::getLength)
	        .def_property_readonly(
	                "end_points",
	                [](Line3D &self) {
		                return py::array(py::dtype("object"), 2, self.P,
		                                 py::cast(self));
	                },
	                py::return_value_policy::reference_internal)
	        .def("__repr__", &formatLine3D);

	// ****************************************************************************
	// A circle.
	// ****************************************************************************
	py::class_<Circle>(m, "Circle")
	        .def(py::init<>())
	        .def(py::init<Point2D, double>(), "c"_a, "radius"_a)
	        .def("set_valid_arc", &Circle::setValidArc, "angle0"_a, "angle1"_a)
	        .def("get_length", py::overload_cast<>(&Circle::getLength))
	        .def("get_length", py::overload_cast<double, double>(&Circle::getLength),
	             "a0"_a, "a1"_a)
	        .def("get_point", &Circle::getPoint, "angle"_a)
	        .def("get_normal", &Circle::getNormal, "angle"_a)
	        .def(
	                "get_interaction",
	                [](Circle &self, Vector2D &V) {
		                double intersectionAngle;
		                bool ok;
		                Point2D p = self.getIntersection(V, intersectionAngle, ok);
		                return py::make_tuple(p, intersectionAngle, ok);
	                },
	                "vector"_a)
	        .def(
	                "get_interaction",
	                [](Circle &self, Line2D &L) {
		                double intersectionAngle;
		                bool ok;
		                Point2D p = self.getIntersection(L, intersectionAngle, ok);
		                return py::make_tuple(p, intersectionAngle, ok);
	                },
	                "line"_a)
	        .def("get_tangent_contact_angle", &Circle::getTangentContactAngle, "h"_a,
	             "clockwise"_a)
	        .def("get_bend", &Circle::getBend)
	        .def("is_including", py::overload_cast<Point2D>(&Circle::isIncluding),
	             "point"_a)
	        .def("is_including", py::overload_cast<Line2D>(&Circle::isIncluding),
	             "line"_a)
	        .def("has_intersection_width", &Circle::hasIntersectionWith, "line"_a)
	        .def("get_common_left_tangent_with", &Circle::getCommonLeftTangentWith,
	             "circle"_a)
	        .def_readwrite("m", &Circle::M)
	        .def_readwrite("r", &Circle::r)
	        .def_property_readonly(
	                "end_points",
	                [](Circle &self) {
		                return py::array(py::dtype("object"), 2, self.arcAngle,
		                                 py::cast(self));
	                },
	                py::return_value_policy::reference_internal)
	        .def("__repr__", &formatCircle);

	m.def("get_circle_tangent", &getCircleTangent, "point"_a, "center"_a, "radius"_a,
	      "clockwise"_a = false);

	// ****************************************************************************
	// An ellipse.
	// ****************************************************************************

	m.attr("NUM_ELLIPSE_PROPS") = NUM_ELLIPSE_PROPS;

	py::class_<Ellipse2D>(m, "Ellipse2D")
	        .def(py::init<>())
	        .def(py::init<Point2D, double, double>(), "m"_a, "half_width"_a,
	             "half_height"_a)
	        .def("set", &Ellipse2D::set, "m"_a, "half_width"_a, "half_height"_a)
	        .def("get_point", &Ellipse2D::getPoint, "angle"_a)
	        .def("get_angle", &Ellipse2D::getAngle, "t"_a)
	        .def("get_perimeter", &Ellipse2D::getPerimeter)
	        .def_readwrite("half_width", &Ellipse2D::halfWidth)
	        .def_readwrite("half_height", &Ellipse2D::halfHeight)
	        .def_readwrite("m", &Ellipse2D::M)
	        .def("__repr__", &formatEllipse2D);

	// **************************************************************

	m.def("get_ellipse_tangent", &getEllipseTangent, "point"_a, "center"_a, "a"_a,
	      "b"_a, "clockwise"_a = false);
}
} // namespace vocaltractlab
