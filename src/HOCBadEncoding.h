#pragma once

#include "HOne.h"

class HOCBadEncoding : public HOne {
  private:
    bool distance_one(int index_a, int index_b);

    int l;
    int n;
    bool *bits;

  public:
    void load_data(const uint8_t *data, int l, int n) override;
    void print_pairs() override;
    ~HOCBadEncoding();
};