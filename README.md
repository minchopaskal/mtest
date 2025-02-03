# MTest

A lightweight unit testing framework intended for use in small projects for which dependency on `gtest` or similar will be an overkill.

## Usage

Add the `mtest.{h,cpp}` files in your project, preferably under a directory specific for testing - f.e `test`.

Define your tests using the `MTEST` macro and make sure to link the source files they reside in with your test project. Then in the `main` function of said project call `runTests()`.

Tests are defined in the following manner:
```c++
MTEST(testName) {
  // test body ...
  MASSERT(...)
  // ...
}
```

## Notes

Currently only one type of assertion is supported - `MASSERT(boolean expression)`.

All tests are run sequentially in the order of their definition. A test is aborted whenever an assertion fails.
