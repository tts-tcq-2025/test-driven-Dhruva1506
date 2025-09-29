#include "StringCalculator.h"
#include <iostream>
#include <cassert>

void test_empty_string_returns_zero() {
  StringCalculator calc;
  assert(calc.add("") == 0);
}

void test_single_number() {
  StringCalculator calc;
  assert(calc.add("1") == 1);
}

void test_two_numbers_comma() {
  StringCalculator calc;
  assert(calc.add("1,2") == 3);
}

void test_multiple_numbers_newline() {
  StringCalculator calc;
  assert(calc.add("1\n2,3") == 6);
}

void test_custom_single_char_delimiter() {
  StringCalculator calc;
  assert(calc.add("//;\n1;2") == 3);
}

void test_ignore_numbers_greater_than_1000() {
  StringCalculator calc;
  assert(calc.add("2,1001") == 2);
}

void test_negative_numbers_throw() {
  StringCalculator calc;
  try {
    calc.add("1,-2,-3");
    assert(false);  // should not reach here
  } catch (const std::runtime_error &e) {
    std::string msg = e.what();
    assert(msg.find("-2") != std::string::npos);
    assert(msg.find("-3") != std::string::npos);
  }
}

void test_custom_delimiter_any_length() {
  StringCalculator calc;
  assert(calc.add("//[***]\n1***2***3") == 6);
}

int main() {
  test_empty_string_returns_zero();
  test_single_number();
  test_two_numbers_comma();
  test_multiple_numbers_newline();
  test_custom_single_char_delimiter();
  test_ignore_numbers_greater_than_1000();
  test_negative_numbers_throw();
  test_custom_delimiter_any_length();

  std::cout << "All tests passed!" << std::endl;
  return 0;
}
