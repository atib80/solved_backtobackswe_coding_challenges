/*
Count Subarrays That Sum To K

Given an array of integers arr and an integer value k, return the total amount
of unique, contiguous, subarrays that sum to k in arr.

Example 1:

Input: [1, 0, -1, 1] k = 0
Output: 4
Explanation: 4 subarrays sum up to 0.

               i j
[1, 0, -1, 1] [1,1]
[1, 0, -1, 1] [0,2]
[1, 0, -1, 1] [1,3]
[1, 0, -1, 1] [2,3]


Example 2:

Input: [3, 7, -4, -2, 1, 5] k = 3
Output: 2
Explanation: 2 subarrays sum up to 3.

                      i j
[3, 7, -4, -2, 1, 5] [0,0]
[3, 7, -4, -2, 1, 5] [1,2]


Constraints:

  The array will not be null or empty (len(arr) > 0).

*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int countSubarrays(const vector<int>& arr, const int k) const {
    if (arr.empty())
      return 0;

    vector<int> sum_of_consecutive_array_elements(arr.size());

    sum_of_consecutive_array_elements[0] = arr[0];

    for (size_t i{1}; i < arr.size(); ++i) {
      sum_of_consecutive_array_elements[i] =
          sum_of_consecutive_array_elements[i - 1] + arr[i];
    }

    int count{};

    for (size_t i{}; i < arr.size(); ++i) {
      for (size_t j{i}; j < arr.size(); ++j) {

            const int sum =
                0 != i ? sum_of_consecutive_array_elements[j] -
                             sum_of_consecutive_array_elements[i - 1]
                       : sum_of_consecutive_array_elements[j];

        count += (sum == k);
      }
    }

    return count;
  }
};

int main() {
  Solution s;

  cout << "s.countSubarrays([1, 0, -1, 1], 0) -> "
       << s.countSubarrays({1, 0, -1, 1}, 0) << '\n';  // expected output: 4
  cout << "s.countSubarrays([3, 7, -4, -2, 1, 5], 3) -> "
       << s.countSubarrays({3, 7, -4, -2, 1, 5}, 3)
       << '\n';  // expected output: 2

  return 0;
}
