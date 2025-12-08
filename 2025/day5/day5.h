#pragma once
#include <iosfwd>
#include <memory>

namespace part1 {

int solve(std::istream &is);

}

namespace part2 {

long long solve(std::istream &is);

}

struct Range {
    long long minimum;
    long long maximum;

    Range(long long minimum_, long long maximum_);

    bool contains(long long num) const;
    bool subset(const Range &other) const;
};

class RangeBST {
public:
    struct Node {
        Range range;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        explicit Node(Range range_);
    };

private:
    std::unique_ptr<Node> head;

    void insert(Range range, Node *curr, Node *prev);

    long long count(const Node *node) const;

public:
    explicit RangeBST(std::istream &is);

    void insert(Range range);

    bool contains(long long num) const;

    long long count() const;
};