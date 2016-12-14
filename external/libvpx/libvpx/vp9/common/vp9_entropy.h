/*
 *  Copyright (c) 2010 The WebM project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef VP9_COMMON_VP9_ENTROPY_H_
#define VP9_COMMON_VP9_ENTROPY_H_

#include "vpx/vpx_integer.h"
#include "vpx_dsp/prob.h"

#include "vp9/common/vp9_common.h"
#include "vp9/common/vp9_enums.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DIFF_UPDATE_PROB 252

#define ZERO_TOKEN      0   
#define ONE_TOKEN       1   
#define TWO_TOKEN       2   
#define THREE_TOKEN     3   
#define FOUR_TOKEN      4   
#define CATEGORY1_TOKEN 5   
#define CATEGORY2_TOKEN 6   
#define CATEGORY3_TOKEN 7   
#define CATEGORY4_TOKEN 8   
#define CATEGORY5_TOKEN 9   
#define CATEGORY6_TOKEN 10  
#define EOB_TOKEN       11  

#define ENTROPY_TOKENS 12

#define ENTROPY_NODES 11

DECLARE_ALIGNED(16, extern const uint8_t, vp9_pt_energy_class[ENTROPY_TOKENS]);

#define CAT1_MIN_VAL    5
#define CAT2_MIN_VAL    7
#define CAT3_MIN_VAL   11
#define CAT4_MIN_VAL   19
#define CAT5_MIN_VAL   35
#define CAT6_MIN_VAL   67

DECLARE_ALIGNED(16, extern const uint8_t, vp9_cat1_prob[1]);
DECLARE_ALIGNED(16, extern const uint8_t, vp9_cat2_prob[2]);
DECLARE_ALIGNED(16, extern const uint8_t, vp9_cat3_prob[3]);
DECLARE_ALIGNED(16, extern const uint8_t, vp9_cat4_prob[4]);
DECLARE_ALIGNED(16, extern const uint8_t, vp9_cat5_prob[5]);
DECLARE_ALIGNED(16, extern const uint8_t, vp9_cat6_prob[14]);

#if CONFIG_VP9_HIGHBITDEPTH
DECLARE_ALIGNED(16, extern const uint8_t, vp9_cat1_prob_high10[1]);
DECLARE_ALIGNED(16, extern const uint8_t, vp9_cat2_prob_high10[2]);
DECLARE_ALIGNED(16, extern const uint8_t, vp9_cat3_prob_high10[3]);
DECLARE_ALIGNED(16, extern const uint8_t, vp9_cat4_prob_high10[4]);
DECLARE_ALIGNED(16, extern const uint8_t, vp9_cat5_prob_high10[5]);
DECLARE_ALIGNED(16, extern const uint8_t, vp9_cat6_prob_high10[16]);
DECLARE_ALIGNED(16, extern const uint8_t, vp9_cat1_prob_high12[1]);
DECLARE_ALIGNED(16, extern const uint8_t, vp9_cat2_prob_high12[2]);
DECLARE_ALIGNED(16, extern const uint8_t, vp9_cat3_prob_high12[3]);
DECLARE_ALIGNED(16, extern const uint8_t, vp9_cat4_prob_high12[4]);
DECLARE_ALIGNED(16, extern const uint8_t, vp9_cat5_prob_high12[5]);
DECLARE_ALIGNED(16, extern const uint8_t, vp9_cat6_prob_high12[18]);
#endif  

#define EOB_MODEL_TOKEN 3

typedef struct {
  const vpx_tree_index *tree;
  const vpx_prob *prob;
  int len;
  int base_val;
  const int16_t *cost;
} vp9_extra_bit;

extern const vp9_extra_bit vp9_extra_bits[ENTROPY_TOKENS];
#if CONFIG_VP9_HIGHBITDEPTH
extern const vp9_extra_bit vp9_extra_bits_high10[ENTROPY_TOKENS];
extern const vp9_extra_bit vp9_extra_bits_high12[ENTROPY_TOKENS];
#endif  

#define DCT_MAX_VALUE           16384
#if CONFIG_VP9_HIGHBITDEPTH
#define DCT_MAX_VALUE_HIGH10    65536
#define DCT_MAX_VALUE_HIGH12   262144
#endif  


#define REF_TYPES 2  

#define COEF_BANDS 6


#define COEFF_CONTEXTS 6
#define BAND_COEFF_CONTEXTS(band) ((band) == 0 ? 3 : COEFF_CONTEXTS)


typedef unsigned int vp9_coeff_count[REF_TYPES][COEF_BANDS][COEFF_CONTEXTS]
                                    [ENTROPY_TOKENS];
typedef unsigned int vp9_coeff_stats[REF_TYPES][COEF_BANDS][COEFF_CONTEXTS]
                                    [ENTROPY_NODES][2];

#define SUBEXP_PARAM                4   
#define MODULUS_PARAM               13  

struct VP9Common;
void vp9_default_coef_probs(struct VP9Common *cm);
void vp9_adapt_coef_probs(struct VP9Common *cm);

#define MAXBAND_INDEX 21

DECLARE_ALIGNED(16, extern const uint8_t, vp9_coefband_trans_8x8plus[1024]);
DECLARE_ALIGNED(16, extern const uint8_t, vp9_coefband_trans_4x4[16]);

static INLINE const uint8_t *get_band_translate(TX_SIZE tx_size) {
  return tx_size == TX_4X4 ? vp9_coefband_trans_4x4
                           : vp9_coefband_trans_8x8plus;
}


#define COEFF_PROB_MODELS 256

#define UNCONSTRAINED_NODES         3

#define PIVOT_NODE                  2   

#define MODEL_NODES (ENTROPY_NODES - UNCONSTRAINED_NODES)
extern const vpx_tree_index vp9_coef_con_tree[TREE_SIZE(ENTROPY_TOKENS)];
extern const vpx_prob vp9_pareto8_full[COEFF_PROB_MODELS][MODEL_NODES];

typedef vpx_prob vp9_coeff_probs_model[REF_TYPES][COEF_BANDS]
                                      [COEFF_CONTEXTS][UNCONSTRAINED_NODES];

typedef unsigned int vp9_coeff_count_model[REF_TYPES][COEF_BANDS]
                                          [COEFF_CONTEXTS]
                                          [UNCONSTRAINED_NODES + 1];

void vp9_model_to_full_probs(const vpx_prob *model, vpx_prob *full);

typedef char ENTROPY_CONTEXT;

static INLINE int combine_entropy_contexts(ENTROPY_CONTEXT a,
                                           ENTROPY_CONTEXT b) {
  return (a != 0) + (b != 0);
}

static INLINE int get_entropy_context(TX_SIZE tx_size, const ENTROPY_CONTEXT *a,
                                      const ENTROPY_CONTEXT *l) {
  ENTROPY_CONTEXT above_ec = 0, left_ec = 0;

  switch (tx_size) {
    case TX_4X4:
      above_ec = a[0] != 0;
      left_ec = l[0] != 0;
      break;
    case TX_8X8:
      above_ec = !!*(const uint16_t *)a;
      left_ec  = !!*(const uint16_t *)l;
      break;
    case TX_16X16:
      above_ec = !!*(const uint32_t *)a;
      left_ec  = !!*(const uint32_t *)l;
      break;
    case TX_32X32:
      above_ec = !!*(const uint64_t *)a;
      left_ec  = !!*(const uint64_t *)l;
      break;
    default:
      assert(0 && "Invalid transform size.");
      break;
  }

  return combine_entropy_contexts(above_ec, left_ec);
}

#ifdef __cplusplus
}  
#endif

#endif  
