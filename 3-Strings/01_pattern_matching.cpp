/*
Pattern Matching
Given a set of strings words and a string pattern return a list of all of the
strings in words that matches the pattern of the pattern string.

Example 1:
Input:
words = ["aa", "bb"]
pattern = "cc"
Output: ["aa", "bb"]
Explanation: Both strings repeat letters just as the pattern string does.

Example 2:
Input:
words = ["aac", "bbc", "bcb", "yzy"]
pattern = "ghg"
Output: ["bcb", "yzy"]

Example 3:
Input:
words = ["aa", "bb"]
pattern = "zy"
Output: []

Note - Return the words in the order as they appear in the input
*/

#include <iostream>
#include <string>
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
  // asymptotic time complexity: O(N * M), where N = number of words, M = longest word's length
  // asymptotic space complexity: O(1)
  vector<string> findAndReplacePattern(const vector<string>& words,
                                       const string& pattern) const {
    if (words.empty())
      return {};

    vector<string> result;

    for (const auto& word : words) {
      if (pattern.empty() && word.empty()) {
        result.emplace_back();
      } else if (word.length() == pattern.length()) {
        char word_to_pattern[128]{};
        char pattern_to_word[128]{};
        bool is_match{true};
        for (size_t i{}; i < word.length(); ++i) {
          const size_t pi{static_cast<size_t>(pattern[i])};
          const size_t wi{static_cast<size_t>(word[i])};
          if ((pattern_to_word[pi] != 0 &&
               pattern_to_word[pi] != word[i]) ||
              (word_to_pattern[wi] != 0 &&
               word_to_pattern[wi] != pattern[i])) {
            is_match = false;
            break;
          }
          pattern_to_word[pi] = word[i];
          word_to_pattern[wi] = pattern[i];
        }

        if (is_match)
          result.emplace_back(word);
      }
    }
    return result;
  }
};

int main() {
  Solution s;

  vector<string> word_matches{s.findAndReplacePattern({"aa", "bb"}, "cc")};
  print_sequence(cbegin(word_matches), cend(word_matches),
                 cout);  // expected output: ["aa", "bb"]
  cout << "\n*******************************************************\n";

  word_matches = s.findAndReplacePattern({"aac", "bbc", "bcb", "yzy"}, "ghg");
  print_sequence(cbegin(word_matches), cend(word_matches),
                 cout);  // expected output: ["bcb", "yzy"]
  cout << "\n*******************************************************\n";

  word_matches = s.findAndReplacePattern({"aa", "bb"}, "zy");
  print_sequence(cbegin(word_matches), cend(word_matches),
                 cout);  // expected output: []

  cout << "\n*******************************************************\n";

  word_matches = s.findAndReplacePattern({"abc", "cde", "zzz"}, "aaa");
  print_sequence(cbegin(word_matches), cend(word_matches),
                 cout);  // expected output: ["zzz"]

  cout << "\n*******************************************************\n";

  word_matches = s.findAndReplacePattern({"xx", "yy", "ka"}, "ba");
  print_sequence(cbegin(word_matches), cend(word_matches),
                 cout);  // expected output: ["ka"]

  cout << "\n*******************************************************\n";

  word_matches = s.findAndReplacePattern({"bc", "cd", "df"}, "ac");
  print_sequence(cbegin(word_matches), cend(word_matches),
                 cout);  // expected output: ["bc","cd","df"]

  cout << "\n*******************************************************\n";

  return 0;
}
