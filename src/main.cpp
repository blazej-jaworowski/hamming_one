#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>

#include "HOCBadEncoding.h"
#include "HOCGoodEncoding.h"
#include "HOGPU.cuh"
#include "HOne.h"

void save_log(std::string log_file, int method, int l, int n,
              long load_duration, long print_duration) {
    std::ofstream file(log_file, std::ios::app);
    file << method << ',' << l << ',' << n << ',' << load_duration << ','
         << print_duration << '\n';
    file.close();
}

int main(int argc, char **argv) {
    HOne *hone;
    int method = 2;
    if (argc > 1) {
        method = atoi(argv[1]);
    }
    switch (method) {
    case 0:
        hone = new HOCBadEncoding();
        break;
    case 1:
        hone = new HOCGoodEncoding();
        break;
    case 2:
        hone = new HOGPU();
    }

    const char *filename = argc > 2 ? argv[2] : "bit_sequences_1000_10000_100";

    int l, n, correct_result;
    sscanf(filename, "bit_sequences_%d_%d_%d", &l, &n, &correct_result);

    std::fstream file;
    file.open(filename, std::ios::in | std::ios::binary);
    int size = (l * n - 1) / 8 + 1;

    uint8_t *data = new uint8_t[size]();

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

    auto time = std::chrono::high_resolution_clock::now();
    hone->load_data(data, l, n);
    auto load_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
                             std::chrono::high_resolution_clock::now() - time)
                             .count();
    delete[] data;

    time = std::chrono::high_resolution_clock::now();
    hone->print_pairs();
    auto print_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
                              std::chrono::high_resolution_clock::now() - time)
                              .count();

    save_log("log", method, l, n, load_duration, print_duration);

    delete hone;

    return 0;
}