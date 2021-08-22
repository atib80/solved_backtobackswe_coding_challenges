/*
Power of Four
Given a non-negative integer input, return true if input is a power of 4. Return false otherwise.

Example #1:
Input: 16
Output: true
Explanation: The number 16 is a power of four. (4^2)

Example #2:
Input: 8
Output: false
Explanation: The number 8 is not a power of four. The exponent would be 3/2 which is not whole.

Constraints: Your solution should run in O(1) time.
*/

#include <iostream>
#include <unordered_set>

using std::cout;
using std::boolalpha;

class Solution {
  public:
    bool powerOfFour(const int input) const noexcept {

      if (input <= 0)
        return false;

      for (size_t i{}; i < sizeof(int) * 8; i+=2) {
        if ((input & ~(1 << i)) == 0)
          return true;
      }

      return false;

    }

    bool powerOfFour_v2(const int input) const noexcept {

      return (input != 0) && ((input & (input - 1)) == 0) && ((input & 0x55555555) != 0);

    }

    bool powerOfFour_v3(const int input) const noexcept {

      const std::unordered_set<int> powers_of_four{1, 1 << 2, 1 << 4, 1 << 6, 1 << 8, 1 << 10, 1 << 12, 1 << 14, 1 << 16, 1 << 18, 1 << 20, 1 << 22, 1 << 24 , 1 << 26, 1 << 28, 1 << 30};

      return powers_of_four.find(input) != std::cend(powers_of_four);
    }
};



int main() {
  Solution s;

  cout << boolalpha;
  cout << "s.powerOfFour_v3(0) -> "    << s.powerOfFour_v3(0) << '\n';    // expected output: false
  cout << "s.powerOfFour_v3(1) -> "    << s.powerOfFour_v3(1) << '\n';    // expected output: true
  cout << "s.powerOfFour_v3(16) -> "   << s.powerOfFour_v3(16) << '\n';   // expected output: true
  cout << "s.powerOfFour_v3(8) -> "    << s.powerOfFour_v3(8) << '\n';    // expected output: false
  cout << "s.powerOfFour_v3(32) -> "   << s.powerOfFour_v3(32) << '\n';   // expected output: false
  cout << "s.powerOfFour_v3(48) -> "   << s.powerOfFour_v3(48) << '\n';   // expected output: false
  cout << "s.powerOfFour_v3(64) -> "   << s.powerOfFour_v3(64) << '\n';   // expected output: true
  cout << "s.powerOfFour_v3(128) -> "  << s.powerOfFour_v3(128) << '\n';  // expected output: false
  cout << "s.powerOfFour_v3(256) -> "  << s.powerOfFour_v3(256) << '\n';  // expected output: true
  cout << "s.powerOfFour_v3(1024) -> " << s.powerOfFour_v3(1024) << '\n'; // expected output: true

  return 0;
}
