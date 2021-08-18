#include <array>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

class Solution {
 public:
  int timeDifference(const vector<string>& times) const {
    if (times.size() < 2)
      return 0;

    constexpr static size_t buffer_size{24 * 60};
    array<bool, buffer_size> minutes{};

    size_t minimum_time_difference{numeric_limits<size_t>::max()};

    for (const string& t : times) {
      const size_t index{parseTimeInMinutesFromString(t)};
      if (minutes[index])
        return 0;
      minutes[index] = true;
    }

    size_t first{};

    while (!minutes[first])
      ++first;

    size_t last{first};

    for (size_t next{first + 1}; next < minutes.size(); ++next) {
      if (minutes[next]) {
        if (next - last < minimum_time_difference) {
          minimum_time_difference = next - last;
        }
        last = next;
      }
    }

    if (1440 - last + first < minimum_time_difference)
      minimum_time_difference = 1440 - last + first;

    return minimum_time_difference;
  }

 private:
  static size_t parseTimeInMinutesFromString(const string& time) {
    const size_t hour = (time[0] - '0') * 10 + time[1] - '0';
    const size_t minutes = (time[3] - '0') * 10 + time[4] - '0';
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
