#include "day4.h"
#include <iostream>
#include <vector>
#include <set>
#include <array>

int part1::solve(std::istream &is) {
    std::vector<std::vector<char>> grid;

    std::vector<char> line;
    for (;;) {
        char ch;
        is.get(ch);

        if (ch == '\n' || is.eof()) {
            grid.emplace_back(line);
            line.clear();
        } else
            line.push_back(ch);

        if (is.eof())
            break;
        if (!is)
            throw std::runtime_error(
                "An error occurred while reading the input");
    }

    return countAllReachable(grid);
}

int part1::countAllReachable(const std::vector<std::vector<char>> &grid) {
    constexpr int max_neighbors = 3;
    const int rows = grid.size(),
              cols = grid[0].size();

    int count = 0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] != '@')
                continue;

            // edge case: corners
            if ((r == 0 && c == 0)
                || (r == 0 && c == cols - 1)
                || (r == rows - 1 && c == 0)
                || (r == rows - 1 && c == cols - 1)) {
                ++count;
                continue;
            }
            int neighbors = 0;
            // edge case: top row
            if (r == 0) {
                for (auto [x, y] : std::array<std::pair<int, int>, 5>(
                         {{0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}})) {
                    if (grid[r + x][c + y] == '@')
                        ++neighbors;
                }
                if (neighbors <= max_neighbors)
                    ++count;
                continue;
            }
            // edge case: bottom row
            if (r == rows - 1) {
                for (auto [x, y] : std::array<std::pair<int, int>, 5>(
                         {{0, -1}, {0, 1}, {-1, -1}, {-1, 0}, {-1, 1}})) {
                    if (grid[r + x][c + y] == '@')
                        ++neighbors;
                }
                if (neighbors <= max_neighbors)
                    ++count;
                continue;
            }
            // edge case: left col
            if (c == 0) {
                for (auto [x, y] : std::array<std::pair<int, int>, 5>(
                         {{-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}})) {
                    if (grid[r + x][c + y] == '@')
                        ++neighbors;
                }
                if (neighbors <= max_neighbors)
                    ++count;
                continue;
            }
            // edge case: right col
            if (c == cols - 1) {
                for (auto [x, y] : std::array<std::pair<int, int>, 5>(
                         {{-1, 0}, {1, 0}, {-1, -1}, {0, -1}, {1, -1}})) {
                    if (grid[r + x][c + y] == '@')
                        ++neighbors;
                }
                if (neighbors <= max_neighbors)
                    ++count;
                continue;
            }

            for (auto [x, y] : std::array<std::pair<int, int>, 8>(
                 {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                  {0, 1}, {1, -1}, {1, 0}, {1, 1}})) {
                if (grid[r + x][c + y] == '@')
                    ++neighbors;
            }
            if (neighbors <= max_neighbors)
                ++count;
        }
    }
    return count;
}

int part2::solve(std::istream &is) {
    std::vector<std::vector<char>> grid;
    std::set<std::pair<int, int>> loc;

    std::vector<char> line;
    for (int r = 0, c = 0;;) {
        char ch;
        is.get(ch);

        if (ch == '\n' || is.eof()) {
            grid.emplace_back(line);
            line.clear();
            c = 0;
            ++r;
        } else {
            if (ch == '@')
                loc.emplace(r, c);
            line.push_back(ch);
            ++c;
        }

        if (is.eof())
            break;
        if (!is)
            throw std::runtime_error(
                "An error occurred while reading the input");
    }

    return countReachableRecursive(grid, loc);
}

int part2::countReachableRecursive(std::vector<std::vector<char>> &grid,
                                   std::set<std::pair<int, int>> &loc) {
    int count = 0;

    for (std::set<std::pair<int, int>> reached_loc;; reached_loc.clear()) {
        for (auto [r, c] : loc) {
            if (reachable(grid, r, c))
                reached_loc.emplace(r, c);
        }

        count += reached_loc.size();

        for (const auto &p : reached_loc) {
            if (auto it = loc.find(p); it != loc.end()) {
                loc.erase(it);
                grid[p.first][p.second] = '.';
            } else
                throw std::runtime_error("A reached location was not found");
        }

        if (reached_loc.empty())
            break;
    }
    return count;
}

bool part2::reachable(const std::vector<std::vector<char>> &grid,
                      int r, int c) {
    constexpr int max_neighbors = 3;
    const int rows = grid.size(),
              cols = grid[0].size();

    // edge case: corners
    if ((r == 0 && c == 0)
        || (r == 0 && c == cols - 1)
        || (r == rows - 1 && c == 0)
        || (r == rows - 1 && c == cols - 1)) {
        return true;
    }

    int neighbors = 0;
    // edge case: top row
    if (r == 0) {
        for (auto [x, y] : std::array<std::pair<int, int>, 5>(
                 {{0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}})) {
            if (grid[r + x][c + y] == '@')
                ++neighbors;
        }
        return neighbors <= max_neighbors;
    }
    // edge case: bottom row
    if (r == rows - 1) {
        for (auto [x, y] : std::array<std::pair<int, int>, 5>(
                 {{0, -1}, {0, 1}, {-1, -1}, {-1, 0}, {-1, 1}})) {
            if (grid[r + x][c + y] == '@')
                ++neighbors;
        }
        return neighbors <= max_neighbors;
    }
    // edge case: left col
    if (c == 0) {
        for (auto [x, y] : std::array<std::pair<int, int>, 5>(
                 {{-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}})) {
            if (grid[r + x][c + y] == '@')
                ++neighbors;
        }
        return neighbors <= max_neighbors;
    }
    // edge case: right col
    if (c == cols - 1) {
        for (auto [x, y] : std::array<std::pair<int, int>, 5>(
                 {{-1, 0}, {1, 0}, {-1, -1}, {0, -1}, {1, -1}})) {
            if (grid[r + x][c + y] == '@')
                ++neighbors;
        }
        return neighbors <= max_neighbors;
    }

    for (auto [x, y] : std::array<std::pair<int, int>, 8>(
         {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
          {0, 1}, {1, -1}, {1, 0}, {1, 1}})) {
        if (grid[r + x][c + y] == '@')
            ++neighbors;
    }
    return neighbors <= max_neighbors;
}