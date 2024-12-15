#include "utils.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>

CmdError::CmdError(const std::string &msg) : msg(msg) {}

std::pair<std::ifstream *, std::ostream *> processArgs(int argc, char *argv[]) {
  std::ifstream *in;
  std::ostream *out = &std::cout;
  try {
    switch (argc) {
    case 3:
      out = new std::ofstream();
      dynamic_cast<std::ofstream *>(out)->open(argv[2]);
    case 2:
      in = new std::ifstream();
      in->open(argv[1]);
      if (!in->is_open())
        throw CmdError(std::string("Failed to read input file ") + argv[1]);
      break;
    default:
      throw CmdError("Invalid number of arguments!");
    }
  } catch (CmdError &e) {
    std::cerr << e.msg << "\n"
              << "Usage: " << argv[0] << " input-file [ output-file ]"
              << std::endl;
    exit(EXIT_FAILURE);
  }

  return std::make_pair(in, out);
}
