
#include <string_view>
#include <source_location>
#include <iostream>
#include <format>

#include "rt.h"
#include "simtest.h"


int main() {
	using namespace rt;
	using namespace sim_test;

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

}
