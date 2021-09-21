/*
Next Permutation
Given a sequence of integers in an array, find the "next permutation" of the
sequence.

If the current permutation is the final permutation in the permutation sequence,
return an array sorted in ascending order.

Here is an example permutation sequence:
1,2,3
1,3,2
2,1,3
2,3,1
3,1,2
3,2,1

Here is how that was constructed:
_,_,_ (can use: 1,2,3)
1,_,_ (can use: 2,3)
1,2,_ (can use: 3)
1,2,3 Permutation #1 (choices exhausted - backtrack)
1,2,_ (can use: 3) (already placed 3 - backtrack)
1,_,_ (can use: 3, 2)
1,3,_ (can use: 2)
1,3,2 Permutation #2 (choices exhausted - backtrack)
1,3,_ (can use: 2) (already placed 2 - backtrack)
1,_,_ (can use: 2, 3) (already placed 3 - backtrack)
_,_,_ (can use: 2, 3, 1)
2,_,_ (can use: 3, 1)
2,1,_ (can use: 3)
2,1,3 Permutation #3 (choices exhausted - backtrack)
... and so on

Example 1:
Input: [1,2,3,4]
Output: [1,2,4,3]

Example 2:
Input: [1,5,2]
Output: [2,1,5]

Example 3:
Input: [3,2,1]
Output: [1,2,3] # Cycle back around to the first permutation

Follow-up:
Can you solve this in O(n) time?
Can you solve this only using O(1) space?

Constraints:
The sequence is conceptually created by placing the least (lowest in value)
unplaced item for that slot when it comes time to choose a placement 0 <= n <=
100 (where n is the length of the array)
*/

#include <algorithm>
#include <iostream>
#include <type_traits>
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
  // asymptotic time complexity: O(n)
  // asymptotic space complexity: O(1)
  vector<int> nextPermutation(vector<int>& nums) const
      noexcept(is_nothrow_move_constructible<vector<int>>::value&&
                   is_nothrow_move_assignable<vector<int>>::value&& noexcept(
                       std::reverse<std::vector<int>::iterator>(
                           std::declval<std::vector<int>::iterator>(),
                           std::declval<std::vector<int>::iterator>()))) {
    // 1. If nums is empty or only has 1 element, return nums.
    if (nums.size() <= 1)
      return move(nums);

    // 2. Find the last increasing element's position while traversing nums
    // starting from the last element.
    size_t i{nums.size() - 1};

    for (; i > 0; --i) {
      if (nums[i - 1] < nums[i])
        break;
    }

    // 3. If the last increasing element's position is 0, we have to reverse the
    // whole array [4, 3, 2, 1] -> [1, 2, 3, 4].
    if (0 == i) {
      reverse(begin(nums), end(nums));
      return move(nums);
    }

    --i;

    // 4. Find the next greater number to nums[i].
    size_t j{i + 1};
    for (size_t k{i + 1}; k < nums.size(); ++k) {
      if (nums[k] > nums[i] && nums[k] < nums[j]) {
        j = k;
      }
    }
    // 5. Swap nums[i] (the first number located to the left of the last
    // increasing element) with the next greater number.
    swap(nums[i], nums[j]);

    // 6. Reverse the order of elements in the increasing sequence.
    reverse(begin(nums) + i + 1, end(nums));

    return move(nums);
  }
};

int main() {
  Solution s;

  vector<int> sequence1{1, 2, 3, 4};
  const vector<int> next_perm_seq1{s.nextPermutation(sequence1)};
  print_sequence(cbegin(next_perm_seq1), cend(next_perm_seq1),
                 cout);  // expected output: [1, 2, 4, 3]

  cout << "\n*******************************************************\n";

  vector<int> sequence2{1, 5, 2};
  const vector<int> next_perm_seq2{s.nextPermutation(sequence2)};
  print_sequence(cbegin(next_perm_seq2), cend(next_perm_seq2),
                 cout);  // // expected output: [2, 1, 5]

  cout << "\n*******************************************************\n";

  vector<int> sequence3{3, 2, 1};
  const vector<int> next_perm_seq3{s.nextPermutation(sequence3)};
  print_sequence(cbegin(next_perm_seq3), cend(next_perm_seq3),
                 cout);  // expected output: [1, 2, 3]

  cout << "\n*******************************************************\n";

  return 0;
}
