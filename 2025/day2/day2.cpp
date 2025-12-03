#include "day2.h"
#include <iostream>

long long part1::solve(std::istream &is) {
    long long sum = 0;
    for (;;) {
        long long begin, end;
        char temp;
        is >> begin >> temp >> end;

        sum += sumInvalidIDs(begin, end);

        if (is.eof())
            break;
        if (!is)
            throw std::runtime_error(
                "An error occurred while reading the input");

        is >> temp;
    }
    return sum;
}

long long part1::sumInvalidIDs(long long begin, long long end) {
    long long sum = 0;
    for (long long id = begin; id <= end; ++id) {
        const int digits = countDigits(id);
        if (digits % 2 != 0)
            continue;

        bool invalid = true;
        for (int i = digits, j = digits / 2; i > j && j > 0; --i, --j) {
            if (getDigit(id, i) != getDigit(id, j)) {
                invalid = false;
                break;
            }
        }
        if (invalid)
            sum += id;
    }
    return sum;
}

long long part2::solve(std::istream &is) {
    long long sum = 0;
    for (;;) {
        long long begin, end;
        char temp;
        is >> begin >> temp >> end;

        sum += sumInvalidIDs(begin, end);

        if (is.eof())
            break;
        if (!is)
            throw std::runtime_error(
                "An error occurred while reading the input");

        is >> temp;
    }
    return sum;
}

long long part2::sumInvalidIDs(long long begin, long long end) {
    long long sum = 0;
    for (long long id = begin; id <= end; ++id) {
        const int digits = countDigits(id);

        for (int seq_sz = 1; seq_sz <= digits / 2; ++seq_sz) {
            // skip sizes which do not fit into digits
            if (digits % seq_sz != 0)
                continue;

            // seq is the first seq_sz digits in id
            long long seq = id / pow10(digits - seq_sz);

            bool invalid = true;
            for (int i = digits - seq_sz; i > 0;) {
                for (int j = i, k = seq_sz; k > 0; --j, --k) {
                    if (getDigit(id, j) != getDigit(seq, k)) {
                        invalid = false;
                        break;
                    }
                }
                if (!invalid)
                    break;

                i -= seq_sz;
                if (i < seq_sz)
                    break;
            }

            if (invalid) {
                sum += id;
                break;
            }
        }
    }
    return sum;
}

int countDigits(long long id) {
    int digits = 0;
    for (; id > 0; id /= 10)
        ++digits;
    return digits;
}

int getDigit(const long long &id, int pos) {
    return static_cast<int>(id % pow10(pos) / pow10(pos - 1));
}

long long pow10(int exp) {
    long long result = 1;
    for (; exp > 0; --exp)
        result *= 10;
    return result;
}