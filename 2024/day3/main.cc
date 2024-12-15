#include "utils.h"
#include <fstream>
#include <ostream>
#include <string>
#include <utility>
using std::endl;
using std::ifstream;
using std::ostream;
using std::pair;
using std::string;

#ifdef REGEX
#include <regex>
#include <sstream>
using std::getline;
using std::ostringstream;
using std::regex;
using std::sregex_iterator;
using std::stoi;
#else
#include "day3.h"
#endif

int main(int argc, char *argv[]) {
  pair<ifstream *, ostream *> streams = processArgs(argc, argv);
  ifstream *in = streams.first;
  ostream *out = streams.second;

  unsigned int sum = 0, enabledSum = 0;
#ifdef REGEX
  ostringstream oss;
  for (string s; getline(*in, s);) {
    oss << s;
  }
  string content = oss.str();
  bool enabled = true;
  regex r("(?:mul\\((\\d{1,3}),(\\d{1,3})\\)|do\\(\\)|don't\\(\\))");
  for (sregex_iterator it(content.begin(), content.end(), r), endIt;
       it != endIt; ++it) {
    string instruction = it->str(0).substr(0, it->str(0).find_first_of('('));
    if (instruction == "do") {
      enabled = true;
    } else if (instruction == "don't") {
      enabled = false;
    } else { // instruction == "mul"
      unsigned int res = stoi(it->str(1)) * stoi(it->str(2));
      sum += res;
      if (enabled)
        enabledSum += res;
    }
  }
#else
  Parser p(*in);
  sum = p.getResult();
  enabledSum = p.getEnabledResult();
#endif

  *out << "Part 1: " << sum << "\n"
       << "Part 2: " << enabledSum << endl;
}
