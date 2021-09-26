/*
Given a string s and an integer value rows return the "zigzag" encoding of s
read off row-by-row.

Example 1:
Input:
s = "YELLOWPINK"
rows = 4

Output: "YPEWILONLK"
Explanation: There are 4 rows in the zigzag formatted string.

Y     P    (row 1: "YP")
E   W I    (row 2: "EWI")
L O   N    (row 3: "LON")
L     K    (row 4: "LK")

Example 2:
Input:
s = "REDBLUEBLACK"
rows = 2

Output: "RDLELCEBUBAK"
Explanation: There are 2 rows in the zigzag formatted string.

R D L E L C    (row 1: "RDLELC")
E B U B A K    (row 2: "EBUBAK")

Example 3:
Input:
s = "REDBLUEBLACK"
rows = 1

Output: "REDBLUEBLACK"
Explanation:

R E D B L U E B L A C K    (row 1: "REDBLUEBLACK")

Constraints:
rows > 0
*/

#include <iostream>
#include <string>

using std::cout;
using std::string;

class Solution {
 public:
  /*
  asymptotic time complexity:  O(n), where 'n' is the length of input string 's'
  asymptotic space complexity: O(1)
  */
  string zigzag(const string& s, const size_t rows) const {
    if (rows <= 1 || s.length() <= 2)
      return s;

    string result;
    result.reserve(s.length());

    const size_t longest_offset{2 * (rows - 1)};

    for (size_t i{}, offset{longest_offset}; i < rows; ++i, offset -= 2) {
      bool is_bigger_step = false;
      if (0 == offset)
        offset = longest_offset;
      for (size_t j{i}; j < s.length();
           j += is_bigger_step ? offset : longest_offset - offset) {
        result.push_back(s[j]);
        is_bigger_step = longest_offset == offset ? true : !is_bigger_step;
      }
    }

    return result;
  }
};

int main() {
  Solution s;

  cout << "s.zigzag(\"YELLOWPINK\", 4) -> " << s.zigzag("YELLOWPINK", 4)
       << '\n';  // expected output: "YPEWILONLK"
  cout << "s.zigzag(\"REDBLUEBLACK\", 2) -> " << s.zigzag("REDBLUEBLACK", 2)
       << '\n';  // expected output: "RDLELCEBUBAK"
  cout << "s.zigzag(\"REDBLUEBLACK\", 1) -> " << s.zigzag("REDBLUEBLACK", 1)
       << '\n';  // expected output: "REDBLUEBLACK"

  return 0;
}
