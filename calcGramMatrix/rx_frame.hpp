//////////////////////////////////////////////////////////////////////////////
// Description: This file contains the class definition for the TxFrame class.
// The TxFrame class is used to encapsulate the data and metadata for a
// single frame of data to be transmitted.
//////////////////////////////////////////////////////////////////////////////
#include "ap_int.h"
#include "hls_math.h"
#include "hls_stream.h"
#include "ap_fixed.h"
#include <complex>
#include <cmath>
#include "hls_fft.h"

using namespace hls;

#ifndef __TX_FRAME_HPP__
#define __TX_FRAME_HPP__

#endif // __TX_FRAME_HPP__



//#define W 16  // Word length
//#define I 1  // Integer length

typedef ap_uint<2> uint2_t;
typedef ap_uint<4> uint4_t;
//typedef ap_uint<8> uint8_t;
typedef ap_uint<10> uint10_t;
//typedef ap_fixed<W, I, AP_TRN, AP_SAT> fixed16_t;
typedef ap_ufixed<16, 2> ufixed16i2_t;
typedef ap_fixed<16, 6> fixed16i6_t;
typedef ap_ufixed<16, 8> ufixed16i8_t;
typedef ap_ufixed<24, 8> ufixed24i8_t;
typedef ap_fixed<16, 1> fixed16_t;
typedef std::complex<fixed16_t> comp16_t;
typedef ap_fixed<16, 2> fixed16i2_t;
typedef std::complex<fixed16i2_t> comp16i2_t;
typedef ap_fixed<17, 2> fixed17_t;
typedef std::complex<fixed17_t> comp17_t;
typedef ap_fixed<18, 3> fixed18_t;
//typedef ap_fixed<20, 3> fixed18_t;
typedef std::complex<fixed18_t> comp18_t;
typedef ap_fixed<20, 5> fixed20_t;
//typedef ap_fixed<22, 5> fixed20_t;
typedef std::complex<fixed20_t> comp20_t;
typedef ap_fixed<20, 5> fixed20_t;
typedef std::complex<fixed20_t> comp20_t;
typedef ap_fixed<22, 5> fixed22_t;
typedef std::complex<fixed22_t> comp22_t;
typedef ap_fixed<24, 5> fixed24_t;
typedef std::complex<fixed24_t> comp24_t;
typedef ap_fixed<26, 5> fixed26_t;
typedef std::complex<fixed26_t> comp26_t;
//typedef ap_fixed<24, 9> fixed24_t;
//typedef std::complex<fixed24_t> comp24_t;
typedef ap_int<14> int14_t;
typedef std::complex<int14_t> compi14_t;
typedef std::complex<short> compShort_t;
typedef std::complex<float> compFloat_t;

// Hamming code parameters
// Data and parity bits are arranged as follows:
// [p1 p2 p3 d1 d2 d3 d4]
/* number of uncoded data bits and data values */
#define DATA_BITS       4
#define DATA_VALUES     (1 << DATA_BITS)

/* number of parity bits and data values */
#define PARITY_BITS     3
#define PARITY_VALUES   (1 << PARITY_BITS)

/* number of code bits (data + parity) and data values */
#define CODE_BITS       (DATA_BITS + PARITY_BITS)
#define CODE_VALUES     (1 << CODE_BITS)

#define AP 0
#define UE 1
#define SELECT_SUBC 0 // Select subcarrier without feedback precoding

#define NUM_UE 4  // Number of UEs
#define NUM_STRM 4  // Number of streams
#define UE_BITS 2  // Number of UE bits
#define MOD_BITS 3  // Number of modulation bits
#define PHY_HEADER_BITS 2  // Number of PHY header bits
#define STRM_BITS 2  // Number of stream bits
#define STRM_LEN_BITS 10  // Number of stream length bits
#define MAC_DATA_BITS 8  // Number of MAC data bits

#define DATA_SUBC_OFFSET 1  // Data subcarrier offset

#define NUM_ANT 8  // Number of antennas
#define NUM_CHOLS 4  // Number of Cholesky decomposition kernels
#define NUM_FFT_PE 1  // Number of FFT kernels
#define NUM_FFT_REUSED (NUM_ANT / NUM_FFT_PE)  // Number of FFT kernels reused

#define BS_II 1  // Second stage II
#define FS_II 1  // First stage II
#define MF_II 1  // Matrix filter II
#define GM_II 12  // Generate matrix II
#define CE_II 1  // Channel estimation II

#define NUM_DATA_SUBC 14  // Number of data subcarriers
#define NUM_PILOTS 2  // Number of pilot subcarriers
#define NUM_USED_SUBC (NUM_DATA_SUBC + NUM_PILOTS)  // Total number of subcarriers

#define NUM_PREFIX_ZERO 96  // Number of prefix zeros
#define NUM_STS 144  // Number of space-time streams
#define NUM_LTS 8 // Number of LTS symbols
#define NUM_PHY_HEADER 1  // Number of PHY header units
#define NUM_PAYLOAD 16  // Number of payload units
#define NUM_EQUAL_SYMBOLS (NUM_PHY_HEADER + NUM_PAYLOAD)  // Number of equalizer symbols
#define NUM_TOTAL_SYMBOLS (NUM_LTS + NUM_PHY_HEADER + NUM_PAYLOAD)  // Total number of symbols

#define NUM_BITS_PER_SYMBOL 2  // Number of bits per symbol

#define MAX_BYTES_BPSK (NUM_PAYLOAD * NUM_DATA_SUBC / 8)  // Maximum number of bytes for BPSK
#define MAX_BYTES_QPSK (NUM_PAYLOAD * NUM_DATA_SUBC / 4)  // Maximum number of bytes for QPSK
#define MAX_BYTES_16QAM (NUM_PAYLOAD * NUM_DATA_SUBC / 2)  // Maximum number of bytes for 16QAM

#define U_FFT_LENGTH (1 << 6)
#define CP_LENGTH (U_FFT_LENGTH / 4)
#define SYMBOL_LENGTH (U_FFT_LENGTH + CP_LENGTH)

#define NUM_DATA_SAMPLES (NUM_TOTAL_SYMBOLS * SYMBOL_LENGTH)  // Number of data samples
#define MAX_FRAME_SIZE 112  // Maximum frame size

#define BYTE_LEN 56
#define TX_SIGNAL_SCALAR 2048  // Scalar for the transmitted signal
