#include "day7.h"
#include <iostream>
#include <queue>
#include <map>

int part1::solve(std::istream &is) {
    Map map(is);
    map.start();
    return map.getSplits();
}

part1::Map::Map(std::istream &is) {
    for (;;) {
        std::string line;
        std::getline(is, line);
        map.emplace_back(line);

        if (is.eof())
            break;
        if (!is)
            throw std::runtime_error(
                "An error occurred while reading the input");
    }
    enter_loc = map[0].find_first_of('S');
    rows = map.size();
    cols = map[0].size();
}

void part1::Map::start() {
    std::queue<std::pair<size_type, size_type>> sources;
    sources.emplace(1, enter_loc);

    while (!sources.empty()) {
        auto [r, c] = sources.front();
        sources.pop();

        for (; r < rows && map[r][c] == '.'; ++r)
            map[r][c] = '|';
        if (r == rows || map[r][c] != '^')
            continue;

        ++splits;
        if (c > 0)
            sources.emplace(r, c - 1);
        if (c < cols)
            sources.emplace(r, c + 1);
    }
}

std::ostream &part1::operator<<(std::ostream &os, const Map &map) {
    for (const auto &line : map.map)
        os << line << '\n';
    return os;
}

unsigned long long part2::solve(std::istream &is) {
    Map map(is);
    map.start();
    return map.getWorlds();
}

bool part2::Map::Compare::operator()(const std::pair<size_type, size_type> &a,
                                     const std::pair<size_type, size_type> &b)
const {
    if (a.first == b.first)
        return a.second > b.second;
    return a.first > b.first;
}


part2::Map::Map(std::istream &is) {
    for (;;) {
        std::string line;
        std::getline(is, line);
        map.emplace_back(line);

        if (is.eof())
            break;
        if (!is)
            throw std::runtime_error(
                "An error occurred while reading the input");
    }
    enter_loc = map[0].find_first_of('S');
    rows = map.size();
    cols = map[0].size();
}

void part2::Map::start() {
    // initialization
    std::map<
        std::pair<size_type, size_type>,
        unsigned long long> unique_sources;
    std::priority_queue<
        std::pair<size_type, size_type>,
        std::vector<std::pair<size_type, size_type>>,
        Compare> sources;
    const std::pair<size_type, size_type> first_source(1, enter_loc);
    sources.push(first_source);
    unique_sources[first_source] = 1;

    // main loop
    while (!sources.empty()) {
        const auto p = sources.top();
        auto r = p.first, c = p.second;
        sources.pop();

        for (; r < rows && map[r][c] == '.'; ++r) {
        }
        if (r == rows) {
            worlds += unique_sources[p];
            continue;
        }

        if (c > 0) {
            const std::pair candidate(r, c - 1);
            if (auto it = unique_sources.find(candidate);
                it == unique_sources.end()) {
                sources.push(candidate);
            }
            unique_sources[candidate] += unique_sources[p];
        }
        if (c < cols) {
            const std::pair candidate(r, c + 1);
            if (auto it = unique_sources.find(candidate);
                it == unique_sources.end()) {
                sources.push(candidate);
            }
            unique_sources[candidate] += unique_sources[p];
        }
    }
}

std::ostream &part2::operator<<(std::ostream &os, const Map &map) {
    for (const auto &line : map.map)
        os << line << '\n';
    return os;
}