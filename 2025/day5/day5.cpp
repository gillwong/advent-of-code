#include "day5.h"
#include <iostream>
#include <vector>
#include <algorithm>

int part1::solve(std::istream &is) {
    const RangeBST range_bst(is);

    // query
    int count = 0;
    for (;;) {
        long long num;
        is >> num;

        if (range_bst.contains(num))
            ++count;

        if (is.eof())
            break;
        if (!is)
            throw std::runtime_error(
                "An error occurred while reading the input");
    }
    return count;
}

long long part2::solve(std::istream &is) {
    return RangeBST(is).count();
}

Range::Range(long long minimum_, long long maximum_)
    : minimum(minimum_), maximum(maximum_) {
}

bool Range::contains(long long num) const {
    return num >= minimum && num <= maximum;
}

bool Range::subset(const Range &other) const {
    return other.minimum <= minimum && other.maximum >= maximum;
}

RangeBST::Node::Node(const Range range_) : range(range_) {
}

void RangeBST::insert(Range range, Node *curr, Node *prev) {
    if (head == nullptr) {
        head = std::make_unique<Node>(range);
        return;
    }

    while (curr != nullptr) {
        prev = curr;

        if (range.subset(curr->range))
            return;

        if (curr->range.subset(range)
            && curr->range.minimum != range.minimum
            && curr->range.maximum != range.maximum) {
            insert(
                Range(range.minimum, curr->range.minimum - 1),
                curr->left.get(), prev);
            insert(
                Range(curr->range.maximum + 1, range.maximum),
                curr->right.get(), prev);
            return;
        }

        if (range.minimum < curr->range.minimum) {
            range.maximum = std::min(range.maximum, curr->range.minimum - 1);
            curr = curr->left.get();
        } else {
            // range.maximum > curr->range.maximum
            range.minimum = std::max(range.minimum, curr->range.maximum + 1);
            curr = curr->right.get();
        }
    }

    if (range.minimum < prev->range.minimum)
        prev->left = std::make_unique<Node>(range);
    else // range.maximum > prev->range.maximum
        prev->right = std::make_unique<Node>(range);
}

long long RangeBST::count(const Node *node) const {
    if (node == nullptr)
        return 0;

    return node->range.maximum - node->range.minimum + 1
           + count(node->left.get())
           + count(node->right.get());
}


RangeBST::RangeBST(std::istream &is) {
    for (;;) {
        long long minimum, maximum;
        char ch;
        is >> minimum >> ch >> maximum;
        insert(Range(minimum, maximum));
        is.get(ch);
        if (is.peek() == '\n')
            break;
    }
}

void RangeBST::insert(Range range) {
    insert(range, head.get(), nullptr);
}

bool RangeBST::contains(long long num) const {
    const Node *curr = head.get();

    while (curr != nullptr) {
        if (curr->range.contains(num))
            return true;

        if (num < curr->range.minimum)
            curr = curr->left.get();
        else // num > curr->range.maximum
            curr = curr->right.get();
    }
    return false;
}

long long RangeBST::count() const {
    return count(head.get());
}