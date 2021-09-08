/*
Rotating a 2D matrix
Given a two-dimensional square matrix (n x n), rotate the matrix 90 degrees to
the right (clockwise).

Example 1:
Input:
[
  [ 1,  2,  3, 4],
  [ 5,  6,  7, 8],
  [ 9, 10, 11, 12],
  [13, 14, 15, 16]
],

Output:
[
 [13,  9, 5, 1],
 [14, 10, 6, 2],
 [15, 11, 7, 3],
 [16, 12, 8, 4]
]

Example 2:
Input:
[
  [10, 20],
  [30, 40]
],

Output:
[
 [30, 10],
 [40, 20]
]

Challenge:
Can you do the rotation in-place?
*/

#include <iostream>
#include <vector>

using namespace std;

template <typename ContainerType>
void print_contents_of_2d_container(const ContainerType& container, ostream& os) {

  auto start_row = container.cbegin();
  auto last_row = container.cend();

  if (start_row == last_row) {
    os << "[ ]" << '\n';
  } else {
    while (start_row != last_row) {
      os << '[';

      auto col_first = start_row->cbegin();
      const auto col_last = --(start_row->cend());

      while (col_first != col_last) {
        os << *col_first << ", ";
        ++col_first;
      }
      os << *col_first << "]\n";

      ++start_row;
    }
  }
}

class Solution {
 public:
  void rotate(vector<vector<int>>& matrix) const noexcept {
    if (matrix.size() >= 2 && matrix.size() == matrix[0].size()) {
      for (size_t offset{}; offset < matrix.size() / 2; ++offset) {
        for (size_t x{offset}; x < matrix.size() - 1 - offset; ++x) {
          const int top_left = matrix[offset][x];
          const int top_right = matrix[x][matrix.size() - 1 - offset];
          const int bottom_right =
              matrix[matrix.size() - 1 - offset][matrix.size() - 1 - x];
          const int bottom_left = matrix[matrix.size() - 1 - x][offset];

          matrix[x][matrix.size() - 1 - offset] = top_left;
          matrix[matrix.size() - 1 - offset][matrix.size() - 1 - x] = top_right;
          matrix[matrix.size() - 1 - x][offset] = bottom_right;
          matrix[offset][x] = bottom_left;
        }
      }
    }
  }
};

int main() {
  Solution s{};

  vector<vector<int>> matrix1{
      {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};

  s.rotate(matrix1);

  print_contents_of_2d_container(matrix1, cout);

  cout << "----------------------------------------\n";

  vector<vector<int>> matrix2{{10, 20}, {30, 40}};

  s.rotate(matrix2);

  print_contents_of_2d_container(matrix2, cout);

  return 0;
}
