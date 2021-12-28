#pragma once

#include "HOne.h"

class HOCBadEncoding : HOne {
private:
    bool distance_one(int index_a, int index_b);

    int l;
    int n;
    bool * bits; 
public:
    void load_data(const uint8_t * data, int l, int n) override;
    std::vector<std::pair<int, int>> get_pairs() override;
    ~HOCBadEncoding();
};