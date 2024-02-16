For arduino_entropy_FFT.ino

This code performs two main tasks:

1. Collecting Entropy-Based Random Numbers:

The Entropy.h library utilizes hardware resources to gather randomness from environmental noise or other unpredictable sources.
SAMPLES number of 16-bit integer samples are collected.
Each sample is obtained by calling Entropy.random() if enough entropy is available, otherwise it's set to 0.
The random values are mapped to the int16_t range (-32768 to 32767) and printed to the serial monitor.
The collection time is measured and printed.
2. Fast Fourier Transform (FFT) Calculation:

The collected samples are treated as an analog signal and analyzed for frequency content.
A manual implementation of the Fast Fourier Transform (FFT) algorithm is used to compute the magnitude of each frequency component.
Only the first third of the frequencies are analyzed as the Nyquist limit restricts meaningful results past half the sampling frequency.
The frequency and magnitude for each analyzed component are printed to the serial monitor.
The FFT calculation time is measured and printed.
Key Points:

The code relies on the Entropy.h library for randomness generation.
It demonstrates a basic approach to using entropy as a source of randomness.
The manual FFT implementation showcases the algorithm but might not be the most efficient choice in all scenarios.
The printed values provide insights into the frequency distribution of the random numbers obtained from the entropy source.
Additional Notes:

The specific behavior of the Entropy.h library might vary depending on the hardware and implementation details.
Alternative libraries or approaches can be used for both random number generation and FFT calculations.
Consider optimizing the FFT implementation for better performance if necessary.


This code combines aspects of the previous examples, focusing on generating truly random numbers and analyzing their frequency components. Let's break down what's happening:

**Overall Goal**

1. **Generate High-Quality Random Numbers:** The core aim is to produce  random numbers based on hardware entropy sources for better quality in spectral analysis.
2. **Calculate Frequency Spectrum (FFT):** Use the Fast Fourier Transform to analyze the generated random numbers, identifying dominant frequencies.
3. **Detect Significant Frequencies:** Print the prominent frequencies observed in the random data  while taking steps to reduce redundant output.

**Explanation**

**Includes and Defines:** (Similar to earlier explanations)

**Setup:** (Identical to the previous explanations)

**Loop**

1. **Array Declarations:**  (Identical to the previous explanations)

2. **High-Quality Random Number Generation:** 
   * **Starts timing.**
   * **`uint32_t random_value = 0;`** Initializes a variable to hold the random value.
   * **`int bits_collected = 0;`** A counter to track collected entropy bits.
   * **Accumulation Loop:** Iterates until `BITS_TO_ACCUMULATE` random bits are collected. This guarantees better randomness than directly reading smaller values.
     * **`Entropy.available()`:** Checks if randomness data is available from the  entropy source. 
     * **Bit Shifting and Masking:** 
       * `(random_value << 1) `: Shifts bits to the left, preparing for a new random bit.
       * `Entropy.random() & 1`: Gets a single bit (0 or 1) from the entropy source.
       * `|`:  "OR" operation adds the new random bit to `random_value`. 
   * **Mapping:** Maps the accumulated raw random number onto the range -32768 to 32767.
   * **Printing, Delay:** Prints the sample and creates a pause to maintain `SAMPLING_FREQUENCY`.
   * **Ends timing.**

3. **FFT Calculations:** (Essentially the same as before)
   * **Timing, FFT Call, etc.**

4. **Serial Plotter Output:** (Commented out like in the first example)

5. **Magnitude Calculation:**  Iterates to calculate the magnitude for each frequency component

6. **Frequency Detection with Hysteresis:** (Identical to earlier explanations)

7. **Quiescent Delay:** A brief pause with `delay(QUIESCENT_DELAY)`.

**FFT Function (`FFT()`):**
   *  A recursive implementation of the Fast Fourier Transform. If you're not familiar with the FFT itself, there are many great online resources that explain the details of how it works!

**Key Differences from Previous Examples**

* **Bit Accumulation:** The focus is on collecting multiple bits and combining them through shifting and masking for higher-quality random numbers.
* **Simplified Sampling Delay:** The delay calculation in the generation loop is a bit simpler as the randomness quality relies on bit accumulation, not precise timing from  `Entropy.random()`.

**In Summary**

This code aims to generate random numbers based on a hardware entropy source (watchdog timer in this case). It then performs a spectrum analysis of these random numbers, looking for any dominant frequencies, and uses hysteresis to make the output less repetitive.

**Let me know if you want a deeper dive into any specific aspect of the code!** 

R4 NOTES:

To run the mbedCrypto implementation of the PSA Crypto API on the MCU, the macro MBEDTLS_ENTROPY_HARDWARE_ALT must be defined in the configuration file. This enables using the TRNG as an entropy source. None of the other cryptographic operations (even in software only mode) will work without this feature.



mbedtls_platform_setup()

int mbedtls_platform_setup(mbedtls_platform_context * ctx)

This function initializes the SCE and the TRNG. It must be invoked before the crypto library can be used. This implementation is used if MBEDTLS_PLATFORM_SETUP_TEARDOWN_ALT is defined.

Example:

    mbedtls_platform_context ctx = {0};

    /* Setup the platform; initialize the SCE and the TRNG */

    if (PSA_SUCCESS != mbedtls_platform_setup(&ctx))

Return values

0Initialization was successful.MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILEDSCE Initialization error.

◆ mbedtls_platform_teardown()

void mbedtls_platform_teardown(mbedtls_platform_context * ctx)

This implementation is used if MBEDTLS_PLATFORM_SETUP_TEARDOWN_ALT is defined. It is intended to de-initialize any items that were initialized in the mbedtls_platform_setup() function, but currently is only a placeholder function.

Example:

    /* De-initialize the platform. This is currently a placeholder function which does not do anything. */

    mbedtls_platform_teardown(&ctx);

Return values

N/A

◆ RM_PSA_CRYPTO_TRNG_Read()

fsp_err_t RM_PSA_CRYPTO_TRNG_Read(uint8_t *const p_rngbuf,uint32_t num_req_bytes,uint32_t * p_num_gen_bytes )

Reads requested length of random data from the TRNG. Generate nbytes of random bytes and store them in p_rngbuf buffer.



Return values

FSP_SUCCESSRandom number generation successfulFSP_ERR_ASSERTIONNULL input parameter(s).FSP_ERR_CRYPTO_UNKNOWNAn unknown error occurred.

Returns

See Common Error Codes or functions called by this function for other possible return codes. This function calls:

s_generate_16byte_random_data
