#include "rx_frame.hpp"
#include "dut_type.hpp"


void calcMatrixRhth(stream<comp18_t> matrixH[NUM_ANT], uint8_t reguVal, 
                    stream<comp18_t> matrixH2next[NUM_ANT], stream<MATRIX_IN_T>& matrixRhth);
