#include "krnl_matmul.h"

void load_input(const uint512_t * in, uint32_t mat[SIZE][SIZE], const uint32_t offset) {
    
    int i=0, j=0;
    uint512_t buff;
    
    for (int k=0; k<NUM_ITER; k++) {
        #pragma HLS LOOP_TRIPCOUNT min = NUM_ITER max = NUM_ITER

        buff = in[offset + k];
        
        if (j == SIZE) {

            j = 0;
            i++;

        }

        for (int l=0; l<INTERFACE_SIZE; l++) {
            #pragma HLS LOOP_TRIPCOUNT min = INTERFACE_SIZE max = INTERFACE_SIZE

            #pragma HLS UNROLL factor=INTERFACE_SIZE
            
            mat[i][j] = ((uint32_t *)(&buff))[l];

            j++;
            
        }

    }

}

void store_output(uint512_t * out, const uint32_t mat[SIZE][SIZE], const uint32_t offset) {

    int i=0, j=0;
    uint512_t buff;
    
    for (int k=0; k<NUM_ITER; k++) {
        #pragma HLS LOOP_TRIPCOUNT min = NUM_ITER max = NUM_ITER

        if (j == SIZE) {

            j = 0;
            i++;

        }

        for (int l=0; l<INTERFACE_SIZE; l++) {
            #pragma HLS LOOP_TRIPCOUNT min = INTERFACE_SIZE max = INTERFACE_SIZE

            #pragma HLS UNROLL factor=INTERFACE_SIZE
            
            ((uint32_t *)(&buff))[l] = mat[i][j];

            j++;

        }

        out[offset + k] = buff;

    }

}

static void execute(const uint32_t A[SIZE][SIZE],
                    const uint32_t B[SIZE][SIZE],
                    uint32_t C[SIZE][SIZE]) {

    for (int i=0; i<SIZE; i++) {
        #pragma HLS LOOP_TRIPCOUNT min = SIZE max = SIZE

        
        for (int j=0; j<SIZE; j++) {
            #pragma HLS LOOP_TRIPCOUNT min = SIZE max = SIZE

            uint32_t outsum = 0;
            for (int k=0; k<SIZE; k++) {
                #pragma HLS LOOP_TRIPCOUNT min = SIZE max = SIZE
                
                outsum += A[i][k] * B[k][j];

            }

            C[i][j] = outsum;

        }

    }
    
    

}

void krnl_matmul(uint512_t *axi_mm) {
    
    #pragma HLS INTERFACE m_axi port = axi_mm depth = SIZE_MM bundle = gmem0

    uint32_t A[SIZE][SIZE];
    uint32_t B[SIZE][SIZE];
    uint32_t C[SIZE][SIZE];

    // #pragma HLS DATAFLOW
    load_input(axi_mm, A, OFFSET_A);
    load_input(axi_mm, B, OFFSET_B);
    execute(A, B, C);
    store_output(axi_mm, C, OFFSET_C);

}