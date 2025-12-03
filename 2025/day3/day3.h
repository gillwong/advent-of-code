#pragma once
#include <iosfwd>
#include <vector>

namespace part1 {

int solve(std::istream &is);
int maxCapacity(const std::vector<char> &bank);

}

namespace part2 {

long long solve(std::istream &is);
long long maxCapacity(const std::vector<char> &bank);

}

long long pow10(int exp);