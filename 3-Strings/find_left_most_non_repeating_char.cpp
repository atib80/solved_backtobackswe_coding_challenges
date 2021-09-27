#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <map>

using namespace std;

class Solution {
public:
  char findLeftMostNonRepeatingCharacter(const string& s) const {
    array<int, 256> visited_characters;
    map<size_t, char> already_visited_character_first_index;

    fill(begin(visited_characters), end(visited_characters), -1);

    for (size_t i{}; i < s.length(); ++i) {

      if (-1 == visited_characters[s[i]]) {
        visited_characters[s[i]] = i;
        already_visited_character_first_index.emplace(i, s[i]);
      } else {
        already_visited_character_first_index.erase(visited_characters[s[i]]);
      }
    }

    if (already_visited_character_first_index.empty())
      return '-';

    return cbegin(already_visited_character_first_index)->second;
  }


};

int main() {

  Solution s;

  cout << "s.findLeftMostNonRepeatingCharacter(\"geeksforgeeks\") -> " << s.findLeftMostNonRepeatingCharacter("geeksforgeeks") << '\n'; // expected output: f
  cout << "s.findLeftMostNonRepeatingCharacter(\"abcabc\") -> " << s.findLeftMostNonRepeatingCharacter("abcabc") << '\n'; // expected output: -

  return 0;
}
