#pragma once

#include <istream>
#include <set>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

enum Direction { Up, Right, Down, Left };

class Guard {
public:
  class Map {
    unsigned int rows, cols;
    std::pair<unsigned int, unsigned int> start;
    std::set<std::pair<unsigned int, unsigned int>> walls;

  public:
    Map(std::istream &in);
    Map(Map &other);
    std::pair<unsigned int, unsigned int> getStart() const;
    const std::set<std::pair<unsigned int, unsigned int>> &getWalls() const;
    bool contains(unsigned int row, unsigned int col) const;
    void addWall(unsigned int row, unsigned int col);
    bool hasWallAt(unsigned int row, unsigned int col) const;
  };

private:
  const Map &map;
  unsigned int row, col;
  Direction dir = Up;
  std::set<std::pair<unsigned int, unsigned int>> visited;
  std::set<std::tuple<unsigned int, unsigned int, Direction>> wallsVisited;

  void turn();

public:
  struct Leaving {};
  struct Loop {};

  Guard(const Map &map, unsigned int row, unsigned int col);
  Guard(const Map &map, unsigned int row, unsigned int col, Direction dir);
  std::pair<unsigned int, unsigned int> getPos() const;
  Direction getDir() const;
  const std::set<std::pair<unsigned int, unsigned int>> &getVisited() const;
  std::pair<short, short> getUpdate() const;
  bool move();
};
