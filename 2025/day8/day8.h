#pragma once
#include <iosfwd>
#include <vector>
#include <tuple>

namespace part1 {

unsigned long long solve(std::istream &is);

}

namespace part2 {

unsigned long long solve(std::istream &is);

}

struct Point {
    long long x;
    long long y;
    long long z;

    Point() : x(0), y(0), z(0) {
    }

    Point(int x_, int y_, int z_) : x(x_), y(y_), z(z_) {
    }

    auto operator<=>(const Point &) const = default;

    double distance(const Point &other) const;
};

using PairDist = std::tuple<Point, Point, double>;

struct PairDistComparator {
    bool operator()(const PairDist &a, const PairDist &b) const;
};

class DSU {
    std::vector<int> parent;
    std::vector<int> size;

public:
    explicit DSU(int sz);

    int findSet(int v) const;

    bool unionSets(int a, int b);

    int getSetSize(int v) const;
};