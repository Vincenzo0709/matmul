#include <iostream>
#include "krnl_matmul.h"
using namespace std;

bool check_values(uint32_t *out, const int expctd) {
    
    for (int i=0; i<DATA_SIZE; i++) {
        
        for (int j=0; j<DATA_SIZE; j++) {

            if (expctd != out[i*DATA_SIZE + j]) {
                cout << endl << "[ERROR] Not expected result!" << endl;
                return false;
            }

        }

    }
    
    return true;

}

int main(int argc, const char **argv) {

    uint32_t A[DATA_SIZE*DATA_SIZE];
    uint32_t B[DATA_SIZE*DATA_SIZE];
    uint32_t out[DATA_SIZE*DATA_SIZE];
    const int expctd = DATA_SIZE;

    for (int i=0; i<DATA_SIZE; i++) {
        
        for (int j=0; j<DATA_SIZE; j++) {

            A[i*DATA_SIZE + j] = 1;
            B[i*DATA_SIZE + j] = 1;
            out[i*DATA_SIZE + j] = 0;

        }

    }

    krnl_matmul(A, B, out);

    return !check_values(out, expctd);

}