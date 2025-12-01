#include "day1.h"

#include <iostream>
#include <string>
#include <format>

constexpr int initial_pos = 50;
constexpr int limit = 100;

int part1(std::istream &is) {
    int count = 0, pos = initial_pos;
    for (;;) {
        char dir;
        int step;
        is >> dir >> step;

        switch (dir) {
        case 'L':
            pos -= step;
            break;
        case 'R':
            pos += step;
            break;
        default:
            throw std::runtime_error(std::format("Unknown direction: {}", dir));
        }
        pos = (pos % limit + limit) % limit;
        if (pos == 0)
            ++count;

        if (is.eof())
            break;
        if (!is)
            throw std::runtime_error(
                "An error occurred while reading the input");
    }
    return count;
}

int part2(std::istream &is) {
    int count = 0, pos = initial_pos;
    for (;;) {
        char dir;
        int step;
        is >> dir >> step;

        switch (dir) {
        case 'L':
            for (; step > 0; --step) {
                if (pos == 0)
                    pos = limit;
                --pos;
                if (pos == 0)
                    ++count;
            }
            break;
        case 'R':
            for (; step > 0; --step) {
                if (pos == limit)
                    pos = 0;
                ++pos;
                if (pos == limit)
                    ++count;
            }
            break;
        default:
            throw std::runtime_error(std::format("Unknown direction: {}", dir));
        }

        if (is.eof())
            break;
        if (!is)
            throw std::runtime_error(
                "An error occurred while reading the input");
    }
    return count;
}