#include "HOGPU.cuh"

#include <cstdio>

void HOGPU::load_data(const uint8_t *data, int l, int n) {
    dword_length = (l - 1) / 32 + 1;
    this->n = n;

    uint32_t *host_data = new uint32_t[n * dword_length]();

    int bit_index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < l; j++) {
            bool bit = ((data[bit_index / 8] >> (7 - bit_index % 8))) & 1;

            host_data[i * dword_length + j / 32] |= bit << (31 - j % 32);
            bit_index++;
        }
    }

    cudaMalloc(&this->data, n * dword_length * 4);
    cudaMemcpy(this->data, host_data, n * dword_length * 4,
               cudaMemcpyHostToDevice);
}

__global__ void print_pairs_kernel(uint32_t *data, int n, int dword_length) {
    int i = blockIdx.x * 1024 + threadIdx.x;
    if (i >= n)
        return;
    for (int j = 0; j < i; j++) {
        bool distance_one = false;
        bool differs = false;
        for (int k = 0; k < dword_length; k++) {
            uint32_t prod =
                data[i * dword_length + k] ^ data[j * dword_length + k];
            if (prod == 0)
                continue;
            if ((prod & (prod - 1)) == 0) {
                if (differs) {
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

        if (distance_one) {
            printf("%d %d\n", j, i);
        }
    }
}

void HOGPU::print_pairs() {
    print_pairs_kernel<<<(n - 1) / 1024 + 1, 1024>>>(data, n, dword_length);
    cudaDeviceSynchronize();
};

HOGPU::~HOGPU() { cudaFree(data); }