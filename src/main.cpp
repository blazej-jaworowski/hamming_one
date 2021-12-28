#include <iostream>
#include <fstream>
#include <cstddef>
#include <cstdint>
#include <cstring>

#include "HOCBadEncoding.h"

int main(int argc, char **argv) {
    std::fstream file;

    int l = 1000;
    int n = 100000;
    file.open("bit_sequences_1000_100000_1000", std::ios::in | std::ios::binary);
    int size = (l * n - 1) / 8 + 1;

    uint8_t * data = new uint8_t[size]();

    std::cout << "Reading data.\n";

    int index = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0;; j++) {
            char c;
            file.read(&c, 1);
            if(c == '\n') break;
            if(c != '0') data[index / 8] |= (0b10000000 >> (index % 8));
            index++;
        }
    }

    std::cout << "Data read.\n";

    HOCBadEncoding hone;
    hone.load_data(data, l, n);
    delete[] data;

    for(const auto& [p1, p2] : hone.get_pairs()) {
        std::cout << p1 << ' ' << p2 << '\n';
    }

    return 0;
}