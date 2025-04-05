#ifndef __KRNL_MATMUL_H__
#define __KRNL_MATMUL_H__

#include <stdint.h>
#include <hls_stream.h>
#include <ap_int.h>

// Matrixes dimensions are fixed
#define SIZE 32
#define INT_BITS 32

// Interface is 512 bits -> 16 uint32_t elements
#define INTERFACE_BITS 512
#define INTERFACE_SIZE (INTERFACE_BITS / INT_BITS)

// A single input/output buffer is 1024 bits -> 32*32 uint32_t elements
#define BUFFER_SIZE (SIZE * SIZE)
#define BUFFER_BITS (BUFFER_SIZE * INT_BITS)

// Iterations needed to access all elements for a single buffer
#define NUM_ITER (BUFFER_SIZE / INTERFACE_SIZE)

// All 3 buffers need 3*32*32 uint32_t elements -> 3*64=192 uint512_t elements
#define SIZE_MM (3 * NUM_ITER)

// Offsets to access the three buffers in cachelines
#define OFFSET_A 0
#define OFFSET_B (NUM_ITER)
#define OFFSET_C (2 * NUM_ITER)

// Offsets to access the three buffers in integers
#define OFF_A 0
#define OFF_B (BUFFER_SIZE)
#define OFF_C (2*BUFFER_SIZE)

// Expected result for a single output matrix element
#define EXPCTD SIZE

typedef ap_uint<INTERFACE_BITS> uint512_t;

void krnl_matmul(uint512_t *);

#endif