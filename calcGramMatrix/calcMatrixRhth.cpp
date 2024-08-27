//////////////////////////////////////////////////////////////////////
// This function is used to calculate the matrix Rxtx.
// Rxtx = X' * X, where X is the matrix Xin.
// Rxtx is the correlation matrix of the received signal.
// Author: Jie Lei
// Date: 06/04/2024
//////////////////////////////////////////////////////////////////////
#include "calcMatrixRhth.hpp"

// Calculate the matrix Rxtx
void calcMatrixRhth(stream<comp18_t> matrixH[NUM_ANT], uint8_t reguVal,
                    stream<comp18_t> matrixH2next[NUM_ANT], stream<MATRIX_IN_T>& matrixRhth) {
    comp18_t matrixHBuf[NUM_ANT][NUM_LTS];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=matrixHBuf
    comp18_t tmpDataIn;
    comp18_t tmpColumnData[NUM_ANT];
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=tmpColumnData
    comp22_t accData;
    comp22_t tmpData;
    MATRIX_IN_T tmpDataOut;
    //fixed20_t regulatorValue = 0.00097656; // 8/8192, Regulator = 8 in MATLAB code
    fixed22_t regulatorValue;

    //fixed20_t regulatorValue = 0.00390625; // 8/2048, Regulator = 8 in MATLAB code
    regulatorValue = (fixed22_t)reguVal / 2048;

    // Read the matrix X from the stream interface
    for (int i = 0; i < NUM_USED_SUBC; i++) {
        // Read the matrix X from the stream interface
        for (int j = 0; j < NUM_LTS; j++) {
#pragma HLS PIPELINE II=1 rewind=true
            for (int k = 0; k < NUM_ANT; k++) {
                tmpDataIn = matrixH[k].read();
                matrixHBuf[k][j] = tmpDataIn;
                matrixH2next[k].write(tmpDataIn);
            }
        }
        // Calculate the matrix Rxtx
        for (int j = 0; j < NUM_ANT; j++) {
            // Read the column data and get its conjugate
            for (int k = 0; k < NUM_ANT; k++) {
#pragma HLS UNROLL skip_exit_check=true
                tmpColumnData[k] = std::conj(matrixHBuf[k][j]);
            }
            // Multiply the column data with the matrix Xin
            for (int k = 0; k < NUM_LTS; k++) {
#pragma HLS PIPELINE II=GM_II
            	accData = (comp22_t){0, 0};
                for (int l = 0; l < NUM_ANT; l++) {
                	accData += (comp22_t)tmpColumnData[l] * (comp22_t)matrixHBuf[l][k];
                }
                //tmpDataOut = (MATRIX_IN_T){tmpData.real(), tmpData.imag()};
                if (j == k) {  
                	tmpData = (comp22_t){accData.real() + regulatorValue, accData.imag()};
                } else {
                	tmpData = (comp22_t){accData.real(), accData.imag()};
                }
                tmpDataOut = {(float)tmpData.real() * 2048, (float)tmpData.imag() * 2048};
                matrixRhth.write(tmpDataOut); // Write the result to the stream interface row by row
            }
        }
    }
}
