/*
 *  Copyright (c) 2010 The WebM project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef VPX_DSP_INV_TXFM_H_
#define VPX_DSP_INV_TXFM_H_

#include <assert.h>

#include "./vpx_config.h"
#include "vpx_dsp/txfm_common.h"
#include "vpx_ports/mem.h"

#ifdef __cplusplus
extern "C" {
#endif

static INLINE tran_low_t check_range(tran_high_t input) {
#if CONFIG_COEFFICIENT_RANGE_CHECKING
  
  
  
  
  
  
  assert(INT16_MIN <= input);
  assert(input <= INT16_MAX);
#endif  
  return (tran_low_t)input;
}

static INLINE tran_low_t dct_const_round_shift(tran_high_t input) {
  tran_high_t rv = ROUND_POWER_OF_TWO(input, DCT_CONST_BITS);
  return check_range(rv);
}

#if CONFIG_VP9_HIGHBITDEPTH
static INLINE tran_low_t highbd_check_range(tran_high_t input,
                                            int bd) {
#if CONFIG_COEFFICIENT_RANGE_CHECKING
  
  
  
  
  
  const int32_t int_max = (1 << (7 + bd)) - 1;
  const int32_t int_min = -int_max - 1;
  assert(int_min <= input);
  assert(input <= int_max);
  (void) int_min;
#endif  
  (void) bd;
  return (tran_low_t)input;
}

static INLINE tran_low_t highbd_dct_const_round_shift(tran_high_t input,
                                                      int bd) {
  tran_high_t rv = ROUND_POWER_OF_TWO(input, DCT_CONST_BITS);
  return highbd_check_range(rv, bd);
}
#endif  

#if CONFIG_EMULATE_HARDWARE
#define WRAPLOW(x, bd) ((((int32_t)(x)) << (24 - bd)) >> (24 - bd))
#else
#define WRAPLOW(x, bd) ((int32_t)(x))
#endif  

void idct4_c(const tran_low_t *input, tran_low_t *output);
void idct8_c(const tran_low_t *input, tran_low_t *output);
void idct16_c(const tran_low_t *input, tran_low_t *output);
void idct32_c(const tran_low_t *input, tran_low_t *output);
void iadst4_c(const tran_low_t *input, tran_low_t *output);
void iadst8_c(const tran_low_t *input, tran_low_t *output);
void iadst16_c(const tran_low_t *input, tran_low_t *output);

#if CONFIG_VP9_HIGHBITDEPTH
void vpx_highbd_idct4_c(const tran_low_t *input, tran_low_t *output, int bd);
void vpx_highbd_idct8_c(const tran_low_t *input, tran_low_t *output, int bd);
void vpx_highbd_idct16_c(const tran_low_t *input, tran_low_t *output, int bd);

void vpx_highbd_iadst4_c(const tran_low_t *input, tran_low_t *output, int bd);
void vpx_highbd_iadst8_c(const tran_low_t *input, tran_low_t *output, int bd);
void vpx_highbd_iadst16_c(const tran_low_t *input, tran_low_t *output, int bd);

static INLINE uint16_t highbd_clip_pixel_add(uint16_t dest, tran_high_t trans,
                                             int bd) {
  trans = WRAPLOW(trans, bd);
  return clip_pixel_highbd(WRAPLOW(dest + trans, bd), bd);
}
#endif

static INLINE uint8_t clip_pixel_add(uint8_t dest, tran_high_t trans) {
  trans = WRAPLOW(trans, 8);
  return clip_pixel(WRAPLOW(dest + trans, 8));
}
#ifdef __cplusplus
}  
#endif

#endif  
