#include <cstdint>
#include <cstring>

#include <immintrin.h>

#include <gtest/gtest.h>

#include "amx/amx.h"
#include "amx/utils.h"

TEST(MatMul, CorrectnessCheck) {
    EXPECT_EQ(true, request_AMX());

    scoped_config_t config;

    constexpr int rows = MAX_ROWS;
    constexpr int cols = MAX_COLS_B;
    constexpr int size = rows * cols;

    int8_t src0[size] = {0};
    int8_t src1[size] = {0};
    int8_t src1_blocked[size] = {0};
    int32_t dst[size / sizeof(int32_t)] = {0};
    int32_t ref_dst[size / sizeof(int32_t)] = {0};

    fill_mat_random(src0, size);
    fill_mat_random(src1, size);
    // 64x16 -> 16x64
    blocked4_rotate(src1, src1_blocked, cols, rows, cols);

    // 16x64 x 64x16 = 16x16
    matmul_ref_impl(src0, src1, ref_dst, rows, cols, rows);
    // 16x64 x 16x64 (blocked) = 16x16
    matmul_amx_impl(src0, src1_blocked, dst);

    #ifndef NDEBUG
    print_mat(src0, rows, cols);
    print_mat(src1_blocked, rows, cols);
    print_mat(dst, rows, rows);
    #endif

    constexpr int match = 0;
    EXPECT_EQ(match, std::memcmp(ref_dst, dst, rows * cols));
}
