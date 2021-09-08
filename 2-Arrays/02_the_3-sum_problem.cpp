#include <algorithm>
#include <iostream>
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

    vector<vector<int>> correct_three_sum_sequences{};

    sort(begin(array), end(array));

    for (size_t i{}; i < arr_size - 2;
         i = static_cast<size_t>(
             upper_bound(cbegin(array) + i + 1, cend(array) - 2, array[i]) -
             cbegin(array))) {
      for (size_t j{i + 1}; j < arr_size - 1;
           j = static_cast<size_t>(
               upper_bound(cbegin(array) + j + 1, cend(array) - 1, array[j]) -
               cbegin(array))) {
        const int two_sum{array[i] + array[j]};

        if (two_sum > 0)
          break;

        if (binary_search(cbegin(array) + j + 1, cend(array), 0 - two_sum)) {
          correct_three_sum_sequences.push_back(
              {array[i], array[j], 0 - two_sum});
        }
      }
    }

    return correct_three_sum_sequences;
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
