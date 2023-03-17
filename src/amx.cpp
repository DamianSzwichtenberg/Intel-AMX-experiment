//==============================================================
// Copyright © 2023 Intel Corporation
//
// SPDX-License-Identifier: MIT
// =============================================================

#include <immintrin.h>

#include <cstdint>

#include "amx/amx.h"
#include "amx/utils.h"

#ifdef __linux__
#include <sys/syscall.h>
#include <unistd.h>

#define XFEATURE_XTILECFG 17
#define XFEATURE_XTILEDATA 18
#define XFEATURE_MASK_XTILECFG (1 << XFEATURE_XTILECFG)
#define XFEATURE_MASK_XTILEDATA (1 << XFEATURE_XTILEDATA)
#define XFEATURE_MASK_XTILE (XFEATURE_MASK_XTILECFG | XFEATURE_MASK_XTILEDATA)
#define ARCH_GET_XCOMP_PERM 0x1022
#define ARCH_REQ_XCOMP_PERM 0x1023
#endif

scoped_config_t::scoped_config_t() { _tile_loadconfig(&layout); }

scoped_config_t::~scoped_config_t() { _tile_release(); }

bool request_AMX() {
#ifdef __linux__
  unsigned long bitmask = 0;
  auto status = syscall(SYS_arch_prctl, ARCH_GET_XCOMP_PERM, &bitmask);
  if (0 != status) return false;
  if (bitmask & XFEATURE_MASK_XTILEDATA) return true;

  status = syscall(SYS_arch_prctl, ARCH_REQ_XCOMP_PERM, XFEATURE_XTILEDATA);
  if (0 != status) return false;

  status = syscall(SYS_arch_prctl, ARCH_GET_XCOMP_PERM, &bitmask);
  if (0 != status || !(bitmask & XFEATURE_MASK_XTILEDATA)) return false;

  return true;
#else
  return false;
#endif
}

void blocked4_rotate(const int8_t* src, int8_t* dst, int m, int k, int n) {
  for (int src_row = 0; src_row < m; src_row += BLOCK_SIZE) {
    for (int src_col = 0; src_col < k; ++src_col) {
      int dst_row = src_row / BLOCK_SIZE;
      int dst_col = src_col * 4;
      int src_idx = src_row * k + src_col;
      int dst_idx = dst_row * n + dst_col;
      dst[dst_idx] = src[src_idx];
      dst[dst_idx + 1] = src[src_idx + k];
      dst[dst_idx + 2] = src[src_idx + 2 * k];
      dst[dst_idx + 3] = src[src_idx + 3 * k];
    }
  }
}

void matmul_amx_impl(const int8_t* src0, const int8_t* src1, int32_t* dst) {
  // assumptions:
  // - AMX enabled (use request_AMX)
  // - tile config loaded (use scoped_config_t)
  // - src1 in blocked format (use blocked4_rotate)
  _tile_zero(0);

  _tile_loadd(1, src0, STRIDE_B);
  _tile_loadd(2, src1, STRIDE_B);

  _tile_dpbssd(0, 1, 2);

  _tile_stored(0, dst, STRIDE_B);
}
