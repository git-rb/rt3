
#include <string_view>
#include <source_location>
#include <iostream>
#include <format>

std::string_view& current_test() {
  static std::string_view test_name;
  return test_name;
}
void test(std::string_view test_name, auto test_func) {
  current_test() = test_name;
  test_func();
}
void check(bool test, std::source_location loc = std::source_location::current()) {
  if (!test)
    std::cout << std::format("{}:{}:{}: Check failed in test \"{}\"\n", loc.file_name(), loc.line(), loc.column(), current_test());
}

int main() {

   

}
