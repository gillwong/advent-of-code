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

#if defined(AUTO) || defined(MULTI)
#include <future>
#include <tuple>
#include <vector>
using std::async;
using std::future;
using std::get;
using std::launch;
using std::tuple;
using std::vector;
#endif

int main(int argc, char *argv[]) {
#ifdef MULTI
  tuple<ifstream *, ostream *, unsigned int> args =
      processMultiArgs(argc, argv);
  ifstream *in = get<0>(args);
  ostream *out = get<1>(args);
  unsigned int threads = get<2>(args);
#else
  pair<ifstream *, ostream *> streams = processArgs(argc, argv);
  ifstream *in = streams.first;
  ostream *out = streams.second;
#endif

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
#if defined(AUTO)
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
#elif defined(MULTI)
  vector<future<unsigned int>> futures;
  const auto &visited = guard.getVisited();

  unsigned int count = 0;
  vector<vector<pair<unsigned int, unsigned int>>> groups(threads);
  for (const auto &pos : visited) {
    groups[count % threads].emplace_back(pos);
    count += 1;
  }

  for (const auto &group : groups) {
    futures.emplace_back(async(
        launch::async,
        [&map, &start](const vector<pair<unsigned int, unsigned int>> &group) {
          unsigned int partial = 0;
          for (const auto &pos : group) {
            Map dup(map);
            dup.addWall(pos.first, pos.second);
            Guard sim(dup, start.first, start.second);
            try {
              for (;;) {
                sim.move();
              }
            } catch (Guard::Loop &) {
              partial += 1;
            } catch (Guard::Leaving &) {
            }
          }
          return partial;
        },
        group));
  }

  for (auto &future : futures) {
    uniqueBlocks += future.get();
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
