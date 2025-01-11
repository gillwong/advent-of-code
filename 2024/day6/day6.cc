#include "day6.h"
#include <istream>
#include <stdexcept>
#include <string>
#include <vector>

#include <iostream>
using std::cout;
using std::endl;

Guard::Map::Map(std::istream &in) {
  unsigned int row = 0;
  for (std::string line; std::getline(in, line); row += 1) {
    if (row == 0)
      cols = line.length();
    if (line.find('^') != std::string::npos) {
      start = {row, line.find('^')};
    }
    for (std::string::size_type i = 0;;) {
      i = line.find('#', i);
      if (i == std::string::npos)
        break;
      walls.emplace(row, i);
      i += 1;
    }
  }
  rows = row;
}

Guard::Map::Map(Guard::Map &other)
    : rows(other.rows), cols(other.cols), start(other.start),
      walls(other.walls) {}

std::pair<unsigned int, unsigned int> Guard::Map::getStart() const {
  return start;
}

const std::set<std::pair<unsigned int, unsigned int>> &
Guard::Map::getWalls() const {
  return walls;
}

bool Guard::Map::contains(unsigned int row, unsigned int col) const {
  return row < rows && col < cols;
}

void Guard::Map::addWall(unsigned int row, unsigned int col) {
  if (contains(row, col)) {
    walls.emplace(row, col);
  }
}

bool Guard::Map::hasWallAt(unsigned int row, unsigned int col) const {
  return walls.count({row, col}) != 0;
}

Guard::Guard(const Map &map, unsigned int row, unsigned int col)
    : map(map), row(row), col(col) {}

Guard::Guard(const Map &map, unsigned int row, unsigned int col, Direction dir)
    : map(map), row(row), col(col), dir(dir) {}

void Guard::turn() {
  switch (dir) {
  case Up:
    dir = Right;
    break;
  case Right:
    dir = Down;
    break;
  case Down:
    dir = Left;
    break;
  case Left:
    dir = Up;
    break;
  }
}

std::pair<unsigned int, unsigned int> Guard::getPos() const {
  return {row, col};
}

Direction Guard::getDir() const { return dir; }

const std::set<std::pair<unsigned int, unsigned int>> &
Guard::getVisited() const {
  return visited;
}

std::pair<short, short> Guard::getUpdate() const {
  int rowUpdate = 0, colUpdate = 0;
  switch (dir) {
  case Up:
    rowUpdate = -1;
    break;
  case Right:
    colUpdate = 1;
    break;
  case Down:
    rowUpdate = 1;
    break;
  case Left:
    colUpdate = -1;
    break;
  }
  return {rowUpdate, colUpdate};
}

bool Guard::move() {
  bool wasNew = visited.emplace(row, col).second;

  auto update = getUpdate();
  int rowUpdate = update.first, colUpdate = update.second;
  row += rowUpdate;
  col += colUpdate;

  if (!map.contains(row, col)) {
    throw Leaving();
  }
  if (map.hasWallAt(row, col)) {
    if (!wallsVisited.emplace(row, col, dir).second) {
      throw Loop();
    }
    // rollback updates
    row -= rowUpdate;
    col -= colUpdate;

    turn();
    return wasNew;
  }
  return wasNew;
}
