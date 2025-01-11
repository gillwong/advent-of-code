#include "../lib/utils.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
using std::endl;
using std::ifstream;
using std::istringstream;
using std::ostream;
using std::pair;
using std::stoul;
using std::string;
using std::vector;

bool test(const unsigned long &target, unsigned long prev,
          vector<int>::const_iterator begin, vector<int>::const_iterator end);

bool test2(const unsigned long &target, unsigned long prev,
           vector<int>::const_iterator begin, vector<int>::const_iterator end);

unsigned long concat(const unsigned long &a, int b);

int main(int argc, char *argv[]) {
  pair<ifstream *, ostream *> streams = processArgs(argc, argv);
  ifstream *in = streams.first;
  ostream *out = streams.second;

  vector<pair<unsigned long, vector<int>>> tests;
  for (string line; getline(*in, line);) {
    string::size_type sep = line.find(':');
    tests.emplace_back(stoul(line.substr(0, sep)), vector<int>());

    istringstream ss(line.substr(sep + 2));
    for (int n; ss >> n; tests.back().second.push_back(n))
      ;
  }

  unsigned long sum = 0;
  vector<pair<unsigned long, vector<int>>> secondTests;
  for (const auto &t : tests) {
    if (test(t.first, t.second.front(), t.second.begin() + 1, t.second.end())) {
      sum += t.first;
    } else {
      secondTests.emplace_back(t);
    }
  }

  *out << "Part 1: " << sum << "\n";

  for (const auto &t : secondTests) {
    if (test2(t.first, t.second.front(), t.second.begin() + 1,
              t.second.end())) {
      sum += t.first;
    }
  }

  *out << "Part 2: " << sum << endl;
}

bool test(const unsigned long &target, unsigned long prev,
          vector<int>::const_iterator begin, vector<int>::const_iterator end) {
  if (begin == end) {
    return prev == target;
  }
  return test(target, prev + *begin, begin + 1, end) ||
         test(target, prev * *begin, begin + 1, end);
}

bool test2(const unsigned long &target, unsigned long prev,
           vector<int>::const_iterator begin, vector<int>::const_iterator end) {
  if (begin == end) {
    return prev == target;
  }
  return test2(target, prev + *begin, begin + 1, end) ||
         test2(target, prev * *begin, begin + 1, end) ||
         test2(target, concat(prev, *begin), begin + 1, end);
}

unsigned long concat(const unsigned long &a, int b) {
  unsigned long mult = 1;
  for (int i = b; i > 0; i /= 10, mult *= 10)
    ;
  return a * mult + b;
}
