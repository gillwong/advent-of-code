#include "day3.h"
#include <istream>
#include <sstream>
#include <string>

Lexer::Error::Error(const std::string &msg) : msg(msg) {}

Lexer::Lexer(std::istream &in) : in(in) {}

bool Lexer::inspect(const char ch) {
  char seen = in.peek();
  return !in.fail() && seen == ch;
}

bool Lexer::inspect(const std::string &s) {
  bool result = true;
  std::string::size_type i = 0;
  for (char seen; i < s.length(); i += 1) {
    in >> seen;
    if (in.fail() || seen != s[i]) {
      result = false;
      break;
    }
  }
  if (i == s.length()) {
    for (; i > 0; i -= 1) {
      in.unget();
    }
  } else {
    for (;; i -= 1) {
      in.unget();
      if (i == 0)
        break;
    }
  }
  return result;
}

bool Lexer::inspectDigit() {
  int seen = in.peek() - '0';
  return !in.fail() && seen >= 0 && seen <= 9;
}

char Lexer::consume(const char ch) {
  char seen = in.peek();
  if (in.fail())
    throw Error("Failed to read input stream.");
  if (seen != ch)
    throw Error(std::string("Expected ") + ch + ", got " + seen + " instead.");
  in >> seen;
  return seen;
}

std::string Lexer::consume(const std::string &s) {
  std::ostringstream result;
  std::string::size_type i = 0;
  try {
    for (char seen; i < s.length(); i += 1) {
      in >> seen;
      if (in.fail())
        throw Error("Failed to read input stream.");
      result << seen;
      if (seen != s[i])
        throw Error(std::string("Expected ") + s + ", got " + result.str() +
                    " instead.");
    }
  } catch (Error &e) {
    for (;; i -= 1) {
      in.unget();
      if (i == 0)
        break;
    }
    throw e;
  }
  return result.str();
}

char Lexer::consumeDigit() {
  int seen = in.peek() - '0';
  if (in.fail())
    throw Error("Failed to read input stream.");
  if (seen < 0 || seen > 9)
    throw Error(std::string("Expected a digit, got ") + (char)in.peek() +
                " instead.");
  return in.get() - '0';
}

Parser::Parser(std::istream &in) : l(in) {
  for (; !in.fail();) {
    try {
      if (l.inspect('m')) {
        unsigned int m = mul();
        result += m;
        if (enabled)
          enabledResult += m;
        continue;
      }
      if (l.inspect('d')) {
        if (l.inspect("don")) {
          dont();
          continue;
        }
        if (l.inspect("do(")) {
          do_();
          continue;
        }
      }
    } catch (Lexer::Error &e) {
      // ignore lexer errors
    }
    in.get();
  }
}

unsigned int Parser::mul() {
  l.consume("mul(");
  unsigned int op1 = num();
  l.consume(',');
  unsigned int op2 = num();
  l.consume(')');
  return op1 * op2;
}

unsigned int Parser::num() {
  const char base = 10, maxDigits = 3;
  unsigned int num = l.consumeDigit();
  for (char i = 1; l.inspectDigit() && i < maxDigits; i += 1) {
    num = (num * base) + l.consumeDigit();
  }
  return num;
}

void Parser::dont() {
  l.consume("don't()");
  enabled = false;
}

void Parser::do_() {
  l.consume("do()");
  enabled = true;
}

unsigned int Parser::getResult() { return result; }
unsigned int Parser::getEnabledResult() { return enabledResult; }
