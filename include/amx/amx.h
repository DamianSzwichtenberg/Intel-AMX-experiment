#pragma once

#include <cstdint>

#define MAX_ROWS 16
#define MAX_COLS_B 64
#define STRIDE_B 64
#define BLOCK_SIZE 4

struct tile_layout_t {
    uint8_t palette_id = 1;
    uint8_t start_row = 0;
    uint8_t reserved[14] = {0};
    uint16_t colsb[8] = {MAX_COLS_B, MAX_COLS_B, MAX_COLS_B};
    uint8_t reserved2[16] = {0};
    uint8_t rows[8] = {MAX_ROWS, MAX_ROWS, MAX_ROWS};
    uint8_t reserved3[8] = {0};
};

struct scoped_config_t {
    scoped_config_t();
    ~scoped_config_t();

    tile_layout_t layout;
};

bool request_AMX();

void blocked4_rotate(const int8_t* src, int8_t* dst, int m, int k, int n);

void matmul_amx_impl(const int8_t* src0, const int8_t* src1, int32_t* dst);
