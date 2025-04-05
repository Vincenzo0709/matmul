#include <iostream>
#include "krnl_matmul.h"
using namespace std;

bool check_values(uint32_t *axi_mm) {
    
    for (int i=0; i<DATA_SIZE; i++) {
        
        for (int j=0; j<DATA_SIZE; j++) {

            if (EXPCTD != axi_mm[OFF_C + (i*DATA_SIZE + j)]) {
                cout << endl << "[ERROR] Not expected result!" << endl;
                return false;
            }

        }

    }
    
    return true;

}

int main(int argc, const char **argv) {

    uint32_t axi_mm[SIZE_MM];

    for (int i=0; i<DATA_SIZE; i++) {
        
        for (int j=0; j<DATA_SIZE; j++) {

            axi_mm[OFF_A + (i*DATA_SIZE + j)] = 1;
            axi_mm[OFF_B + (i*DATA_SIZE + j)] = 1;
            axi_mm[OFF_C + (i*DATA_SIZE + j)] = 0;

        }

    }

    krnl_matmul(axi_mm);

    return !check_values(axi_mm);

}