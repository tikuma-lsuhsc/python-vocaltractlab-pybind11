import vocaltractlab as vtl
from math import pi

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
a.scalar_product(b) == a@b
