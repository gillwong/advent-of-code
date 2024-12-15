#pragma once

#include <vector>

void radixSort(std::vector<unsigned int>::iterator begin,
               std::vector<unsigned int>::iterator end,
               const unsigned int max);

void countingSort(std::vector<unsigned int>::iterator begin,
                  std::vector<unsigned int>::iterator end,
                  const unsigned int limit);
