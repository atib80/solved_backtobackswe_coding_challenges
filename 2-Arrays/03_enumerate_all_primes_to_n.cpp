/*
Enumerate All Primes To N
Given an integer value n, enumerate all prime numbers from 1 to n (exclusive)
and return the list with the enumeration.

Example 1:
Input: 1
Output: []
Explanation: 1 is not a prime number

Example 2:
Input: 23
Output: [2, 3, 5, 7, 11, 13, 17, 19]

Constraints:
n >= 1
*/

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

template <typename ForwardIteratorType>
void print_sequence(ForwardIteratorType first,
                    ForwardIteratorType last,
                    ostream& os) {
  if (first == last) {
    os << "[ ]";
  } else {
    os << '[';
    --last;
    while (first != last) {
      os << *first << ", ";
      ++first;
    }
    os << *first << ']';
  }
}

class Solution {
 public:
  vector<int> enumeratePrimes(int n) const {
    n = abs(n);

    if (n < 2)
      return {};

    vector<int> prime_numbers{2};

    for (int i{3}; i < n; i += 2) {
      if (i % 2 == 0)
        continue;

      const int highest_factor{static_cast<int>(sqrt(i)) + 1};
      bool is_prime{true};
      for (int64_t j{3}; j < highest_factor; j += 2) {
        if (i % j == 0) {
          is_prime = false;
          break;
        }
      }

      if (is_prime)
        prime_numbers.emplace_back(i);
    }

    return prime_numbers;
  }
};

int main() {
  Solution s;

  const vector<int> sequence1{s.enumeratePrimes(1)};
  print_sequence(cbegin(sequence1), cend(sequence1),
                 cout);  // expected output: []
  cout << '\n';
  cout << "*******************************************************\n";

  const vector<int> sequence2{s.enumeratePrimes(23)};
  print_sequence(cbegin(sequence2), cend(sequence2),
                 cout);  // expected output: [2, 3, 5, 7, 11, 13, 17, 19]
  cout << '\n';
  cout << "*******************************************************\n";

  return 0;
}
