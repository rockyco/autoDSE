///////////////////////////////////////////////////////////////////////////////////////
// This is the testbench for the calcMatrixRxtx function.
// The testbench reads the input matrix Xin from a file and writes the output matrix Rxtx to a file.
// The input matrix Xin is stored in a file named "matrixXin.txt".
// The output matrix Rxtx is stored in a file named "matrixRxtx_hw.txt".
// The input matrix Xin is a 2D array of complex numbers.
// The output matrix Rxtx is a 2D array of complex numbers.
// The input matrix Xin is read from the file "matrixXin.txt" and written to the stream interface.
// The output matrix Rxtx is read from the stream interface and written to the file "matrixRxtx_hw.txt".
// The testbench compares the output matrix Rxtx with the expected output matrix Rxtx.
// The expected output matrix Rxtx is read from a file named "matrixRxtx_expected.txt".
// The testbench prints "Test passed" if the output matrix Rxtx matches the expected output matrix Rxtx.
// The testbench prints "Test failed" if the output matrix Rxtx does not match the expected output matrix Rxtx.
// The testbench uses the following parameters:
// NUM_ANT: Number of antennas
// NUM_LTS: Number of long training symbols
// NUM_USED_SUBC: Total number of subcarriers
// Author: Jie Lei
// Date: 07/04/2024
///////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#include "calcMatrixRhth.hpp"

// This is the testbench for testing the calcMatrixRxtx function
int main(void) {
    // Define the input and output data
    stream<comp18_t> matrixH[NUM_ANT];
    stream<comp18_t> reoMatrixH2calcQ[NUM_ANT];
    stream<MATRIX_IN_T> matrixRhth;
    compFloat_t matrixHBuf[NUM_ANT][NUM_LTS][NUM_USED_SUBC];
    compFloat_t tmpInData;
    compFloat_t tmpOutData;
    compFloat_t tmpOutFloat;
    compFloat_t matrixHoutBuf[NUM_ANT][NUM_LTS][NUM_USED_SUBC];
    compFloat_t goldenHoutData[NUM_ANT][NUM_LTS][NUM_USED_SUBC];
    compFloat_t matrixRhthBuf[NUM_ANT][NUM_LTS][NUM_USED_SUBC];
    compFloat_t goldenRhthData[NUM_ANT][NUM_LTS][NUM_USED_SUBC];
    float rm, im;
    // Reading the input matrix Xin from the file
    FILE *fp_in;
    fp_in = fopen("reorderMatHin.txt", "r");
    if (fp_in == NULL) {
        printf("FILE NOT FOUND\n");// Error, file not found
        return 1;
    }
    for (int i = 0; i < NUM_USED_SUBC; i++) {
        for (int j = 0; j < NUM_ANT; j++) {
            for (int k = 0; k < NUM_LTS; k++) {
                fscanf(fp_in, "%f%fi\t", &rm, &im);
                tmpInData = {rm / 8192, im / 8192};
                matrixHBuf[j][k][i] = tmpInData;
            }
            fscanf(fp_in, "\n");
        }
    }
    fclose(fp_in);
    // Write the input matrix Xin to the .txt file
    FILE *fp_in_write;
    fp_in_write = fopen("reorderMatXin_hw.txt", "w");
    if (fp_in_write == NULL) {
        printf("FILE NOT FOUND\n");// Error, file not found
        return 1;
    }
    for (int i = 0; i < NUM_USED_SUBC; i++) {
        for (int j = 0; j < NUM_LTS; j++) {
            for (int k = 0; k < NUM_ANT; k++) {
                tmpInData = matrixHBuf[k][j][i];
                matrixH[k].write(tmpInData);
                fprintf(fp_in_write, "%f%+fi\t", (float)tmpInData.real(), (float)tmpInData.imag());
            }
            fprintf(fp_in_write, "\n");
        }
    }
    fclose(fp_in_write);
    // Call the calcMatrixRxtx function
    calcMatrixRhth(matrixH, reoMatrixH2calcQ, matrixRhth);

    FILE *fp_out;
    // Write the output data to the .txt file
    fp_out = fopen("matrixHout_hw.txt", "w");
    if (fp_out == NULL) {
        printf("FILE NOT FOUND\n");// Error, file not found
        return 1;
    }
    for (int i = 0; i < NUM_USED_SUBC; i++) {
        for (int j = 0; j < NUM_LTS; j++) {
            for (int k = 0; k < NUM_ANT; k++) {
                tmpOutData = reoMatrixH2calcQ[k].read();
                matrixHoutBuf[k][j][i] = {tmpOutData.real() * 8192, tmpOutData.imag() * 8192};
                fprintf(fp_out, "%f%+fi\t", (float)tmpOutData.real(), (float)tmpOutData.imag());
            }
            fprintf(fp_out, "\n");
        }
    }
    fclose(fp_out);
    // Write the output matrix Rxtx to the .txt file
    fp_out = fopen("matrixRhth_hw.txt", "w");
    if (fp_out == NULL) {
        printf("FILE NOT FOUND\n");// Error, file not found
        return 1;
    }
    for (int i = 0; i < NUM_USED_SUBC; i++) {
        for (int j = 0; j < NUM_ANT; j++) {
            for (int k = 0; k < NUM_LTS; k++) {
                tmpOutData = matrixRhth.read();
                //cout << "matrixRxtx[" << j << "][" << k << "][" << i << "] = " << tmpOutData << endl;
                tmpOutFloat = {tmpOutData.real(), tmpOutData.imag()};
                //cout << "tmpOutFloat[" << j << "][" << k << "][" << i << "] = " << tmpOutFloat << endl;
                matrixRhthBuf[j][k][i] = tmpOutFloat;
                fprintf(fp_out, "%f%+fi\t", (float)tmpOutFloat.real(), (float)tmpOutFloat.imag());
            }
            fprintf(fp_out, "\n");
        }
    }
    fclose(fp_out);
    // Read the golden data from the file
    FILE *fp_golden;
    fp_golden = fopen("reorderMatHin.txt", "r");
    if (fp_golden == NULL) {
        printf("FILE NOT FOUND\n");// Error, file not found
        return 1;
    }
    for (int i = 0; i < NUM_USED_SUBC; i++) {
        for (int j = 0; j < NUM_ANT; j++) {
            for (int k = 0; k < NUM_LTS; k++) {
                fscanf(fp_golden, "%f%fi\t", &rm, &im);
                goldenHoutData[j][k][i] = {rm, im};
            }
            fscanf(fp_golden, "\n");
        }    
    }
    fclose(fp_golden);
    fp_golden = fopen("matrixRhth.txt", "r");
    if (fp_golden == NULL) {
        printf("FILE NOT FOUND\n");// Error, file not found
        return 1;
    }
    for (int i = 0; i < NUM_USED_SUBC; i++) {
        for (int j = 0; j < NUM_ANT; j++) {
            for (int k = 0; k < NUM_LTS; k++) {
                fscanf(fp_golden, "%f%fi\t", &rm, &im);
                goldenRhthData[j][k][i] = {rm, im};
                //cout << "goldenData[" << j << "][" << k << "][" << i << "] = " << goldenData[j][k][i] << endl;
            }
            fscanf(fp_golden, "\n");
        }
    }
    fclose(fp_golden);
    // Compare the output data with the golden data
    int err = 0;
    for (int i = 0; i < NUM_USED_SUBC; i++) {
        for (int j = 0; j < NUM_LTS; j++) {
            for (int k = 0; k < NUM_ANT; k++) {
                if (std::abs(matrixHoutBuf[k][j][i].real() - goldenHoutData[k][j][i].real()) > 4 ||
                    std::abs(matrixHoutBuf[k][j][i].imag() - goldenHoutData[k][j][i].imag()) > 4) {
                    err++;
                    printf("ERROR: matrixXoutBuf[%d][%d][%d] = %f%+fi, goldenHoutData[%d][%d][%d] = %f%+fi\n", 
                        k, j, i, matrixHoutBuf[k][j][i].real(), matrixHoutBuf[k][j][i].imag(), 
                        k, j, i, goldenHoutData[k][j][i].real(), goldenHoutData[k][j][i].imag());
                }
            }
        }
    }
    for (int i = 0; i < NUM_USED_SUBC; i++) {
        for (int j = 0; j < NUM_ANT; j++) {
            for (int k = 0; k < NUM_LTS; k++) {
                if (std::abs(matrixRhthBuf[j][k][i].real() - goldenRhthData[j][k][i].real()) > 7 || 
                    std::abs(matrixRhthBuf[j][k][i].imag() - goldenRhthData[j][k][i].imag()) > 7) {
                    err++;
                    printf("Error: matrixRxtx[%d][%d][%d] = %f%+fi, goldenData[%d][%d][%d] = %f%+fi\n", 
                        j, k, i, (float)matrixRhthBuf[j][k][i].real(), (float)matrixRhthBuf[j][k][i].imag(), 
                        j, k, i, (float)goldenRhthData[j][k][i].real(), (float)goldenRhthData[j][k][i].imag());
                }
            }
        }
    }
    if (err == 0) {
        printf("Test passed\n");
    } else {
        printf("Test failed\n");
    }
    return err;
}
