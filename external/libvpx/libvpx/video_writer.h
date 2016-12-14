/*
 *  Copyright (c) 2014 The WebM project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef VIDEO_WRITER_H_
#define VIDEO_WRITER_H_

#include "./video_common.h"

typedef enum {
  kContainerIVF
} VpxContainer;

struct VpxVideoWriterStruct;
typedef struct VpxVideoWriterStruct VpxVideoWriter;

#ifdef __cplusplus
extern "C" {
#endif

VpxVideoWriter *vpx_video_writer_open(const char *filename,
                                      VpxContainer container,
                                      const VpxVideoInfo *info);

void vpx_video_writer_close(VpxVideoWriter *writer);

int vpx_video_writer_write_frame(VpxVideoWriter *writer,
                                 const uint8_t *buffer, size_t size,
                                 int64_t pts);

#ifdef __cplusplus
}  
#endif

#endif  