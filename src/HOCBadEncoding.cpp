#include "HOCBadEncoding.h"
#include <cstdio>

void HOCBadEncoding::load_data(const uint8_t *data, int l, int n) {
    this->l = l;
    this->n = n;

    bits = new bool[n * l];

    int bit_index = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < l; j++) {
            bits[i * l + j] =
                ((data[bit_index / 8] >> (7 - bit_index % 8))) & 1;
            bit_index++;
        }
    }
}

HOCBadEncoding::~HOCBadEncoding() { delete[] bits; }

void HOCBadEncoding::print_pairs() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (distance_one(i, j)) {
                printf("%d %d\n", j, i);
            }
        }
    }
}

bool HOCBadEncoding::distance_one(int index_a, int index_b) {
    bool differing = false;
    for (int i = 0; i < l; i++) {
        if (bits[index_a * l + i] != bits[index_b * l + i]) {
            if (differing)
                return false;
            differing = true;
        }
    }
    return differing;
}