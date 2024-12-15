#pragma once

#include <iostream>
#include <string>
#include <utility>

struct CmdError {
  std::string msg;
  CmdError(const std::string &msg);
};

std::pair<std::ifstream *, std::ostream *> processArgs(int argc, char *argv[]);
