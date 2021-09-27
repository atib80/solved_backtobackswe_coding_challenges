/*
Replace Words With Prefix
Given a list of prefixes prefixes and a sentence sentence, replace all words in
sentence that start with any of the given prefixes in prefixes.

Example:
Inputs:
prefixes = ["cat", "catch", "Alabama"]
sentence = "The cats were catching yarn"

Output: "The cat were cat yarn"
Explanation: "cats" and "catching" were both replaced by their shortest prefix
match "cat".

Note:
The shortest matching prefix will win when a word matches multiple prefixes.
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

class Solution {
 public:
  string replaceWordsWithPrefix(vector<string>& prefixes, string sentence) {
    sort(begin(prefixes), end(prefixes),
         [](const auto& lhs, const auto& rhs) noexcept -> bool {
           return lhs.length() < rhs.length();
         });

    vector<string> words{str_split(sentence, " |\t|\n", "|", false)};

    unordered_map<string, vector<size_t>> word_to_prefixes;

    for (size_t i{}; i < words.size(); ++i) {
      if (1U == word_to_prefixes.count(words[i]))
        continue;

      word_to_prefixes[words[i]] = {};

      for (size_t j{}; j < prefixes.size(); ++j) {
        if (words[i].length() <= prefixes[j].length())
          break;
        if (words[i].front() == prefixes[j].front())
          word_to_prefixes[words[i]].emplace_back(j);
      }
    }

    for (size_t i{}; i < words.size(); ++i) {
      for (size_t j{}; j < word_to_prefixes.at(words[i]).size(); ++j) {
        const size_t prefix_index = word_to_prefixes.at(words[i])[j];
        if (0U == words[i].find(prefixes[prefix_index])) {
          words[i] = prefixes[prefix_index];
          break;
        }
      }
    }

    const size_t cap{sentence.capacity()};
    sentence.clear();
    sentence.reserve(cap);

    for (auto& word : words) {
      sentence.append(move(word));
      sentence.push_back(' ');
    }

    sentence.pop_back();
    return sentence;
  }

  static pair<size_t, size_t> str_find_first_needle_position(
      const string& src,
      const vector<string>& needle_parts,
      const size_t start_pos = 0U) {
    const size_t not_found_index{string::npos};
    size_t first_needle_pos{not_found_index};
    size_t needle_len{};

    for (const auto& needle : needle_parts) {
      const size_t needle_start_pos = src.find(needle, start_pos);
      if (needle_start_pos < first_needle_pos) {
        first_needle_pos = needle_start_pos;
        needle_len = needle.length();
      }
    }

    return {first_needle_pos, needle_len};
  }

  static vector<string> str_split(
      const string& src,
      const string& needle,
      const string& needle_parts_separator_token = "",
      const bool split_on_whole_needle = true,
      const bool ignore_empty_string = true,
      const size_t max_count = string::npos) {
    const size_t src_len{src.length()};

    if (0U == src_len)
      return {};

    const size_t needle_len{needle.length()};

    if (0U == needle_len) {
      const size_t upper_limit{max_count < src_len ? max_count : src_len};
      std::vector<string> parts{};
      parts.reserve(upper_limit);
      for (size_t i{}; i < upper_limit; ++i)
        parts.emplace_back(1, src[i]);
      return parts;
    }

    const size_t needle_parts_separator_token_len{
        needle_parts_separator_token.length()};

    vector<string> needle_parts{};

    if (needle_parts_separator_token_len > 0U && !split_on_whole_needle) {
      size_t start_pos{};

      while (true) {
        const size_t next_pos{
            needle.find(needle_parts_separator_token, start_pos)};

        if (string::npos == next_pos) {
          needle_parts.emplace_back(
              needle.substr(start_pos, needle_len - start_pos));
          break;
        }

        needle_parts.emplace_back(
            needle.substr(start_pos, next_pos - start_pos));

        start_pos = next_pos + needle_parts_separator_token.length();
      }
    } else
      needle_parts.emplace_back(needle);

    vector<string> parts{};
    size_t number_of_parts{}, prev{};

    while (true) {
      const pair<size_t, size_t> p =
          str_find_first_needle_position(src, needle_parts, prev);
      const size_t current{p.first};
      const size_t needle_part_len{p.second};

      if (string::npos == current || 0U == needle_part_len ||
          parts.size() == max_count)
        break;

      if (current - prev > 0U) {
        parts.emplace_back(std::cbegin(src) + prev, std::cbegin(src) + current);
        number_of_parts++;
      } else if (!ignore_empty_string) {
        parts.emplace_back();
        number_of_parts++;
      }

      prev = current + needle_part_len;

      if (prev >= src_len)
        break;
    }

    if (parts.size() < max_count) {
      if (prev < src_len)
        parts.emplace_back(std::cbegin(src) + prev, std::cend(src));
      else if (!ignore_empty_string)
        parts.emplace_back();
    }

    return parts;
  }
};

int main() {
  Solution s;

  vector<string> prefixes1{"cat", "catch", "Alabama"};

  cout << "s.replaceWordsWithPrefix([\"cat\", \"catch\", \"Alabama\"], \"The "
          "cats were catching yarn\") -> "
       << s.replaceWordsWithPrefix(prefixes1, "The cats were catching yarn")
       << '\n';

  vector<string> prefixes2{"h",     "t",       "ab",          "abcxyz", "ba",
                           "lmnop", "lmnopqr", "xyxyxyxyxyx", "lllll"};
  cout << "s.replaceWordsWithPrefix([\"h\", \"t\", \"ab\", \"abcxyz\", \"ba\", "
          "\"lmnop\", \"lmnopqr\", \"xyxyxyxyxyx\", \"lllll\"], \"hi there "
          "this is back to back swe Hi there this is back to back swehi there "
          "this is back to back swehi there this is back to back swe\") -> "
       << s.replaceWordsWithPrefix(
              prefixes2,
              "hi there this is back to back swe Hi there this is back to back "
              "swehi there this is back to back swehi there this is back to "
              "back swe")
       << '\n';

  return 0;
}
