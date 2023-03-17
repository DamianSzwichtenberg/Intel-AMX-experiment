#include "amx/utils.h"

#include <cstdint>
#include <iostream>
#include <random>
#include <string>

void matmul_ref_impl(const int8_t* src0, const int8_t* src1, int32_t* dst,
                     int m, int k, int n) {
  for (int i0 = 0; i0 < m; ++i0) {
    for (int i1 = 0; i1 < n; ++i1) {
      for (int i2 = 0; i2 < k; ++i2) {
        // assumption: dst is filled with zeros
        dst[i0 * n + i1] += src0[i0 * k + i2] * src1[i1 + i2 * n];
      }
    }
  }
}

template <typename value_t>
void print_mat(const value_t* mat, int rows, int cols) {
  std::string msg =
      "Mat[" + std::to_string(rows) + ", " + std::to_string(cols) + "]\n";
  std::cout << msg;
  for (int i0 = 0; i0 < rows; ++i0) {
    for (int i1 = 0; i1 < cols; ++i1) {
      // we need to cast, in case value_t = int8_t, which is interpreted
      // as a char
      std::cout << static_cast<int32_t>(mat[i0 * cols + i1]) << " ";
    }
    std::cout << "\n";
  }
}

template void print_mat(const int8_t* mat, int rows, int cols);
template void print_mat(const int32_t* mat, int rows, int cols);

template <typename value_t>
void fill_mat_random(value_t* mat, int size) {
  std::mt19937 gen;
  std::uniform_int_distribution<value_t> distrib(1, 9);
  for (int i = 0; i < size; ++i) {
    mat[i] = distrib(gen);
  }
}

template void fill_mat_random(int8_t* mat, int size);
template void fill_mat_random(int32_t* mat, int size);
