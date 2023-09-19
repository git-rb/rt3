
namespace sim_test {
	using sl = std::source_location;
	std::string_view current_test; //global
	constexpr auto fail_str = "{}:{}:{}: Check failed in test\"{}\"\n";
	auto fmt_fail(sl l) {
		return std::format(fail_str, l.file_name(),
				l.line(), l.column(), current_test);
	}

	void test(std::string_view desc, auto f) {
		current_test = desc;
		f();
	}
	void check(bool test, sl loc = sl::current()) {
		if (!test) std::cout << fmt_fail(loc);
	}
}

