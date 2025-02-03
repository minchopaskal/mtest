#include "mtest.h"

namespace detail {

std::vector<std::pair<std::string, void(*)()>> tests;

void addTest(std::string_view name, void (*f)()) {
  tests.push_back({std::string{name}, f});
}

} // namespace detail

void runTests() {
  std::vector<std::string> failed;
  for (auto& [name, test] : detail::tests) {
    try {
      printf("Running test %s...\n", name.c_str());
      test();
    } catch (const detail::TestException &e) {
      failed.push_back(name);
      printf("Assertion failed in test `%s`: %s\n", name.c_str(), e.what());
    }
  }

  if (failed.empty()) {
    printf("All tests passed!\n");
    return;
  }

  printf("Failed tests:\n");
  for (auto& name : failed) {
    printf("\t* %s\n", name.c_str());
  }
}
