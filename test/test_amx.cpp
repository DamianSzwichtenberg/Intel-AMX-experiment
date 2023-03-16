#include <cstdint>

#include <gtest/gtest.h>

#include "amx/utils.h"

TEST(MatMul, CorrectnessCheck) {
    constexpr int side = 4;
    constexpr int size = side * side;

    int8_t src0[size] = {0};
    int8_t src1[size] = {0};
    int32_t dst[size] = {0};

    fill_mat_random(src0, size);
    fill_mat_random(src1, size);

    matmul_ref_impl(src0, src1, dst, side, side, side);

    print_mat(src0, side, side);
    print_mat(src1, side, side);
    print_mat(dst, side, side);
}
