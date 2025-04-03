#ifndef __KRNL_MATMUL_H__
#define __KRNL_MATMUL_H__

#include <stdint.h>
#include <hls_stream.h>

#define DATA_SIZE 32
#define EXPCTD DATA_SIZE

#define OFFSET_A 0
#define OFFSET_B DATA_SIZE*DATA_SIZE
#define OFFSET_C 2*DATA_SIZE*DATA_SIZE

#define SIZE_MM 3*DATA_SIZE*DATA_SIZE

void krnl_matmul(uint32_t *);

#endif