/*
Power of Four
Given a non-negative integer input, return true if input is a power of 4. Return
false otherwise.

Example #1:
Input: 16
Output: true
Explanation: The number 16 is a power of four. (4^2)

Example #2:
Input: 8
Output: false
Explanation: The number 8 is not a power of four. The exponent would be 3/2
which is not whole.

Constraints: Your solution should run in O(1) time.
*/

#include <array>
#include <iostream>
#include <unordered_set>

using std::boolalpha;
using std::cout;

class Solution {
 public:
  bool powerOfFour(const int input) const noexcept {
    if (input <= 0)
      return false;

    for (size_t i{}; i < sizeof(int) * 8; i += 2) {
      if ((input & ~(1 << i)) == 0)
        return true;
    }

    return false;
  }

  bool powerOfFour_v2(const int input) const noexcept {
    return ((input & (input - 1)) == 0) && ((input & 0x55555555) != 0);
  }

  static constexpr std::array<int, sizeof(int) * 4>
  generate_all_powers_of_four() noexcept {
    std::array<int, sizeof(int) * 4> powers_of_four{};

    for (size_t i{}; i < sizeof(int) * 8; i += 2)
      powers_of_four[i / 2] = 1 << i;

    return powers_of_four;
  }

  bool powerOfFour_v3(const int input) const {
    constexpr std::array<int, sizeof(int) * 4> seq_of_powers_of_four{
        generate_all_powers_of_four()};

    const std::unordered_set<int> powers_of_four(seq_of_powers_of_four.cbegin(),
                                                 seq_of_powers_of_four.cend());

    return powers_of_four.find(input) != std::cend(powers_of_four);
  }
};

int main() {
  Solution s;

  cout << boolalpha;
  cout << "s.powerOfFour_v2(0) -> " << s.powerOfFour_v2(0)
       << '\n';  // expected output: false
  cout << "s.powerOfFour_v2(1) -> " << s.powerOfFour_v2(1)
       << '\n';  // expected output: true
  cout << "s.powerOfFour_v2(16) -> " << s.powerOfFour_v2(16)
       << '\n';  // expected output: true
  cout << "s.powerOfFour_v2(8) -> " << s.powerOfFour_v2(8)
       << '\n';  // expected output: false
  cout << "s.powerOfFour_v2(32) -> " << s.powerOfFour_v2(32)
       << '\n';  // expected output: false
  cout << "s.powerOfFour_v2(48) -> " << s.powerOfFour_v2(48)
       << '\n';  // expected output: false
  cout << "s.powerOfFour_v2(64) -> " << s.powerOfFour_v2(64)
       << '\n';  // expected output: true
  cout << "s.powerOfFour_v2(128) -> " << s.powerOfFour_v2(128)
       << '\n';  // expected output: false
  cout << "s.powerOfFour_v2(256) -> " << s.powerOfFour_v2(256)
       << '\n';  // expected output: true
  cout << "s.powerOfFour_v2(1024) -> " << s.powerOfFour_v2(1024)
       << '\n';  // expected output: true

  return 0;
}
