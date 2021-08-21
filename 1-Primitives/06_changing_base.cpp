/*
Changing Base
Given an integer (represented as a string) under base b1, convert it to base b2.

Example 1:
Input: ("12", 10, 2)
Output: "1100"
Explanation: We are converting "12" which is under base 10 (decimal) to base 2
(binary)

Example 2:
Input: ("123", 4, 10)
Output: "27"
Explanation: We are converting "123" which is under base 4 (quaternary) to base
10

Example 3:
Input: ("123", 4, 16)
Output: "1B"
Explanation: Convert "123" from base 4 to 16

Example 4:
Input: ("123", 10, 10)
Output: "123"

Constraints:
2 <= b1 <= 36
2 <= b2 <= 36
For base-2 up to base-10 use the digits 0-9 to represent digits
Use the English alphabet characters A-Z in base-11 and higher
*/

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

class Solution {
 public:
  string changeBase(const string& number, const int b1, const int b2) const {
    return convert_decimal_number_to_number_base(
        get_number_in_decimal(number, b1), b2);
  }

 private:
  string convert_decimal_number_to_number_base(int decimal_number,
                                               const int base) const {
    string number_in_base;
    number_in_base.reserve(64);

    while (0 != decimal_number) {
      const int remainder = decimal_number % base;
      decimal_number /= base;
      number_in_base.push_back(get_correct_digit_char(remainder));
    }

    reverse(begin(number_in_base), end(number_in_base));
    return number_in_base;
  }

  int get_number_in_decimal(const string& number, const int number_base) const {
    int number_in_decimal{};
    for (size_t i{}; i < number.length(); ++i) {
      number_in_decimal *= number_base;
      number_in_decimal += get_correct_digit_value(number[i]);
    }

    return number_in_decimal;
  }

  inline int get_correct_digit_value(const char digit_char) const {
    if (digit_char >= '0' && digit_char <= '9')
      return static_cast<int>(digit_char - '0');

    if (digit_char >= 'A' && digit_char <= 'Z')
      return static_cast<int>(10 + (digit_char - 'A'));

    if (digit_char >= 'a' && digit_char <= 'z')
      return static_cast<int>(10 + (digit_char - 'a'));

    return 0;
  }

  inline char get_correct_digit_char(const int digit_value) const {
    return digit_value >= 0 && digit_value <= 9
               ? static_cast<char>('0' + digit_value)
               : (digit_value >= 10 && digit_value <= 36
                      ? static_cast<char>('A' + (digit_value - 10))
                      : '0');
  }
};

int main() {
  Solution s;

  std::cout << R"(s.changeBase("12", 10, 2) -> )" << s.changeBase("12", 10, 2)
            << '\n';  // expected output: "1100"
  std::cout << R"(s.changeBase("123", 4, 10) -> )" << s.changeBase("123", 4, 10)
            << '\n';  // expected output: "27"
  std::cout << R"(s.changeBase("123", 4, 16) -> )" << s.changeBase("123", 4, 16)
            << '\n';  // expected output: "1B"
  std::cout << R"(s.changeBase("123", 10, 10) -> )"
            << s.changeBase("123", 10, 10) << '\n';  // expected output: "123"

  return 0;
}
