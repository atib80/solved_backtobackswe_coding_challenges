/*
Add binary strings

Given two strings s1 and s2 consisting of only ones and zeros, return a string
representing the sum of s1 and s2 when they are considered as binary numbers.

Example #1:
Input: s1 = "101", s2 = "1"
Output: "110"
Explanation: In base 10, “101” represents 5, and “1” represents 1. Their sum is
6, which is “110” in binary.

Note:  Neither s1 nor s2 have any leading zeros. The returned string should not
have any leading zeros either.
*/

#include <iostream>
#include <string>
#include <utility>

using std::cbegin;
using std::cout;
using std::move;
using std::string;

class Solution {
 public:
  // asymptotic time complexity:  O(n), where n is max(s1.length(), s2.length())
  // asymptotic space complexity: O(1)
  string addBinaryStrings(string s1, string s2) const {
    if (s1.empty()) {
      return !s2.empty() ? s2 : "0";
    }

    if (s2.empty()) {
      return !s1.empty() ? s1 : "0";
    }

    auto& longer_bin_number = s1.length() > s2.length() ? s1 : s2;
    auto& shorter_bin_number = !(s1.length() > s2.length()) ? s1 : s2;

    int carry{};

    for (int i = longer_bin_number.length() - 1,
             j = shorter_bin_number.length() - 1;
         j >= 0; --i, --j) {
      const int bit_result =
          (longer_bin_number[i] - '0') + (shorter_bin_number[j] - '0') + carry;
      carry = bit_result >> 1;
      longer_bin_number[i] = bit_result % 2 + '0';
    }

    for (int i = longer_bin_number.length() - shorter_bin_number.length() - 1;
         i >= 0; --i) {
      const int bit_result = (longer_bin_number[i] - '0') + carry;
      carry = bit_result >> 1;
      longer_bin_number[i] = bit_result % 2 + '0';
    }

    if (0 != carry)
      longer_bin_number.insert(cbegin(longer_bin_number), 1, '1');

    return move(longer_bin_number);
  }
};

int main() {
  Solution s;

  cout << "s.addBinaryStrings(\"101\", \"1\") -> "
       << s.addBinaryStrings("101", "1") << '\n';  // expected output: "110"
  cout << "s.addBinaryStrings(\"111\", \"111\") -> "
       << s.addBinaryStrings("111", "111") << '\n';  // expected output: "1110"

  return 0;
}
