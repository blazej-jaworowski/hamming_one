#pragma once

#include <cstddef>
#include <cstdint>
#include <utility>
#include <vector>

class HOne {
  public:
    virtual void load_data(const uint8_t *data, int l, int n) = 0;
    virtual void print_pairs() = 0;
};