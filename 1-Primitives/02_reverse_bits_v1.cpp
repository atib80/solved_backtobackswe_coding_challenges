#include <iostream>

using namespace std;

// asymptotic time complexity: O(n)
// asymptotic space complexity: O(1)

class Solution {
 public:
  int reverseBits(int input) const {
    int reversed_number{};

    while (input != 0) {
      reversed_number <<= 1;
      reversed_number |= (input & 1);
      input >>= 1;
    }

    return reversed_number;
  }
};

int main() {
  Solution s;

  std::cout << "s.reverseBits(1) -> " << s.reverseBits(1)
            << '\n';  // expected output: 1
  std::cout << "s.reverseBits(4) -> " << s.reverseBits(4)
            << '\n';  // expected output: 1
  std::cout << "s.reverseBits(10) -> " << s.reverseBits(10)
            << '\n';  // expected output: 5
  std::cout << "s.reverseBits(5) -> " << s.reverseBits(5)
            << '\n';  // expected output: 5
  std::cout << "s.reverseBits(240) -> " << s.reverseBits(240)
            << '\n';  // expected output: 15

  return 0;
}
