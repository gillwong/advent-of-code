#include <iostream>
#include <string>
#include <format>
#include <fstream>
#include "day1.h"

struct CmdError final : std::runtime_error {
    explicit CmdError(const std::string &msg) : std::runtime_error(msg) {
    }
};

int main(int argc, char *argv[]) {
    try {
        if (argc != 2)
            throw CmdError(
                std::format("Invalid number of arguments: {}", argc));

        std::ifstream infile(argv[1]);
        std::cout << "Part 1: " << part1(infile) << "\n";
        infile.close();

        infile.open(argv[1]);
        std::cout << "Part 2: " << part2(infile) << "\n";
    } catch (CmdError &err) {
        std::cerr << "Command error: " << err.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred" << std::endl;
    }
}