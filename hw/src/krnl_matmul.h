#ifndef __KRNL_MATMUL_H__
#define __KRNL_MATMUL_H__

#include <stdint.h>
#include <hls_stream.h>

#define DATA_SIZE 32

void krnl_matmul(const uint32_t *, const uint32_t *, uint32_t *);

#endif