
#include <string_view>
#include <source_location>
#include <iostream>
#include <format>

#include "rt.h"
#include "simtest.h"

sim_test::sl loc;

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

	test("a tuple with w=0.0 is a point", [] {
				auto a = tuple {4.3, -4.2, 3.1, 0.0};
				check(is_vector(a));
			});

}
