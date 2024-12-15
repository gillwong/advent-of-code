#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <cmath>
#include "utils.h"
#include "day1.h"
using std::endl;
using std::ifstream;
using std::map;
using std::ostream;
using std::pair;
using std::vector;

int main(int argc, char *argv[]) {
  pair<ifstream *, ostream *> streams = processArgs(argc, argv);
  ifstream *in = streams.first;
  ostream *out = streams.second;

  vector<unsigned int> l, r;
  using size_type = decltype(l)::size_type;
  map<unsigned int, unsigned int> rCnt;

  unsigned int limit = 0;
  for (unsigned int temp;;) {
    *in >> temp;
    if (in->fail())
      break;
    l.push_back(temp);
    limit = std::max(limit, temp);
    *in >> temp;
    if (in->fail())
      break;
    r.push_back(temp);
    limit = std::max(limit, temp);
    rCnt[temp] += 1;
  }

#if defined(COUNTING)
  countingSort(l.begin(), l.end(), limit);
  countingSort(r.begin(), r.end(), limit);
#elif defined(RADIX)
  radixSort(l.begin(), l.end(), limit);
  radixSort(r.begin(), r.end(), limit);
#else
  std::sort(l.begin(), l.end());
  std::sort(r.begin(), r.end());
#endif

  size_type total = 0, score = 0;
  for (size_type i = 0; i < l.size(); i += 1) {
    total += std::abs((int)(l[i] - r[i]));
    score += l[i] * rCnt[l[i]];
  }
  *out << "Part 1: " << total << "\n"
       << "Part 2: " << score << endl;
}
