#include "krnl_matmul.h"

void load_input(const uint32_t * in, uint32_t mat[DATA_SIZE][DATA_SIZE]) {
    
    for (int i=0; i<DATA_SIZE; i++) {
        #pragma HLS LOOP_TRIPCOUNT min = DATA_SIZE max = DATA_SIZE

        for (int j=0; j<DATA_SIZE; j++) {
            #pragma HLS LOOP_TRIPCOUNT min = DATA_SIZE max = DATA_SIZE

            mat[i][j] = in[i*DATA_SIZE + j];

        }

    }

}

void store_output(uint32_t * out, const uint32_t mat[DATA_SIZE][DATA_SIZE]) {

    for (int i=0; i<DATA_SIZE; i++) {
        #pragma HLS LOOP_TRIPCOUNT min = DATA_SIZE max = DATA_SIZE

        for (int j=0; j<DATA_SIZE; j++) {
            #pragma HLS LOOP_TRIPCOUNT min = DATA_SIZE max = DATA_SIZE

             out[i*DATA_SIZE + j] = mat[i][j];

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

void krnl_matmul(const uint32_t *in_A, const uint32_t *in_B, uint32_t *out) {
    
    #pragma HLS INTERFACE m_axi port = in_A depth = DATA_SIZE*DATA_SIZE bundle = gmem0
    #pragma HLS INTERFACE m_axi port = in_B depth = DATA_SIZE*DATA_SIZE bundle = gmem1
    #pragma HLS INTERFACE m_axi port = out depth = DATA_SIZE*DATA_SIZE bundle = gmem2

    uint32_t A[DATA_SIZE][DATA_SIZE];
    uint32_t B[DATA_SIZE][DATA_SIZE];
    uint32_t C[DATA_SIZE][DATA_SIZE];

    #pragma HLS DATAFLOW
    load_input(in_A, A);
    load_input(in_B, B);
    execute(A, B, C);
    store_output(out, C);

}