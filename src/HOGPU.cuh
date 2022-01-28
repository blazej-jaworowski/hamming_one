#pragma once

#include "HOne.h"

class HOGPU : public HOne {
  private:
    uint32_t *data;
    int dword_length;
    int n;

  public:
    void load_data(const uint8_t *data, int l, int n) override;
    void print_pairs() override;
    ~HOGPU();
};