#pragma once

#include <istream>
#include <string>

class Lexer {
  std::istream &in;

public:
  struct Error {
    std::string msg;
    Error(const std::string &msg);
  };

  Lexer(std::istream &in);
  bool inspect(const char ch);
  bool inspect(const std::string &s);
  bool inspectDigit();
  char consume(const char ch);
  std::string consume(const std::string &s);
  char consumeDigit();
};

class Parser {
  Lexer l;
  unsigned int result = 0, enabledResult = 0;
  bool enabled = true;

public:
  Parser(std::istream &in);
  unsigned int getResult();
  unsigned int getEnabledResult();
  unsigned int mul();
  unsigned int num();
  void dont();
  void do_();
};
