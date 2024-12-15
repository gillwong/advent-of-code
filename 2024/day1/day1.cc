#include "day1.h"
#include <algorithm>
#include <vector>

void radixSort(std::vector<unsigned int>::iterator begin,
               std::vector<unsigned int>::iterator end,
               const unsigned int max) {
  using container = std::vector<unsigned int>;
  using size_type = container::size_type;

  const size_type sz = end - begin;
  const char bits = 12;
  const size_type buckets = 1 << bits;
  const unsigned int mask = buckets - 1;

  container copy(sz);
  for (size_type pos = 0; max >> (pos * bits) > 0; pos += 1) {
    size_type bucket[buckets] = {0};

    // stable sort using counting sort
    for (container::iterator it = begin; it != end; ++it) {
      bucket[(*it >> (pos * bits)) & mask] += 1;
    }
    for (size_type i = 1; i < buckets; i += 1) {
      bucket[i] += bucket[i - 1];
    }
    for (container::iterator it = end - 1;; --it) {
      copy[bucket[(*it >> (pos * bits)) & mask] - 1] = *it;
      bucket[(*it >> (pos * bits)) & mask] -= 1;
      if (it == begin)
        break;
    }
    std::copy(copy.begin(), copy.end(), begin);
  }
}

void countingSort(std::vector<unsigned int>::iterator begin,
                  std::vector<unsigned int>::iterator end,
                  const unsigned int limit) {
  using container = std::vector<unsigned int>;
  using size_type = container::size_type;

  container copy(begin, end);
  std::vector<size_type> count(limit);
  // get count of each value
  for (container::iterator it = begin; it != end; ++it) {
    count[*it - 1] += 1;
  }
  // accumulate count of values less than or equal to value
  for (size_type i = 1; i < limit; i += 1) {
    count[i] += count[i - 1];
  }

  for (container::reverse_iterator it = copy.rbegin(); it != copy.rend();
       ++it) {
    *(begin + (count[*it - 1] - 1)) = *it;
    count[*it - 1] -= 1;
  }
}
