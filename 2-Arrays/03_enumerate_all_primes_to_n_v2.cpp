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

asymptotic time complexity: O(n * lglgn)
asymptotic space complexity: O(n)
*/

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
  vector<size_t> enumeratePrimes(size_t n) const {
    if (n < 2U)
      return {};

    vector<bool> is_prime(n, true);
    is_prime[0] = is_prime[1] = false;
    vector<size_t> prime_numbers;

    for (size_t i{2}; i < n; ++i) {
      if (is_prime[i]) {
        prime_numbers.emplace_back(i);
        for (size_t j{i + i}; j < n; j += i) {
          is_prime[j] = false;
        }
      }
    }

    return prime_numbers;
  }
};

int main() {
  Solution s;

  const vector<size_t> sequence1{s.enumeratePrimes(1)};
  print_sequence(cbegin(sequence1), cend(sequence1),
                 cout);  // expected output: []
  cout << '\n';
  cout << "*******************************************************\n";

  const vector<size_t> sequence2{s.enumeratePrimes(23)};
  print_sequence(cbegin(sequence2), cend(sequence2),
                 cout);  // expected output: [2, 3, 5, 7, 11, 13, 17, 19]
  cout << '\n';
  cout << "*******************************************************\n";

  return 0;
}
