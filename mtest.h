#pragma once

#include <filesystem>
#include <functional>
#include <source_location>
#include <string>
#include <vector>
#include <utility>

namespace detail {

struct TestException : std::exception {
  std::string err;

  TestException(std::string err) : err(err) {}

  const char* what() const noexcept override {
    return err.c_str();
  }
};

void addTest(std::string_view name, void (*f)());

} // namespace detail

#define MASSERT(expr) \
  do { \
    auto loc = std::source_location::current(); \
    if (!static_cast<bool>((expr))) { \
      auto p = std::filesystem::path(std::string{loc.file_name()}); \
      throw detail::TestException( \
        std::string{ p.filename() } + \
        ":" + \
        std::to_string(loc.line()) \
      ); \
    } \
  } while (false)

#define MTEST(name) \
  void Test_ ## name(); \
  namespace detail { \
    struct Register_ ## name { \
      Register_ ## name() { \
        detail::addTest(#name, & Test_ ## name); \
      } \
    } name##Register; \
  } \
  void Test_ ## name()

void runTests();
