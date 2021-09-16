
/*
Spiral Traversal of A Matrix
Given a two-dimensional matrix with m rows and n columns (m x n matrix), return
its spiral ordering starting from the top left of the matrix (row 0, col 0).

Example 1:
Input:
[
 [ 1, 2, 3],
 [ 4, 5, 6],
 [ 7, 8, 9]
]
Output: [1,2,3,6,9,8,7,4,5]

Example 2:
Input:
[
  [1,2],
  [3,4],
  [5,6],
  [7,8]
]
Output: [1,2,4,6,8,7,5,3]

Example 3:
Input:
[
  [1],
  [2],
  [3],
  [4]
]
Output: [1,2,3,4]

Example 4:
Input:
[
  [1,2,3,4],
  [5,6,7,8]
]
Output: [1,2,3,4,8,7,6,5]

Constraints:
0 <= m <= 100
0 <= n <= 100
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
  vector<int> spiralOrder(const vector<vector<int>>& matrix) {
    if (matrix.empty())
      return {};

    const size_t max_cells{matrix.size() * matrix[0].size()};

    vector<int> result;
    result.reserve(max_cells);

    int min_x{}, max_x{static_cast<int>(matrix.size() - 1)};
    int min_y{}, max_y{static_cast<int>(matrix[0].size() - 1)};

    // starting point is the upper-left corner of 'matrix' (min_x, min_y)
    int x{}, y{};

    while (min_x <= max_x && min_y <= max_y) {
      y = min_y;

      while (y <= max_y && min_x <= max_x) {
        result.emplace_back(matrix[min_x][y]);
        ++y;
      }

      ++min_x;  // we increase min_x by 1 so that we don't accidentally wind up
                // visiting the previously visited top row again
      x = min_x;

      while (x <= max_x && min_y <= max_y) {
        result.emplace_back(matrix[x][max_y]);
        ++x;
      }

      --max_y;  // we decrease max_y by 1 so that we don't accidentally wind up
                // visiting the previously visited right column again
      y = max_y;

      while (y >= min_y && min_x <= max_x) {
        result.emplace_back(matrix[max_x][y]);
        --y;
      }

      --max_x;  // we decrease max_x by 1 so that we don't accidentally wind up
                // visiting the previously visited bottom row again
      x = max_x;

      while (x >= min_x && min_y <= max_y) {
        result.emplace_back(matrix[x][min_y]);
        --x;
      }

      ++min_y;  // we increase min_y by 1 so that we don't accidentally wind up
                // visiting the previously visited left column again
    }
    return result;
  }
};

int main() {
  Solution s;

  vector<int> result{s.spiralOrder({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}})};

  std::cout << "s.spiralOrder({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}) -> \n";
  print_sequence(cbegin(result), cend(result), cout);

  cout << "\n*******************************************************\n";

  result = s.spiralOrder({{1, 2}, {3, 4}, {5, 6}, {7, 8}});
  std::cout << "s.spiralOrder({{1, 2}, {3, 4}, {5, 6}, {7, 8}}) -> \n";
  print_sequence(cbegin(result), cend(result), cout);

  cout << "\n*******************************************************\n";

  result = s.spiralOrder({{1}, {2}, {3}, {4}});
  std::cout << "s.spiralOrder({{1}, {2}, {3}, {4}}) -> \n";
  print_sequence(cbegin(result), cend(result), cout);

  cout << "\n*******************************************************\n";

  result = s.spiralOrder({{1, 2, 3, 4}, {5, 6, 7, 8}});
  std::cout << "s.spiralOrder({{1, 2, 3, 4}, {5, 6, 7, 8}}) -> \n";
  print_sequence(cbegin(result), cend(result), cout);

  cout << "\n*******************************************************\n";

  return 0;
}
