#pragma once

#include <fstream>
#include <ostream>
#include <string>
#include <tuple>
#include <utility>

struct CmdError {
  std::string msg;
  CmdError(const std::string &msg);
};

std::pair<std::ifstream *, std::ostream *> processArgs(int argc, char *argv[]);

std::tuple<std::ifstream *, std::ostream *, unsigned int>
processMultiArgs(int argc, char *argv[]);
