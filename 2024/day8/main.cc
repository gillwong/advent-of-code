#include "utils.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
using std::abs;
using std::endl;
using std::getline;
using std::ifstream;
using std::map;
using std::ostream;
using std::pair;
using std::set;
using std::string;
using std::vector;

int gcd(int a, int b);

int main(int argc, char *argv[]) {
  pair<ifstream *, ostream *> streams = processArgs(argc, argv);
  ifstream *in = streams.first;
  ostream *out = streams.second;

  map<char, vector<pair<unsigned int, unsigned int>>> antennas;
  unsigned int rows = 0, cols;

  for (string line; getline(*in, line); rows += 1) {
    if (rows == 0) {
      cols = line.length();
    }
    for (string::size_type i = 0;;) {
      i = line.find_first_not_of('.', i);
      if (i == string::npos) {
        break;
      }
      antennas[line[i]].emplace_back(rows, i);
      i += 1;
    }
  }

  set<pair<unsigned int, unsigned int>> part1;

  for (const auto &e : antennas) {
    for (auto it = e.second.begin(); it != e.second.end(); ++it) {
      for (auto it1 = it + 1; it1 != e.second.end(); ++it1) {
        int rowDiff = it->first - it1->first,
            colDiff = it->second - it1->second;

        unsigned int nodeRow = it->first + rowDiff,
                     nodeCol = it->second + colDiff;
        if (nodeRow < rows && nodeCol < cols) {
          part1.emplace(nodeRow, nodeCol);
        }
        nodeRow = it1->first - rowDiff;
        nodeCol = it1->second - colDiff;
        if (nodeRow < rows && nodeCol < cols) {
          part1.emplace(nodeRow, nodeCol);
        }
      }
    }
  }

  set<pair<unsigned int, unsigned int>> part2;

  for (const auto &e : antennas) {
    for (auto it = e.second.begin(); it != e.second.end(); ++it) {
      for (auto it1 = it + 1; it1 != e.second.end(); ++it1) {
        int rowDiff = it->first - it1->first,
            colDiff = it->second - it1->second;
        int div = gcd(abs(rowDiff), abs(colDiff));
        rowDiff /= div;
        colDiff /= div;

        // forward
        for (unsigned int r = it->first, c = it->second; r < rows && c < cols;
             r += rowDiff, c += colDiff) {
          part2.emplace(r, c);
        }
        // backwards
        for (unsigned int r = it->first - rowDiff, c = it->second - colDiff;
             r < rows && c < cols; r -= rowDiff, c -= colDiff) {
          part2.emplace(r, c);
        }
      }
    }
  }

  *out << "Part 1: " << part1.size() << "\n"
       << "Part 2: " << part2.size() << endl;
}

int gcd(int a, int b) { return a == 0 ? b : gcd(b % a, a); }
