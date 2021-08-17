#include <cmath>
#include <iostream>

#include <cmath>

class Solution {
  public:
    bool powerOfTwo(int input) const {

      return input > 0 && ((input & (input - 1)) == 0);

    }

     bool powerOfTwo_v2(int input) const {

      constexpr double dbl_delta{0.0000000000001};

      const double result = std::log2(input);
      const double rounded_result = std::round(result);
      return std::abs(result - rounded_result) <= dbl_delta;

    }

     bool powerOfTwo_v3(int input) const {

       if (1 == input)
        return true;

       while (input != 0) {
         if ((input & 1) && (input > 2)) {
          return false;
         }

          input >>= 1;
       }

       return true;

    }
};

int main() {

  Solution s;

  std::cout << std::boolalpha << "s.powerOfTwo_v3(1) -> " << s.powerOfTwo_v3(1) << '\n'; // expected output: true
  std::cout << "s.powerOfTwo_v3(16) -> " << s.powerOfTwo_v3(16) << '\n'; // expected output: true
  std::cout << "s.powerOfTwo_v3(17) -> " << s.powerOfTwo_v3(17) << '\n'; // expected output: false
  std::cout << "s.powerOfTwo_v3(134217730) -> " << s.powerOfTwo_v3(134217730) << '\n'; // expected output: false

  return 0;
}
