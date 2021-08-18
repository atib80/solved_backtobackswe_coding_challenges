#include <iostream>
#include <limits>
#include <set>
#include <string>
#include <vector>

using namespace std;

class Solution {
 public:
  int timeDifference(const vector<string>& times) const {
    set<int> time_points{};
    int minimum_time_difference{numeric_limits<int>::max()};
    for (const string& t : times) {
      const int minutes = parseTimeInMinutesFromString(t);

      auto p = time_points.emplace(minutes);

      if (!p.second)
        return 0;

      const auto ub_iter = time_points.upper_bound(minutes);

      if (ub_iter != end(time_points)) {
        if (*ub_iter - minutes < minimum_time_difference) {
          minimum_time_difference = *ub_iter - minutes;
        }
      }

      if (p.first != begin(time_points)) {
        --p.first;
        if (minutes - *p.first < minimum_time_difference) {
          minimum_time_difference = minutes - *p.first;
        }
      }
    }

    const auto last = --end(time_points);

    const int diff_between_first_last_time_point =
        (1440 - *last) + *begin(time_points);

    if (diff_between_first_last_time_point < minimum_time_difference)
      return diff_between_first_last_time_point;

    return minimum_time_difference;
  }

 private:
  static int parseTimeInMinutesFromString(const string& time) {
    const int hour = (time[0] - '0') * 10 + time[1] - '0';
    const int minutes = (time[3] - '0') * 10 + time[4] - '0';
    return hour * 60 + minutes;
  }
};

int main() {
  Solution s;

  cout << "s.timeDifference({\"00:03\", \"23:59\", \"12:03\"}) -> "
       << s.timeDifference({"00:03", "23:59", "12:03"})
       << '\n';  // expected output: 4

  cout << "s.timeDifference({\"14:10\", \"13:30\", \"10:30\", \"16:42\"}) -> "
       << s.timeDifference({"14:10", "13:30", "10:30", "16:42"})
       << '\n';  // expected output: 40

  cout << "s.timeDifference({\"13:10\", \"04:40\", \"17:00\"}) -> "
       << s.timeDifference({"13:10", "04:40", "17:00"})
       << '\n';  // expected output: 230

  cout << "s.timeDifference({\"10:00\", \"23:45\", \"05:00\", \"00:01\"}) -> "
       << s.timeDifference({"10:00", "23:45", "05:00", "00:01"})
       << '\n';  // expected output: 16

  return 0;
}