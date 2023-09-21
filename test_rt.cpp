
#include "rt.h"
#include "simtest.h"


int main() {
	using namespace rt;
	using namespace simtest;

	test("A tuple with w=1.0 is a point", [] {
			auto a = tuple {4.3, -4.2, 3.1, 1.0};
			check(a.x == 4.3);
			check(a.y == -4.2);
			check(a.z == 3.1);
			check(a.w == 1.0);
			check(is_point(a));
		});

	test("a tuple with w=0.0 is a vector", [] {
			auto a = tuple {4.3, -4.2, 3.1, 0.0};
			check(is_vector(a));
		});

	test("point() creates tuples with w=1.0", [] {
			auto p = point(4, -4, 3);
			check(p == tuple {4, -4, 3, 1});
		});

	test("vector() creates tuple with w=0.0", [] {
			auto v = vector(4, -4, 3);
			check(v == tuple {4, -4, 3, 0});
		});
	
	test("adding tuples", [] {
			auto t1 = tuple(3, -2, 5, 1);
			auto t2 = tuple(-2, 3, 1, 0);
			check(t1 + t2 == tuple(1, 1, 6, 1));
		});

	test("Subtracting two points", [] {
			auto p1 = point(3, 2, 1);
			auto p2 = point(5, 6, 7);
			check(p1 - p2 == vector(-2, -4, -6));
		});

	test("Subtracting a vector from a point", [] {
			auto p = point(3, 2, 1);
			auto v = vector(5, 6, 7);
			check(p - v == point(-2, -4, -6));
		});
	
	test("Subtracting two vectors", [] {
			auto v1 = vector(3, 2, 1); 
			auto v2 = vector(5, 6, 7);
		});

	test("Subtracting a vector from zero vector", [] {
			auto zero = vector(0, 0, 0);
			auto v = vector(1, -2, 3);
			check(zero - v == vector(-1, 2, -3));
		});

	test("Negating a tuple", [] {
			auto a = tuple {1, -2, 3, -4};
			check(-a == tuple(-1, 2, -3, 4));
		});

	test("Multiplying a tuple by a scalar", [] {
			auto a = tuple(1, -2, 3, -4);
			check(a * 3.5 == tuple(3.5, -7, 10.5, -14));
		});

	test("Multiplying a tuple by a fraction", [] {
			check(tuple{1, -2, 3, -4} * 0.5 == tuple {0.5, -1, 1.5, -2});
		});

	test("Dividing tuple by scalar", [] {
			auto a = tuple {1, -2, 3, -4};
			check(a/2 == tuple {0.5, -1, 1.5, -2});
		});

	test("Computing magnitude of vector(1, 0, 0)", [] {
			auto v = vector(1, 0, 0);
			check(magnitude(v) == 1.0);
		});

	test("Computing magnitude of vector(0, 1, 0)", [] {
			auto v = vector(0, 1, 0);
			check(magnitude(v) == 1.0);
		});

	test("Computing magnitude of vector(0, 0, 1)", [] {
			auto v = vector(0, 0, 1);
			check(magnitude(v) == 1.0);
		});

	test("Computing magnitude of vector(1, 2, 3)", [] {
			auto v = vector(1, 2, 3);
			check(magnitude(v) == std::sqrt(14));
		});

	test("Computing magnitude of vector(-1, -2, -3)", [] {
			auto v = vector(1, 2, 3);
			check(magnitude(v) == std::sqrt(14));
		});

	test("Normalizing vector (4, 0, 0) gives (1, 0 ,0)", [] {
			auto v = vector(4, 0, 0);
			check(normalize(v) == vector(1, 0, 0));
		});

	test("Normalizing vector (1, 2, 3)", [] {
			auto v = vector(1, 2, 3);
			auto f = std::sqrt(14);
			check(normalize(v) == vector(1 / f, 2 / f, 3 / f));
		});

	test("Magnitude of a normalized vector", [] {
			auto v = vector(1, 2, 3);
			auto norm = normalize(v);
			check(magnitude(norm) == 1);
		});

	test("Dot product of two tuples", [] {
			auto a = vector(1, 2, 3);
			auto b = vector(2, 3, 4);
			check(dot(a, b) == 20);
		});

	test("Cross product of two vectors", [] {
			auto a = vector(1, 2, 3);
			auto b = vector(2, 3, 4);
			check(cross(a, b) == vector(-1, 2, -1));
			check(cross(b, a) == vector(1, -2, 1));
		});

	test("Colors are tuples", [] {
			auto c = color {-0.5, 0.4, 1.7};
			check(c.r == -0.5);
			check(c.g == 0.4);
			check(c.b == 1.7);
		});
	test("Adding color", [] {
			auto c1 = color {0.9, 0.6, 0.75};
			auto c2 = color {0.7, 0.1, 0.25};
			check(c1 + c2 == color {1.6, 0.7, 1.0});
			color r = c1 + c2;
			check(r == color {1.6, 0.7, 1.0});
		});
	test("Subtracting colors", [] {
			auto c1 = color {0.9, 0.6, 0.75};
			auto c2 = color {0.7, 0.1, 0.25};
			check(c1 - c2 == color {0.2, 0.5, 0.5});
		});
	test("Multiplying a color by a scalar", [] {
			auto c = color {0.2, 0.3, 0.4};
			check(c * 2 == color {0.4, 0.6, 0.8});
		});
	test("Multiplying a colors", [] {
			auto c1 = color {1, 0.2, 0.4};
			auto c2 = color {0.9, 1, 0.1};
			check(c1 * c2 == color {0.9, 0.2, 0.04});
		});

}
