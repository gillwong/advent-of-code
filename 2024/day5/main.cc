#include "utils.h"
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
using std::endl;
using std::ifstream;
using std::map;
using std::ostream;
using std::pair;
using std::set;
using std::stoi;
using std::string;
using std::swap;
using std::vector;

bool isCorrect(const map<unsigned int, set<unsigned int>> &rules,
               const map<unsigned int, unsigned int> &pos);

int main(int argc, char *argv[]) {
  pair<ifstream *, ostream *> streams = processArgs(argc, argv);
  ifstream *in = streams.first;
  ostream *out = streams.second;

  // values must precede key if both occur
  map<unsigned int, set<unsigned int>> rules;

  // parse page ordering rules
  for (string line; getline(*in, line) && !line.empty();) {
    string::size_type pos = line.find('|');
    rules[stoi(line.substr(pos + 1))].insert(stoi(line.substr(0, pos)));
  }

  unsigned int correctCnt = 0, incorrectCnt = 0;
  // value is the update and the corresponding page positions
  vector<pair<vector<unsigned int>, map<unsigned int, unsigned int>>> incorrect;

  for (string line; getline(*in, line);) {
    vector<unsigned int> update;
    // to test correctness
    map<unsigned int, unsigned int> pos;

    for (string::size_type currPos = 0, prev = 0, curr = line.find(',');;
         currPos += 1, prev = curr + 1, curr = line.find(',', prev)) {
      unsigned int page = stoi(
          line.substr(prev, curr == string::npos ? string::npos : curr - prev));
      update.push_back(page);
      pos[page] = currPos;
      if (curr == string::npos)
        break;
    }

    if (isCorrect(rules, pos))
      correctCnt += update[update.size() / 2];
    else
      incorrect.emplace_back(update, pos);
  }

  for (auto &update : incorrect) {
    map<unsigned int, unsigned int> &pos = update.second;
    while (!isCorrect(rules, pos)) {
      for (auto &e : pos) {
        if (rules.count(e.first) != 0) {
          for (unsigned int pred : rules.at(e.first)) {
            if (pos.count(pred) != 0) {
              unsigned int predPos = pos.at(pred);
              if (predPos > e.second) {
                swap(update.first[e.second], update.first[predPos]);
                pos[pred] = e.second;
                e.second = predPos;
                goto outerLoop;
              }
            }
          }
        }
      }
    outerLoop:;
    }
    incorrectCnt += update.first[update.first.size() / 2];
  }

  *out << "Part 1: " << correctCnt << "\n"
       << "Part 2: " << incorrectCnt << endl;
}

bool isCorrect(const map<unsigned int, set<unsigned int>> &rules,
               const map<unsigned int, unsigned int> &pos) {
  for (auto e : pos) {
    if (rules.count(e.first) != 0) {
      for (unsigned int pred : rules.at(e.first)) {
        if (pos.count(pred) != 0) {
          // remove equality because two pages cannot be in the same position
          if (pos.at(pred) > e.second)
            return false;
        }
      }
    }
  }
  return true;
}
