#include "../lib/utils.h"
#include "day6.h"
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
using std::endl;
using std::ifstream;
using std::ostream;
using std::pair;
using std::string;
using Map = Guard::Map;

#ifdef MULTIPLE
#include <future>
#include <vector>
using std::async;
using std::future;
using std::launch;
using std::vector;
#endif

int main(int argc, char *argv[]) {
  pair<ifstream *, ostream *> streams = processArgs(argc, argv);
  ifstream *in = streams.first;
  ostream *out = streams.second;

  Map map(*in);
  auto start = map.getStart();
  Guard guard(map, start.first, start.second);

  unsigned int uniqueVisits = 1;
  try {
    for (;;) {
      if (guard.move()) {
        uniqueVisits += 1;
      }
    }
  } catch (Guard::Leaving &) {
  }

  unsigned int uniqueBlocks = 0;
#ifdef MULTIPLE
  vector<future<bool>> futures;
  for (const auto &pos : guard.getVisited()) {
    futures.emplace_back(async(
        launch::async,
        [&map, &start](const pair<unsigned int, unsigned int> &pos) {
          Map dup(map);
          dup.addWall(pos.first, pos.second);
          Guard sim(dup, start.first, start.second);
          try {
            for (;;) {
              sim.move();
            }
          } catch (Guard::Loop &) {
            return true;
          } catch (Guard::Leaving &) {
            return false;
          }
        },
        pos));
  }

  for (auto &future : futures) {
    if (future.get()) {
      uniqueBlocks += 1;
    }
  }
#else
  for (const auto &pos : guard.getVisited()) {
    Map dup(map);
    dup.addWall(pos.first, pos.second);
    Guard sim(dup, start.first, start.second);
    try {
      for (;;) {
        sim.move();
      }
    } catch (Guard::Loop &) {
      uniqueBlocks += 1;
    } catch (Guard::Leaving &) {
    }
  }
#endif

  *out << "Part 1: " << uniqueVisits << "\n"
       << "Part 2: " << uniqueBlocks << endl;
}
