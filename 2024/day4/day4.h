#pragma once

#include <string>
#include <vector>

class Board {
public:
  struct Error {
    std::string msg;
    Error(const std::string &msg);
  };

private:
  const std::vector<std::string> &board;
  const unsigned int rows;
  const unsigned int cols;

  void checkBounds(unsigned int r, unsigned int c) const;

public:
  Board(const std::vector<std::string> &board);
  unsigned int getRows() const;
  unsigned int getCols() const;
  char get(unsigned int r, unsigned int c) const;
  std::string getLeft(unsigned int r, unsigned int c, unsigned int cnt) const;
  std::string getRight(unsigned int r, unsigned int c, unsigned int cnt) const;
  std::string getTop(unsigned int r, unsigned int c, unsigned int cnt) const;
  std::string getBottom(unsigned int r, unsigned int c, unsigned int cnt) const;
  std::string getTopLeft(unsigned int r, unsigned int c,
                         unsigned int cnt) const;
  std::string getTopRight(unsigned int r, unsigned int c,
                          unsigned int cnt) const;
  std::string getBottomLeft(unsigned int r, unsigned int c,
                            unsigned int cnt) const;
  std::string getBottomRight(unsigned int r, unsigned int c,
                             unsigned int cnt) const;
};

class WordSearch {
  const Board board;
  const std::string word;
  const std::string xword = "MAS";
  std::vector<std::vector<bool>> memo;
  unsigned int wordCnt = 0;
  unsigned int xwordCnt = 0;

  void search();
  void searchX();

public:
  WordSearch(const std::vector<std::string> &board, const std::string word);
  unsigned int getCount() const;
  unsigned int getXCount() const;
};
