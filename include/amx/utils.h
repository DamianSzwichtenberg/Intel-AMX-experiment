//==============================================================
// Copyright © 2023 Intel Corporation
//
// SPDX-License-Identifier: MIT
// =============================================================

#pragma once

#include <cstdint>

void matmul_ref_impl(const int8_t* src0, const int8_t* src1, int32_t* dst,
                     int m, int k, int n);

template <typename value_t>
void print_mat(const value_t* mat, int rows, int cols);

template <typename value_t>
void fill_mat_random(value_t* mat, int size);
