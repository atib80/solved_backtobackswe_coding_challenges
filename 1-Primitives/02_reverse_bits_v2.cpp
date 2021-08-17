#include <cmath>
#include <iostream>

// asymptotic time complexity: O(n)
// asymptotic space complexity: O(1)

using namespace std;

class Solution {
 public:
  int reverseBits(int input) const {
    if (0 == input)
      return 0;

    size_t lsb{};
    size_t msb = static_cast<size_t>(log2(input));

    while (lsb < msb) {
      const int lb = (input & (1 << msb)) >> msb;
      const int ub = (input & (1 << lsb)) >> lsb;
      input = lb != 0 ? input | (lb << lsb) : input & ~(1 << lsb);
      input = ub != 0 ? input | (ub << msb) : input & ~(1 << msb);
      ++lsb;
      --msb;
    }

    return input;
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
