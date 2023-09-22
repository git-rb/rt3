//simtest.h - testing suite
//

#ifndef SIMTEST_H
#define SIMTEST_H

#include <source_location>
#include <string_view>
#include <format>
#include <iostream>

namespace simtest {

	using loc_t = std::source_location;
	std::string_view current_test; 
	constexpr auto fail_str = "{}:{}:{}: Check failed in test \"{}\"\n";

	auto fmt_fail(loc_t l) {
		return std::format(fail_str, l.file_name(),
				l.line(), l.column(), current_test);
	}

	void test(std::string_view desc, auto f) {
		current_test = desc;
		f();
	}

	void check(bool test, loc_t l = loc_t::current()) {
		if (!test) std::cout << fmt_fail(l);
	}
}

#endif
