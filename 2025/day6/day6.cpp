#include "day6.h"
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <format>

unsigned long long part1::solve(std::istream &is) {
    std::vector<std::vector<unsigned int>> lines;
    for (std::vector<unsigned int> line;;) {
        unsigned int num;
        is >> num;

        line.push_back(num);

        if (is.peek() == '\n') {
            lines.emplace_back(line);
            line.clear();

            char ch;
            is >> ch;
            is.unget();
            if (!std::isdigit(ch))
                break;
        }
    }

    unsigned long long total = 0;
    const size_t problem_sz = lines.size();
    for (size_t i = 0;; ++i) {
        char ch;
        is >> ch;

        if (is.eof())
            break;
        if (!is)
            throw std::runtime_error(
                "An error occurred while reading the input");

        unsigned long long result;
        switch (ch) {
        case '*':
            result = 1;
            for (size_t j = 0; j < problem_sz; ++j)
                result *= lines[j][i];
            break;
        case '+':
            result = 0;
            for (size_t j = 0; j < problem_sz; ++j)
                result += lines[j][i];
            break;
        default:
            throw std::runtime_error(std::format("Unknown character: {}", ch));
        }
        total += result;
    }
    return total;
}

unsigned long long part2::solve(std::istream &is) {
    std::vector<std::string> lines;
    std::string last;
    for (;;) {
        std::string line;
        std::getline(is, line);

        if (line[0] == '*' || line[0] == '+') {
            last = line;
            break;
        }

        lines.emplace_back(line);
    }
    last += ' ';

    unsigned long long total = 0;
    for (size_t i = 0; i < last.length(); ++i) {
        char ch = last[i];
        if (ch == ' ')
            continue;

        size_t j = 0;
        for (;; ++j) {
            if (i + j + 1 == last.length() || last[i + j + 1] != ' ')
                break;
        }

        std::vector<unsigned int> problem(j, -1);
        for (auto it = lines.cbegin(); it != lines.cend(); ++it) {
            for (size_t k = 0; k < j; ++k) {
                if ((*it)[i + k] == ' ')
                    continue;
                if (problem[k] == static_cast<unsigned int>(-1)) {
                    problem[k] = (*it)[i + k] - '0';
                    continue;
                }
                problem[k] = 10 * problem[k] + ((*it)[i + k] - '0');
            }
        }

        unsigned long long result;
        switch (ch) {
        case '*':
            result = 1;
            for (auto num : problem)
                result *= num;
            break;
        case '+':
            result = 0;
            for (auto num : problem)
                result += num;
            break;
        default:
            throw std::runtime_error(
                std::format("Unknown character: {}", ch));
        }
        total += result;

        i += j;
    }
    return total;
}