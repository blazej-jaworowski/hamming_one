#include "HOCGoodEncoding.h"

#include <iostream>

void HOCGoodEncoding::load_data(const uint8_t *data, int l, int n) {
    this->l = l;
    this->n = n;

    s = (l - 1) / 32 + 1;
    bits = new uint32_t[s * n]();

    int bit_index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < l; j++) {
            bool bit = ((data[bit_index / 8] >> (7 - bit_index % 8))) & 1;

            bits[i * s + j / 32] |= bit << (31 - j % 32);
            bit_index++;
        }
    }
}

std::vector<std::pair<int, int>> HOCGoodEncoding::get_pairs() {
    std::vector<std::pair<int, int>> r;
    for (int i = 1; i < n; i++) {
        for(int j = 0; j < i; j++) {
            bool distance_one = false;
            bool differs = false;
            for(int k = 0; k < s; k++) {
                uint32_t prod = bits[i * s + k] ^ bits[j * s + k];
                if(prod == 0) continue;
                if((prod & (prod - 1)) == 0) {
                    if(differs) {
                        distance_one = false;
                        break;
                    }
                    differs = true;
                    distance_one = true;
                    continue;
                }
                distance_one = false;
                break;
            }

            if(distance_one) {
                 r.emplace_back(j, i);
            }
        }
        if(i % 1000 == 999) std::cout << i << '\n';
    }
    return r;
}

HOCGoodEncoding::~HOCGoodEncoding() { delete[] bits; }