#include "krnl_matmul.h"

void load_input(const uint32_t * in, uint32_t mat[DATA_SIZE][DATA_SIZE], const uint32_t offset) {
    
    for (int i=0; i<DATA_SIZE; i++) {
        #pragma HLS LOOP_TRIPCOUNT min = DATA_SIZE max = DATA_SIZE

        for (int j=0; j<DATA_SIZE; j++) {
            #pragma HLS LOOP_TRIPCOUNT min = DATA_SIZE max = DATA_SIZE

            mat[i][j] = in[offset + (i*DATA_SIZE + j)];

        }

    }

}

void store_output(uint32_t * out, const uint32_t mat[DATA_SIZE][DATA_SIZE], const uint32_t offset) {

    for (int i=0; i<DATA_SIZE; i++) {
        #pragma HLS LOOP_TRIPCOUNT min = DATA_SIZE max = DATA_SIZE

        for (int j=0; j<DATA_SIZE; j++) {
            #pragma HLS LOOP_TRIPCOUNT min = DATA_SIZE max = DATA_SIZE

             out[offset + (i*DATA_SIZE + j)] = mat[i][j];

        }

    }

}

static void execute(const uint32_t A[DATA_SIZE][DATA_SIZE],
                    const uint32_t B[DATA_SIZE][DATA_SIZE],
                    uint32_t C[DATA_SIZE][DATA_SIZE]) {

    for (int i=0; i<DATA_SIZE; i++) {
        #pragma HLS LOOP_TRIPCOUNT min = DATA_SIZE max = DATA_SIZE

        
        for (int j=0; j<DATA_SIZE; j++) {
            #pragma HLS LOOP_TRIPCOUNT min = DATA_SIZE max = DATA_SIZE

            uint32_t outsum = 0;
            for (int k=0; k<DATA_SIZE; k++) {
                #pragma HLS LOOP_TRIPCOUNT min = DATA_SIZE max = DATA_SIZE
                
                outsum += A[i][k] * B[k][j];

            }

            C[i][j] = outsum;

        }

    }
    
    

}

void krnl_matmul(uint32_t *axi_mm) {
    
    #pragma HLS INTERFACE m_axi port = axi_mm depth = SIZE_MM bundle = gmem0

    uint32_t A[DATA_SIZE][DATA_SIZE];
    uint32_t B[DATA_SIZE][DATA_SIZE];
    uint32_t C[DATA_SIZE][DATA_SIZE];

    // #pragma HLS DATAFLOW
    load_input(axi_mm, A, OFFSET_A);
    load_input(axi_mm, B, OFFSET_B);
    execute(A, B, C);
    store_output(axi_mm, C, OFFSET_C);

}