/*
Given an array of n integers, return all unique triplets [a,b,c] in the array
such that a + b + c = 0.

Example 1:
Input:
[-3, -1, 1, 0, 2, 10, -2, 8]

Output:
[
 [-3, 1, 2],
 [-2, 0, 2],
 [-1, 0, 1]
]

Example 2:
Input:
[-5, 3, 2, 0, 1, -1, -5, 3, 2]

Output:
[
 [-5, 2, 3],  # The same triplet is not duplicated.
 [-1, 0, 1]
]

Example 3:
Input:
[1, 2, 3, 4]

Output:
[] # No triplets found that sum to zero.

Note
Duplicate triplets are not allowed in the output.
*/

#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <utility>
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
  vector<vector<int>> threeSum(vector<int>& array) const {
    const size_t arr_size{array.size()};
    if (arr_size < 3U)
      return {};

    vector<vector<int>> all_three_sum_sequences{};
    unordered_set<int> visited_numbers{};
    sort(begin(array), end(array));

    for (size_t i{}; i < arr_size - 2; ++i) {
      if (1U == visited_numbers.count(array[i]))
        continue;

      visited_numbers.emplace(array[i]);

      size_t left{i + 1}, right{arr_size - 1};

      while (left < right) {
        const int two_sum{array[left] + array[right]};

        if (two_sum == -array[i]) {
          all_three_sum_sequences.push_back(
              {array[i], array[left], array[right]});
          break;
        } else if (two_sum > -array[i]) {
          --right;
        } else {
          ++left;
        }
      }
    }
    return all_three_sum_sequences;
  }
};

int main() {
  Solution s;

  vector<int> seq1{-3, -1, 1, 0, 2, 10, -2, 8};

  const vector<vector<int>> all_sequences1{s.threeSum(seq1)};

  for (const vector<int>& sequence : all_sequences1) {
    print_sequence(cbegin(sequence), cend(sequence), cout);
    cout << '\n';
  }

  cout << "*******************************************************\n";

  vector<int> seq2{-5, 3, 2, 0, 1, -1, -5, 3, 2};

  const vector<vector<int>> all_sequences2{s.threeSum(seq2)};

  for (const vector<int>& sequence : all_sequences2) {
    print_sequence(cbegin(sequence), cend(sequence), cout);
    cout << '\n';
  }

  cout << "*******************************************************\n";

  vector<int> seq3{1, 2, 3, 4};

  const vector<vector<int>> all_sequences3{s.threeSum(seq3)};

  for (const vector<int>& sequence : all_sequences3) {
    print_sequence(cbegin(sequence), cend(sequence), cout);
    cout << '\n';
  }

  cout << "*******************************************************\n";

  return 0;
}
