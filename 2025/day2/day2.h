#pragma once
#include <iosfwd>

namespace part1 {

long long solve(std::istream &is);
long long sumInvalidIDs(long long begin, long long end);

}

namespace part2 {

long long solve(std::istream &is);
long long sumInvalidIDs(long long begin, long long end);

}

int countDigits(long long id);
int getDigit(const long long &id, int pos);
long long pow10(int exp);