#include "day3.h"
#include <iostream>
#include <vector>
#include <algorithm>

int part1::solve(std::istream &is) {
    int sum = 0;
    std::vector<char> bank;
    for (;;) {
        char ch;
        is.get(ch);

        if (ch == '\n' || is.eof()) {
            sum += maxCapacity(bank);
            bank.clear();
        } else
            bank.push_back(ch - '0');

        if (is.eof())
            break;
        if (!is)
            throw std::runtime_error(
                "An error occurred while reading the input");
    }
    return sum;
}

int part1::maxCapacity(const std::vector<char> &bank) {
    std::vector<char> max_suffix(bank.size() - 1);
    char max_suffix_seen = 0;
    for (auto i = bank.size() - 1; i != 0; --i) {
        max_suffix_seen = std::max(max_suffix_seen, bank[i]);
        max_suffix[i - 1] = max_suffix_seen;
    }

    int max_capacity = 0;
    for (std::vector<char>::size_type i = 0; i < max_suffix.size(); ++i)
        max_capacity = std::max(max_capacity, bank[i] * 10 + max_suffix[i]);

    return max_capacity;
}

long long part2::solve(std::istream &is) {
    long long sum = 0;
    std::vector<char> bank;
    for (;;) {
        char ch;
        is.get(ch);

        if (ch == '\n' || is.eof()) {
            sum += maxCapacity(bank);
            bank.clear();
        } else
            bank.push_back(ch - '0');

        if (is.eof())
            break;
        if (!is)
            throw std::runtime_error(
                "An error occurred while reading the input");
    }
    return sum;
}

long long part2::maxCapacity(const std::vector<char> &bank) {
    // initialization
    std::vector<long long>::size_type
        max_capacities_sz = bank.size(), max_suffix_sz = bank.size() - 1;
    std::vector<long long> max_capacities(max_capacities_sz);
    for (std::vector<long long>::size_type i = 0; i < max_capacities_sz; i++)
        max_capacities[i] = bank[i];
    std::vector<long long> max_suffix(max_suffix_sz);

    for (int i = 0; i < 11; ++i) {
        long long max_suffix_seen = 0;
        for (auto j = max_capacities_sz; j != 0; --j) {
            max_suffix_seen = std::max(max_suffix_seen, max_capacities[j]);
            max_suffix[j - 1] = max_suffix_seen;
        }

        max_capacities.resize(--max_capacities_sz);
        for (std::vector<long long>::size_type j = 0;
             j < max_capacities_sz; ++j) {
            max_capacities[j] = bank[j] * pow10(i + 1) + max_suffix[j];
        }

        max_suffix.resize(--max_suffix_sz);
    }

    long long result = 0;
    for (const auto &cap : max_capacities)
        result = std::max(result, cap);
    return result;
}

long long pow10(int exp) {
    long long result = 1;
    for (; exp > 0; --exp)
        result *= 10;
    return result;
}