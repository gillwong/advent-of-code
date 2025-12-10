#include "day8.h"
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <cmath>
#include <ranges>

unsigned long long part1::solve(std::istream &is) {
    std::map<Point, int> clusters;
    int sz = 0;
    for (;;) {
        int x, y, z;
        char temp_1, temp_2;
        is >> x >> temp_1 >> y >> temp_2 >> z;

        Point point(x, y, z);
        clusters[point] = sz++;

        if (is.eof())
            break;
        if (!is)
            throw std::runtime_error(
                "An error occurred while reading the input");
    }

    // calculate pairwise distances
    std::priority_queue<
        PairDist, std::vector<PairDist>, PairDistComparator> pair_dists;
    for (auto it_1 = clusters.cbegin(); it_1 != clusters.cend(); ++it_1) {
        for (auto it_2 = it_1; it_2 != clusters.cend(); ++it_2) {
            if (it_1 == it_2)
                continue;
            pair_dists.emplace(it_1->first, it_2->first,
                               it_1->first.distance(it_2->first));
        }
    }

    DSU dsu(sz);
    for (int i = 0; i < 1000; ++i) {
        auto [a, b, dist] = pair_dists.top();
        pair_dists.pop();

        dsu.unionSets(clusters[a], clusters[b]);
    }

    // calculate top 3
    std::set<int> visited;
    std::priority_queue<int> top_cluster_sizes;
    for (auto val : clusters | std::views::values) {
        int p = dsu.findSet(val);
        if (!visited.insert(p).second)
            continue;
        top_cluster_sizes.push(dsu.getSetSize(p));
    }

    unsigned long long result = 1;
    for (int i = 0; i < 3; ++i) {
        result *= top_cluster_sizes.top();
        top_cluster_sizes.pop();
    }
    return result;
}

unsigned long long part2::solve(std::istream &is) {
    std::map<Point, int> clusters;
    int sz = 0;
    for (;;) {
        int x, y, z;
        char temp_1, temp_2;
        is >> x >> temp_1 >> y >> temp_2 >> z;

        Point point(x, y, z);
        clusters[point] = sz++;

        if (is.eof())
            break;
        if (!is)
            throw std::runtime_error(
                "An error occurred while reading the input");
    }

    // calculate pairwise distances
    std::priority_queue<
        PairDist, std::vector<PairDist>, PairDistComparator> pair_dists;
    for (auto it_1 = clusters.cbegin(); it_1 != clusters.cend(); ++it_1) {
        for (auto it_2 = it_1; it_2 != clusters.cend(); ++it_2) {
            if (it_1 == it_2)
                continue;
            pair_dists.emplace(it_1->first, it_2->first,
                               it_1->first.distance(it_2->first));
        }
    }

    DSU dsu(sz);
    std::pair<Point, Point> last_pair;
    while (!pair_dists.empty()) {
        auto [a, b, dist] = pair_dists.top();
        pair_dists.pop();

        if (dsu.unionSets(clusters[a], clusters[b]))
            last_pair = std::make_pair(a, b);
    }

    const unsigned long long result = last_pair.first.x * last_pair.second.x;
    return result;
}


double Point::distance(const Point &other) const {
    return std::sqrt((other.z - z) * (other.z - z)
                     + (other.y - y) * (other.y - y)
                     + (other.x - x) * (other.x - x));
}

bool PairDistComparator::operator()(const PairDist &a, const PairDist &b)
const {
    return std::get<2>(a) > std::get<2>(b);
}

DSU::DSU(int sz) : parent(sz), size(sz, 1) {
    while (sz > 0)
        parent[sz] = --sz;
}

int DSU::findSet(int v) const {
    if (parent[v] == v)
        return v;
    return findSet(parent[v]);
}

bool DSU::unionSets(int a, int b) {
    a = findSet(a);
    b = findSet(b);
    if (a != b) {
        parent[b] = a;
        size[a] += size[b];
    }
    return a != b; // true if union happened
}

int DSU::getSetSize(int v) const {
    return size[findSet(v)];
}