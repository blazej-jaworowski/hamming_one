#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>
#include <utility>

class HOne {
public:
    virtual void load_data(const uint8_t * data, int l, int n) = 0;
    virtual std::vector<std::pair<int, int>> get_pairs() = 0;
};