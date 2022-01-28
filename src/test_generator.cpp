#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

int main(int argc, char **argv) {
    int l = 1000;
    int n = 100000;
    int num_pairs = 10;

    switch (argc) {
    case 1:
        break;
    case 4:
        l = atoi(argv[1]);
        n = atoi(argv[2]);
        num_pairs = atoi(argv[3]);
        if (l == 0 || n == 0 || num_pairs == 0) {
            std::cerr << "Invalid arguments\n";
            return -1;
        }
        break;
    case 3:
        l = atoi(argv[1]);
        n = atoi(argv[2]);
        if (l == 0 || n == 0) {
            std::cerr << "Invalid arguments\n";
            return -1;
        }
        break;
    default:
    case 2:
        std::cerr << "Invalid number of arguments.\n";
        return -1;
    }

    std::stringstream filename;
    filename << "bit_sequences_" << l << '_' << n << '_' << num_pairs;

    srand(0);

    std::vector<bool *> bits;

    for (int i = 0; i < n; i++) {
        bool *new_bits = new bool[l];
        int bit_index = 0;
        for (int j = 0; j < l; j++) {
            new_bits[bit_index++] = rand() % 2;
        }
        bits.push_back(new_bits);

        if (num_pairs > 0 &&
            (n - i < num_pairs || rand() % ((n - i) / num_pairs) == 0)) {
            const bool *to_copy = bits[rand() % bits.size()];
            new_bits = new bool[l];
            std::memcpy(new_bits, to_copy, l);
            int change = rand() % l;
            new_bits[change] = !new_bits[change];
            bits.push_back(new_bits);
            i++;
            num_pairs--;
        }
    }

    std::fstream file(filename.str(), std::fstream::out | std::fstream::trunc);

    for (const bool *b : bits) {
        for (int i = 0; i < l; i++) {
            file << b[i] ? '1' : '0';
        }
        file << '\n';
        delete[] b;
    }

    file.close();
}