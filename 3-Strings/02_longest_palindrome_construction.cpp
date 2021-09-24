/*
Longest Palindrome Construction
Given a string, determine the length of the longest possible palindromic string
that can be constructed using the characters of the string.

Example 1:
Input: "aabbc"
Output: 5
Explanation: The longest palindromes possible are {"abcba", "bacab"}.

Example 2:
Input: "abbcccd"
Output: 5
Explanation: The original string length is 7, but the longest palindromes are
{"cbcbc",  "bcccb"}; 'a' and 'd' were not used.

Example 3:
Input: "aA"
Output: 1
Explanation: Since the input is case-sensitive, the longest palindromes are
{"a", "A"}.

Example 4:
Input: "xyz"
Output: 1

Example 5:
Input: "ccc"
Output: 3
*/

#include <iostream>
#include <cmath>
#include <string>

using std::abs;
using std::cout;
using std::string;

class Solution {
 public:
  int longestPalindrome(const string& s) const noexcept {
    int character_count[256]{};
    int number_of_odd_characters{};
    int max_palindrome_length{};

    for (const char ch : s) {
      const size_t index = ch >= 0 ? ch : 256 - abs(ch);
      if ((character_count[index] & 1) == 1) {
        --number_of_odd_characters;
        max_palindrome_length += 2;
      } else {
        ++number_of_odd_characters;
      }

      ++character_count[index];
    }

    return max_palindrome_length + (number_of_odd_characters > 0 ? 1 : 0);
  }
};

int main() {
  Solution s;

  cout << "s.longestPalindrome(\"aabbc\") -> " << s.longestPalindrome("aabbc")
       << '\n';  // expected output: 5
  cout << "s.longestPalindrome(\"abbcccd\") -> "
       << s.longestPalindrome("abbcccd") << '\n';  // expected output: 5
  cout << "s.longestPalindrome(\"aA\") -> " << s.longestPalindrome("aA")
       << '\n';  // expected output: 1
  cout << "s.longestPalindrome(\"xyz\") -> " << s.longestPalindrome("xyz")
       << '\n';  // expected output: 1
  cout << "s.longestPalindrome(\"ccc\") -> " << s.longestPalindrome("ccc")
       << '\n';  // expected output: 3

  return 0;
}
