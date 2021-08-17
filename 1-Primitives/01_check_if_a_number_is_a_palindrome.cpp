#include <cmath>
#include <iostream>

class Solution {
 public:
  bool isPalindrome(int x) {
    if (x < 0)
      return false;

    if (x < 10)
      return true;

    const size_t number_of_digits = static_cast<size_t>(std::log10(x)) + 1;

    int mask{static_cast<int>(std::pow(10, number_of_digits - 1))};

    for (size_t i{}; i < number_of_digits / 2; ++i) {
      if (x / mask != x % 10)
        return false;

      x %= mask;
      x /= 10;
      mask /= 100;
    }

    return true;
  }
};

int main() {
  Solution s;

  std::cout << std::boolalpha << "s.isPalindrome(9232) -> "
            << s.isPalindrome(9232) << '\n';  // expected output: false
  std::cout << "s.isPalindrome(12321) -> " << s.isPalindrome(12321)
            << '\n';  // expected output: true
  std::cout << "s.isPalindrome(1) -> " << s.isPalindrome(1)
            << '\n';  // expected output: true
  std::cout << "s.isPalindrome(-121) -> " << s.isPalindrome(-121)
            << '\n';  // expected output: false
  std::cout << "s.isPalindrome(240) -> " << s.isPalindrome(240)
            << std::noboolalpha << '\n';  // expected output: false

  return 0;
}
