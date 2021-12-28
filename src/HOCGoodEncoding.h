#pragma once

#include "HOne.h"

class HOCGoodEncoding : HOne {
  private:
    uint32_t * bits;
    int l;
    int n;
    int s;
  public:
    void load_data(const uint8_t *data, int l, int n) override;
    std::vector<std::pair<int, int>> get_pairs() override;
    ~HOCGoodEncoding();
};