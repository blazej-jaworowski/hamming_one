#include <cstddef>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>

#include "HOCBadEncoding.h"
#include "HOCGoodEncoding.h"

int main(int argc, char **argv) {
    const char *filename = argc > 1 ? argv[1] : "bit_sequences_1000_10000_100";

    int l, n, correct_result;
    sscanf(filename, "bit_sequences_%d_%d_%d", &l, &n, &correct_result);

    std::fstream file;
    file.open(filename, std::ios::in | std::ios::binary);
    int size = (l * n - 1) / 8 + 1;

    uint8_t *data = new uint8_t[size]();

    std::cout << "Reading data.\n";

    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0;; j++) {
            char c;
            file.read(&c, 1);
            if (c == '\n')
                break;
            if (c != '0')
                data[index / 8] |= (0b10000000 >> (index % 8));
            index++;
        }
    }

    std::cout << "Data read.\n";

    HOCGoodEncoding hone;
    hone.load_data(data, l, n);
    delete[] data;

    auto pairs = hone.get_pairs();
    // for(const auto& [p1, p2] : pairs) {
    //     std::cout << p1 << ' ' << p2 << '\n';
    // }
    std::cout << "Expected: " << correct_result << "\n"
              << "Got:      " << pairs.size() << '\n';

    return 0;
}