/*
Valid sudoku
Given a 9x9 sudoku board, return true if it is valid, return false otherwise.

An example valid board:

|4|1| | |7| | | |5|
| |8| | | |6| |9| |
| | | |5| | | | | |
| | |7|4| |1|3| | |
|5|3| | | | | |1|2|
| | |4|3| |8|7| | |
| | | | | |4| | | |
| |9| |8| | | |7| |
|7| | | |6| | |2|8|


Note:
A sudoku board is valid if each respective row, column, & subgrid contain unique numerical values. A duplicate value in a row, column, or 3x3 subgrid invalidates the whole board.
0 denotes an empty cell.
*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
  public:
    bool validSudoku(const vector<vector<int>>& board) const {
      bool unique_rows[90]{};
      bool unique_columns[90]{};
      bool unique_subgrids[90]{};

      for (size_t i{}; i < min<size_t>(9U, board.size()); ++i) {
        for (size_t j{}; j < min<size_t>(9U, board[i].size()); ++j) {
          if (board[i][j] != 0) {
          const int row_index = i * 10 + board[i][j];
          if (unique_rows[row_index])
            return false;

          const int col_index = j * 10 + board[i][j];
          if (unique_columns[col_index])
            return false;

          const int subgrid_index = ((i/3) * 3 + j/3) * 10 + board[i][j];
          if (unique_subgrids[subgrid_index])
            return false;

          unique_rows[row_index] = true;
          unique_columns[col_index] = true;
          unique_subgrids[subgrid_index] = true;
        }
       }
      }

      return true;
    }
};


int main() {

  Solution s;

  vector<vector<int>> sudoku_grid{{4, 1, 0, 0, 7, 0, 0, 0, 5}, {0, 8, 0, 0, 0, 6, 0, 9, 0}, {0, 0, 0, 5, 0, 0, 0, 0, 0}, {0, 0, 7, 4, 0, 1, 3, 0, 0}, {5, 3, 0, 0, 0, 0, 0, 1, 2}, {0, 0, 4, 3, 0, 8, 7, 0, 0}, {0, 0, 0, 0, 0, 4, 0, 0, 0}, {0, 9, 0, 8, 0, 0, 0, 7, 0}, {7, 0, 0, 0, 6, 0, 0, 2, 8}};

  cout << boolalpha << "s.validSudoku("
  "[4, 1, 0, 0, 7, 0, 0, 0, 5]"
  "[0, 8, 0, 0, 0, 6, 0, 9, 0]"
  "[0, 0, 0, 5, 0, 0, 0, 0, 0]"
  "[0, 0, 7, 4, 0, 1, 3, 0, 0]"
  "[5, 3, 0, 0, 0, 0, 0, 1, 2]"
  "[0, 0, 4, 3, 0, 8, 7, 0, 0]"
  "[0, 0, 0, 0, 0, 4, 0, 0, 0]"
  "[0, 9, 0, 8, 0, 0, 0, 7, 0]"
  "[7, 0, 0, 0, 6, 0, 0, 2, 8]"
  ") -> " << s.validSudoku(sudoku_grid) << '\n'; // expected output: true

  return 0;
}

