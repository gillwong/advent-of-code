#include "utils.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
using std::endl;
using std::getline;
using std::ifstream;
using std::istringstream;
using std::ostream;
using std::pair;
using std::string;
using std::vector;

bool isReportSafe(const vector<unsigned int> &report, const bool isIncreasing);

bool isSafe(const unsigned int prev, const unsigned int curr,
           const bool isIncreasing);

int main(int argc, char *argv[]) {
  pair<ifstream *, ostream *> streams = processArgs(argc, argv);
  ifstream *in = streams.first;
  ostream *out = streams.second;

  unsigned int safe = 0, dampenSafe = 0;
  for (string s; getline(*in, s);) {
    istringstream report(s);
    vector<unsigned int> levels;
    unsigned int increasing = 0, decreasing = 0;
    bool isIncreasing;

    unsigned int prev, curr;
    report >> curr;
    levels.push_back(curr);
    for (;;) {
      prev = curr;
      report >> curr;
      if (report.fail()) { // reach end of line
        isIncreasing = increasing > decreasing;
        break;
      }
      if (curr > prev) {
        increasing += 1;
      } else if (curr < prev) {
        decreasing += 1;
      }
      levels.push_back(curr);
    }
    const unsigned int sz = levels.size();

    bool unsafe = !isReportSafe(levels, isIncreasing);
    if (!unsafe) {
      safe += 1;
      dampenSafe += 1;
      continue;
    }

    vector<unsigned int> newLevels(sz - 1);
    for (vector<unsigned int>::size_type i = 0; i < sz; i += 1) {
      // copy except one element
      for (vector<unsigned int>::size_type j = 0, k = 0; j < sz; j += 1) {
        if (j == i)
          continue;
        newLevels[k] = levels[j];
        k += 1;
      }
      if (isReportSafe(newLevels, isIncreasing)) {
        dampenSafe += 1;
        break;
      }
    }
  }

  *out << "Part 1: " << safe << "\n"
       << "Part 2: " << dampenSafe << endl;
}

bool isSafe(const unsigned int prev, const unsigned int curr,
           const bool isIncreasing) {
  const unsigned int minDiff = 1, maxDiff = 3;
  unsigned int diff = isIncreasing ? curr - prev : prev - curr;
  return diff >= minDiff && diff <= maxDiff;
}

bool isReportSafe(const vector<unsigned int> &report, const bool isIncreasing) {
  for (vector<unsigned int>::size_type i = 1; i < report.size(); i += 1) {
    if (!isSafe(report[i - 1], report[i], isIncreasing))
      return false;
  }
  return true;
}
