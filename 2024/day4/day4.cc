#include "day4.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using std::cout;
using std::endl;

Board::Error::Error(const std::string &msg) : msg(msg) {}

Board::Board(const std::vector<std::string> &board)
    : board(board), rows(board.size()), cols(board.front().size()) {}

unsigned int Board::getRows() const { return rows; }

unsigned int Board::getCols() const { return cols; }

void Board::checkBounds(unsigned int r, unsigned int c) const {
  if (r >= rows || c >= cols)
    throw Error("Out of bounds.");
}

char Board::get(unsigned int r, unsigned int c) const { return board[r][c]; }

std::string Board::getLeft(unsigned int r, unsigned int c,
                           unsigned int cnt) const {
  checkBounds(r, c);
  checkBounds(r, c - cnt + 1);
  std::ostringstream oss;
  for (; cnt > 0; cnt -= 1, c -= 1) {
    oss << board[r][c];
  }
  return oss.str();
}

std::string Board::getRight(unsigned int r, unsigned int c,
                            unsigned int cnt) const {
  checkBounds(r, c);
  checkBounds(r, c + cnt - 1);
  std::ostringstream oss;
  for (; cnt > 0; cnt -= 1, c += 1) {
    oss << board[r][c];
  }
  return oss.str();
}

std::string Board::getTop(unsigned int r, unsigned int c,
                          unsigned int cnt) const {
  checkBounds(r, c);
  checkBounds(r - cnt + 1, c);
  std::ostringstream oss;
  for (; cnt > 0; cnt -= 1, r -= 1) {
    oss << board[r][c];
  }
  return oss.str();
}

std::string Board::getBottom(unsigned int r, unsigned int c,
                             unsigned int cnt) const {
  checkBounds(r, c);
  checkBounds(r + cnt - 1, c);
  std::ostringstream oss;
  for (; cnt > 0; cnt -= 1, r += 1) {
    oss << board[r][c];
  }
  return oss.str();
}

std::string Board::getTopLeft(unsigned int r, unsigned int c,
                              unsigned int cnt) const {
  checkBounds(r, c);
  checkBounds(r - cnt + 1, c - cnt + 1);
  std::ostringstream oss;
  for (; cnt > 0; cnt -= 1, r -= 1, c -= 1) {
    oss << board[r][c];
  }
  return oss.str();
}

std::string Board::getTopRight(unsigned int r, unsigned int c,
                               unsigned int cnt) const {
  checkBounds(r, c);
  checkBounds(r - cnt + 1, c + cnt - 1);
  std::ostringstream oss;
  for (; cnt > 0; cnt -= 1, r -= 1, c += 1) {
    oss << board[r][c];
  }
  return oss.str();
}

std::string Board::getBottomLeft(unsigned int r, unsigned int c,
                                 unsigned int cnt) const {
  checkBounds(r, c);
  checkBounds(r + cnt - 1, c - cnt + 1);
  std::ostringstream oss;
  for (; cnt > 0; cnt -= 1, r += 1, c -= 1) {
    oss << board[r][c];
  }
  return oss.str();
}

std::string Board::getBottomRight(unsigned int r, unsigned int c,
                                  unsigned int cnt) const {
  checkBounds(r, c);
  checkBounds(r + cnt - 1, c + cnt - 1);
  std::ostringstream oss;
  for (; cnt > 0; cnt -= 1, r += 1, c += 1) {
    oss << board[r][c];
  }
  return oss.str();
}

WordSearch::WordSearch(const std::vector<std::string> &board,
                       const std::string word)
    : board(board), word(word),
      memo(board.size(), std::vector<bool>(board.front().size(), true)) {
  search();
  searchX();
}

void WordSearch::search() {
  for (unsigned int i = 0; i < board.getRows(); i += 1) {
    for (unsigned int j = 0; j < board.getCols(); j += 1) {
      if (!memo[i][j])
        continue;
      try {
        if (board.getLeft(i, j, word.length()) == word) {
          wordCnt += 1;
          for (unsigned int cnt = word.length(), k = j; cnt > 0;
               cnt -= 1, k -= 1) {
            memo[i][k] = false;
          }
        }
      } catch (Board::Error &) {
      }
      try {
        if (board.getRight(i, j, word.length()) == word) {
          wordCnt += 1;
          for (unsigned int cnt = word.length(), k = j; cnt > 0;
               cnt -= 1, k += 1) {
            memo[i][k] = false;
          }
        }
      } catch (Board::Error &) {
      }
      try {
        if (board.getTop(i, j, word.length()) == word) {
          wordCnt += 1;
          for (unsigned int cnt = word.length(), k = i; cnt > 0;
               cnt -= 1, k -= 1) {
            memo[k][j] = false;
          }
        }
      } catch (Board::Error &) {
      }
      try {
        if (board.getBottom(i, j, word.length()) == word) {
          wordCnt += 1;
          for (unsigned int cnt = word.length(), k = i; cnt > 0;
               cnt -= 1, k += 1) {
            memo[k][j] = false;
          }
        }
      } catch (Board::Error &) {
      }
      try {
        if (board.getTopLeft(i, j, word.length()) == word) {
          wordCnt += 1;
          for (unsigned int cnt = word.length(), k = i, l = j; cnt > 0;
               cnt -= 1, k -= 1, l -= 1) {
            memo[k][l] = false;
          }
        }
      } catch (Board::Error &) {
      }
      try {
        if (board.getTopRight(i, j, word.length()) == word) {
          wordCnt += 1;
          for (unsigned int cnt = word.length(), k = i, l = j; cnt > 0;
               cnt -= 1, k -= 1, l += 1) {
            memo[k][l] = false;
          }
        }
      } catch (Board::Error &) {
      }
      try {
        if (board.getBottomLeft(i, j, word.length()) == word) {
          wordCnt += 1;
          for (unsigned int cnt = word.length(), k = i, l = j; cnt > 0;
               cnt -= 1, k += 1, l -= 1) {
            memo[k][l] = false;
          }
        }
      } catch (Board::Error &) {
      }
      try {
        if (board.getBottomRight(i, j, word.length()) == word) {
          wordCnt += 1;
          for (unsigned int cnt = word.length(), k = i, l = j; cnt > 0;
               cnt -= 1, k += 1, l += 1) {
            memo[k][l] = false;
          }
        }
      } catch (Board::Error &) {
      }
    }
  }
}

void WordSearch::searchX() {
  for (unsigned int i = 1; i < board.getRows() - 1; i += 1) {
    for (unsigned int j = 1; j < board.getCols() - 1; j += 1) {
      if (board.get(i, j) != 'A')
        continue;
      try {
        if ((board.getBottomRight(i - 1, j - 1, xword.length()) == xword ||
             board.getTopLeft(i + 1, j + 1, xword.length()) == xword) &&
            (board.getBottomLeft(i - 1, j + 1, xword.length()) == xword ||
             board.getTopRight(i + 1, j - 1, xword.length()) == xword))
          xwordCnt += 1;
      } catch (Board::Error &) {
      }
    }
  }
}

unsigned int WordSearch::getCount() const { return wordCnt; }

unsigned int WordSearch::getXCount() const { return xwordCnt; }
