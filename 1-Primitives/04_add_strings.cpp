#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <string>

using namespace std;

class Solution {
 public:
  string addStrings(string s1, string s2) const {
    if (is_nan(s1) || is_nan(s2))
      return "NaN";

    if (is_zero(s1))
      return s2;

    if (is_zero(s2))
      return s1;

    string result{};
    result.reserve(max(s1.length(), s2.length()) + 1);

    bool is_negative_addition{};

    if ((is_negative(s1) && !is_negative(s2)) ||
        (!is_negative(s1) && is_negative(s2))) {
      const string& abs_s1{!is_negative(s1) ? s1 : abs(s1)};
      const string& abs_s2{!is_negative(s2) ? s2 : abs(s2)};

      if (abs_s1 == abs_s2)
        return "0";

      const bool is_abs_first_greater_abs_second{is_less(abs_s2, abs_s1)};
      const bool is_abs_second_greater_than_abs_first{
          !is_abs_first_greater_abs_second};

      is_negative_addition =
          (is_negative(s1) && is_abs_first_greater_abs_second) ||
          (is_negative(s2) && is_abs_second_greater_than_abs_first);

      const string& greater_number_decimal_digits{
          is_abs_first_greater_abs_second ? abs_s1 : abs_s2};

      const string& smaller_number_decimal_digits{
          !is_abs_first_greater_abs_second ? abs_s1 : abs_s2};

      size_t n{greater_number_decimal_digits.length()};
      size_t m{smaller_number_decimal_digits.length()};
      int carry{};

      while (n > 0U || m > 0U || carry != 0) {
        int sum{carry};
        carry = 0;

        if (n > 0U) {
          const size_t index{n - 1};
          const int first_operand = greater_number_decimal_digits[index] - '0';

          if (sum + first_operand < 0) {
            sum += 10 + first_operand;
            --carry;
          } else {
            sum += first_operand;
          }
          --n;
        }
        if (m > 0U) {
          const size_t index{m - 1};
          const int second_operand =
              -(smaller_number_decimal_digits[index] - '0');
          if (sum + second_operand < 0) {
            sum += 10 + second_operand;
            --carry;
          } else {
            sum += second_operand;
          }
          --m;
        }

        if (0 == carry)
          carry = sum / 10;

        result.push_back('0' + static_cast<char>(std::abs(sum) % 10));
      }
    } else {
      const size_t offset = is_negative(s1) && is_negative(s2)
                                ? (is_negative_addition = true, 1U)
                                : (is_negative_addition = false, 0U);

      size_t n{s1.length()};
      size_t m{s2.length()};
      int carry{};

      while (n > offset || m > offset || carry != 0) {
        int sum{carry};

        if (n > offset) {
          sum += s1[n - 1] - '0';
          --n;
        }
        if (m > offset) {
          sum += s2[m - 1] - '0';
          --m;
        }

        carry = sum / 10;

        const int remainder = sum % 10;

        result.push_back('0' + remainder);
      }
    }

    std::reverse(begin(result), end(result));

    const auto first_non_zero_digit_pos = result.find_first_not_of('0');

    if (first_non_zero_digit_pos != 0U) {
      if (is_negative_addition) {
        result.replace(std::cbegin(result),
                       std::cbegin(result) + first_non_zero_digit_pos, 1U, '-');
        return result;
      }

      result.erase(std::cbegin(result),
                   std::cbegin(result) + first_non_zero_digit_pos);
    }

    if (is_negative_addition)
      result.insert(std::cbegin(result), '-');

    return result;
  }

 private:
  bool is_nan(const string& decimal_number) const noexcept {
    const bool is_neg{is_negative(decimal_number)};
    const size_t offset = is_neg ? 1U : 0U;
    return decimal_number.empty() ||
           any_of(cbegin(decimal_number) + offset, cend(decimal_number),
                  [](const char ch) { return ch < '0' || ch > '9'; }) ||
           (decimal_number.length() >= 2 && '0' == decimal_number[0]) ||
           (is_neg && decimal_number.length() >= 2 && '0' == decimal_number[1]);
  }

  bool is_zero(const string& decimal_number) const noexcept {
    return !is_nan(decimal_number) && decimal_number == "0";
  }

  bool is_negative(const string& decimal_number) const noexcept {
    return !decimal_number.empty() && decimal_number[0] == '-';
  }

  string abs(const string& decimal_number) const {
    if (is_nan(decimal_number))
      return "NaN";

    if (!is_negative(decimal_number))
      return decimal_number;

    return decimal_number.substr(1);
  }

  bool is_less(const std::string& ln, const string& rn) const {
    if (!is_nan(ln) && !is_nan(rn)) {
      const size_t ln_size{ln.length()};
      const size_t rn_size{rn.length()};

      const bool is_ln_negative{is_negative(ln)};
      const bool is_rn_negative{is_negative(rn)};

      if (is_ln_negative && !is_rn_negative)
        return true;

      if (!is_ln_negative && is_rn_negative)
        return false;

      if (ln_size != rn_size) {
        if (ln_size < rn_size)
          return !is_ln_negative && !is_rn_negative;
        return is_ln_negative && is_rn_negative;
      }

      if (is_ln_negative && is_rn_negative) {
        for (size_t i{1}; i < ln_size; ++i) {
          if (ln[i] > rn[i])
            return true;
          if (ln[i] < rn[i])
            return false;
        }
      } else {
        for (size_t i{}; i < ln_size; ++i) {
          if (ln[i] < rn[i])
            return true;
          if (ln[i] > rn[i])
            return false;
        }
      }
    }

    return false;
  }
};

int main() {
  Solution s{};

  std::cout << "s.addStrings(\"123\", \"456\") -> "
            << s.addStrings("123", "456") << '\n';  // expected output: 579
  std::cout << "s.addStrings(\"-1010\", \"102\") -> "
            << s.addStrings("-1010", "102") << '\n';  // expected output: -908
  std::cout << "s.addStrings(\"1020\", \"-101\") -> "
            << s.addStrings("1020", "-101") << '\n';  // expected output: 919
  std::cout << "s.addStrings(\"-2510\", \"-103\") -> "
            << s.addStrings("-2510", "-103") << '\n';  // expected output: -2613

  return 0;
}
