#include "utils.h"
#include "day4.h"
#include <fstream>
#include <ostream>
#include <string>
#include <utility>
#include <vector>
using std::endl;
using std::ifstream;
using std::ostream;
using std::pair;
using std::string;
using std::vector;

int main(int argc, char *argv[]) {
  pair<ifstream *, ostream *> streams = processArgs(argc, argv);
  ifstream *in = streams.first;
  ostream *out = streams.second;

  vector<string> board;

  for (string line; getline(*in, line);) {
    board.push_back(line);
  }

  WordSearch ws(board, "XMAS");

  *out << "Part 1: " << ws.getCount() << "\n"
       << "Part 2: " << ws.getXCount() << endl;
}
