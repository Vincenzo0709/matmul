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

    for (int ti=0; ti<N_TILES; ti++) {
        #pragma HLS LOOP_TRIPCOUNT min = N_TILES max = N_TILES

        for (int tj=0; tj<N_TILES; tj++) {
            #pragma HLS LOOP_TRIPCOUNT min = N_TILES max = N_TILES

            uint32_t outsum = 0;
            for (int ni=0; ni<TILE_SIZE; ni++) {
                #pragma HLS LOOP_TRIPCOUNT min = TILE_SIZE max = TILE_SIZE

                for (int nj=0; nj<TILE_SIZE; nj++) {
                    #pragma HLS LOOP_TRIPCOUNT min = TILE_SIZE max = TILE_SIZE

                    for (int k=0; k<SIZE; k++) {
                        #pragma HLS LOOP_TRIPCOUNT min = SIZE max = SIZE
                            
                        outsum += A[i][k] * B[k][j];

                    }

                }

            }

            C[i][j] = outsum;

        }

    }
    
    

}

void krnl_matmul(uint512_t *axi_mm) {
    
    #pragma HLS INTERFACE m_axi port = axi_mm depth = SIZE_MM bundle = gmem0

    uint32_t A[SIZE][SIZE];
    #pragma HLS ARRAY_PARTITION A
    uint32_t B[SIZE][SIZE];
    uint32_t C[SIZE][SIZE];

    // #pragma HLS DATAFLOW
    load_input(axi_mm, A, OFFSET_A);
    load_input(axi_mm, B, OFFSET_B);
    execute(A, B, C);
    store_output(axi_mm, C, OFFSET_C);

}