#pragma once
#include <iosfwd>
#include <vector>
#include <set>

namespace part1 {

int solve(std::istream &is);
int countAllReachable(const std::vector<std::vector<char>> &grid);

}

namespace part2 {

int solve(std::istream &is);
int countReachableRecursive(std::vector<std::vector<char>> &grid,
                            std::set<std::pair<int, int>> &loc);
bool reachable(const std::vector<std::vector<char>> &grid, int r, int c);

}