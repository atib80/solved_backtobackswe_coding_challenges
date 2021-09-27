/*
Valid Palindrome
Given a string s, determine whether s is a palindrome while only considering
alphanumeric characters and ignoring case.

Example 1:
Input: s = "Race Car"
Output: true
Explanation: When we ignore case and only consider alphanumeric characters, the
string "Race Car" is equivalent to "racecar," which is a palindrome.
*/

#include <algorithm>
#include <array>
#include <iostream>
#include <string>

using namespace std;

class Solution {
 public:
  Solution() noexcept {
    fill(begin(valid_characters), end(valid_characters), 0);
    for (char i{'A'}, j{'a'}; i <= 'Z'; ++i, ++j) {
      valid_characters[(size_t)i] = j;
      valid_characters[(size_t)j] = j;
    }
  }

  // asymptotic time complexity:  O(n)
  // asymptotic space complexity: O(1)
  bool validPalindrome(const string& s) const noexcept {
    if (s.empty())
      return false;

    size_t i{}, j{s.length() - 1};

    while (i < j) {
      if (0 == valid_characters[(size_t)s[i]]) {
        ++i;
      } else if (0 == valid_characters[(size_t)s[j]]) {
        --j;
      } else if (valid_characters[(size_t)s[i]] !=
                 valid_characters[(size_t)s[j]]) {
        return false;
      } else {
        ++i;
        --j;
      }
    }

    return true;
  }

 private:
  array<char, 256> valid_characters;
};

int main() {
  Solution s;

  cout << boolalpha << "s.validPalindrome(\"Race Car\") -> "
       << s.validPalindrome("Race Car") << '\n';  // expected output: true
  cout << boolalpha << "s.validPalindrome(\"robot\") -> "
       << s.validPalindrome("robot") << '\n';  // expected output: false

  return 0;
}
