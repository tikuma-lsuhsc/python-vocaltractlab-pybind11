import vocaltractlab as vtl
from math import pi


def test_point2d():
    a = vtl.Point2D()
    print(a)

    b = vtl.Point2D(1, 2)
    print(b)

    c = vtl.Point3D(1, 2, 3)
    print(c)

    d = vtl.Vector2D(vtl.Point2D(1, 2), vtl.Point2D(3, 4))
    print(d)

    a.set(4, 4)
    assert a.x == 4 and a.y == 4

    print(a.to_point3d())
    print(a.normalize())
    print(a.turn_right())
    print(a.turn_left())
    a.turn(pi / 2)
    print(a)
    print(b.magnitude())
    print(b.square_magnitude())

    print(a.is_right_from(d))
    print(b.is_left_from(d))
    a.lean_on(d, b)
    print(a.get_distance_from(d))

    a += b
    a -= b
    a *= 2
    a /= 2

    print(a.x, a.y)
    a == b
    a != b
    a + b
    a - b
    a * 4
    a / 4
    4 * a

    a.x = 4
    a.y = 2
    print(a)
    b = -a
    a.scalar_product(b) == a @ b


def test_point3d():
    a = vtl.Point3D()
    b = vtl.Point3D(1, 2, 3)
    a.set(4, 5, 6)
    a.is_right_from(vtl.Vector2D())
    a.to_point2d()
    a.normalize()
    a.magnitude()
    a += b
    a -= b
    a *= 4
    a /= 4
    a.x
    a.y
    a.z
    a != b
    a == b
    a + b
    a - b
    a * 2
    2 * a
    a / 4
    -a
    a.scalar_product(b)
    a @ b
    a.cross_product(b)


def test_vector2d():
    a = vtl.Vector2D()
    b = vtl.Vector2D(p=vtl.Point2D(), v=vtl.Point2D())
    a.set(p=vtl.Point2D(), v=vtl.Point2D())
    a.get_intersection(b)
    a.get_intersection(vtl.Line2D())
    a.get_intersection(vtl.Line3D())
    a.normalize()
    a.get_point(0)
    a.get_length(0)
    a.is_not_null()
    a.p
    a.v
    print(a)


def test_line2d():
    a = vtl.Line2D()
    b = vtl.Line2D(p0=vtl.Point2D(), p1=vtl.Point2D())
    a.set(p0=vtl.Point2D(), p1=vtl.Point2D())
    a.get_intersection(line=vtl.Line2D())
    a.get_point(position=0)
    a.get_length()
    a.encloses(point=vtl.Point2D())
    print(type(a.end_points_))
    a[0].x = 5
    a.end_points_[1].y=4
    print(tuple(a.end_points_))
    print(a)

def test_line3d():
    a = vtl.Line3D()
    b = vtl.Line3D(p0=vtl.Point3D(), p1=vtl.Point3D())
    a.set(p0=vtl.Point3D(), p1=vtl.Point3D())
    a.get_intersection(vector=vtl.Vector2D())
    a.get_point(position=0)
    a.get_length()
    print(a.end_points)
    print(a)

test_line2d()
