#pragma once
#include <iosfwd>
#include <vector>
#include <string>

namespace part1 {

int solve(std::istream &is);

class Map {
    friend std::ostream &operator<<(std::ostream &os, const Map &map);

public:
    using size_type = std::vector<std::string>::size_type;

private:
    std::vector<std::string> map;
    size_type enter_loc, rows, cols;
    int splits = 0;

public:
    explicit Map(std::istream &is);
    void start();

    int getSplits() const { return splits; }
};

}

namespace part2 {

unsigned long long solve(std::istream &is);

class Map {
    friend std::ostream &operator<<(std::ostream &os, const Map &map);

public:
    using size_type = std::vector<std::string>::size_type;

private:
    struct Compare {
        bool operator()(const std::pair<size_type, size_type> &a,
                        const std::pair<size_type, size_type> &b) const;
    };

    std::vector<std::string> map;
    size_type enter_loc, rows, cols;
    unsigned long long worlds = 0;

public:
    explicit Map(std::istream &is);
    void start();

    unsigned long long getWorlds() const { return worlds; }
};

}