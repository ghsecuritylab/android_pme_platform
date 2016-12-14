/*
 *  Copyright (c) 2011 The WebM project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef VP9_COMMON_VP9_FILTER_H_
#define VP9_COMMON_VP9_FILTER_H_

#include "./vpx_config.h"
#include "vpx/vpx_integer.h"
#include "vpx_dsp/vpx_filter.h"
#include "vpx_ports/mem.h"


#ifdef __cplusplus
extern "C" {
#endif

#define EIGHTTAP            0
#define EIGHTTAP_SMOOTH     1
#define EIGHTTAP_SHARP      2
#define SWITCHABLE_FILTERS  3 
#define BILINEAR            3
#define SWITCHABLE_FILTER_CONTEXTS (SWITCHABLE_FILTERS + 1)
#define SWITCHABLE 4 

typedef uint8_t INTERP_FILTER;

extern const InterpKernel *vp9_filter_kernels[4];

#ifdef __cplusplus
}  
#endif

#endif  
