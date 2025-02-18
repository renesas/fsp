/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <stdint.h>
#include "bsp_api.h"
#if BSP_FEATURE_MACL_SUPPORTED
 #include "../bsp/mcu/all/bsp_macl.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup RM_CMSIS_DSP
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Perform multiplication via MACL module.
 *
 * @param[in]   pSrcA        Pointer which point to data A.
 * @param[in]   pSrcB        Pointer which point to data B.
 * @param[out]  pDst         Pointer to buffer which will hold the calculation result.
 * @param[in]   blockSize    Numbers of elements to be calculated.
 **********************************************************************************************************************/
void arm_mult_q31 (const q31_t * pSrcA, const q31_t * pSrcB, q31_t * pDst, uint32_t blockSize)
{
    R_BSP_MaclMulQ31(pSrcA, pSrcB, pDst, blockSize);
}

/*******************************************************************************************************************//**
 * Perform scaling a vector by multiplying scalar via MACL module.
 *
 * @param[in]   pSrc         Pointer which point to a vector.
 * @param[in]   scaleFract   Pointer to the scalar number.
 * @param[in]   shift        Number of bits to shift the result by
 * @param[out]  pDst         Pointer to buffer which will hold the calculation result.
 * @param[in]   blockSize    Numbers of elements to be calculated.
 **********************************************************************************************************************/
void arm_scale_q31 (const q31_t * pSrc, q31_t scaleFract, int8_t shift, q31_t * pDst, uint32_t blockSize)
{
    R_BSP_MaclScaleQ31(pSrc, scaleFract, shift, pDst, blockSize);
}

/*******************************************************************************************************************//**
 * Perform Q31 matrix multiplication via MACL module.
 *
 * @param[in]   pSrcA        Points to the first input matrix structure A.
 * @param[in]   pSrcB        Points to the second input matrix structure B.
 * @param[out]  pDst         Points to the buffer which hold output matrix structure.
 **********************************************************************************************************************/
arm_status arm_mat_mult_q31 (const arm_matrix_instance_q31 * pSrcA,
                             const arm_matrix_instance_q31 * pSrcB,
                             arm_matrix_instance_q31       * pDst)
{
    arm_status status;                 // Status of matrix multiplication

 #ifdef ARM_MATH_MATRIX_CHECK

    /* Check for matrix mismatch condition */
    if ((pSrcA->numCols != pSrcB->numRows) ||
        (pSrcA->numRows != pDst->numRows) ||
        (pSrcB->numCols != pDst->numCols))
    {
        /* Set status as ARM_MATH_SIZE_MISMATCH */
        status = ARM_MATH_SIZE_MISMATCH;

        /* Return to application */
        return status;
    }
 #endif                                // #ifdef ARM_MATH_MATRIX_CHECK

    /* Enable multiply-accumulate operation in normal mode */
    R_MACL->MULC = BSP_MACL_FIXED_POINT_MODE_DISABLE;

    R_BSP_MaclMatMulQ31(pSrcA, pSrcB, pDst);

    /* Set status as ARM_MATH_SUCCESS */
    status = ARM_MATH_SUCCESS;

    /* Return to application */
    return status;
}

/*******************************************************************************************************************//**
 * Perform Q31 matrix and vector multiplication via MACL module.
 *
 * @param[in]   pSrcMat      Points to the first input matrix structure.
 * @param[in]   pVec         Points to the input vector.
 * @param[out]  pDst         Points to the buffer which hold the output vector.
 **********************************************************************************************************************/
void arm_mat_vec_mult_q31 (const arm_matrix_instance_q31 * pSrcMat, const q31_t * pVec, q31_t * pDst)
{
    R_BSP_MaclMatVecMulQ31(pSrcMat, pVec, pDst);
}

/*******************************************************************************************************************//**
 * Perform scaling a matrix by multiplying scalar via MACL module.
 *
 * @param[in]   pSrc         Points to the vector.
 * @param[in]   scaleFract   Points to the scalar number.
 * @param[in]   shift        Number of bits to shift the result by
 * @param[out]  pDst         Points to the buffer which will hold the calculation result.
 **********************************************************************************************************************/
arm_status arm_mat_scale_q31 (const arm_matrix_instance_q31 * pSrc,
                              q31_t                           scaleFract,
                              int32_t                         shift,
                              arm_matrix_instance_q31       * pDst)
{
    arm_status status;                 // Status of matrix scaling

 #ifdef ARM_MATH_MATRIX_CHECK

    /* Check for matrix mismatch condition */
    if ((pSrc->numRows != pDst->numRows) ||
        (pSrc->numCols != pDst->numCols))
    {
        /* Set status as ARM_MATH_SIZE_MISMATCH */
        status = ARM_MATH_SIZE_MISMATCH;

        /* Return to application */
        return status;
    }
 #endif                                // #ifdef ARM_MATH_MATRIX_CHECK

    R_BSP_MaclMatScaleQ31(pSrc, scaleFract, shift, pDst);

    /* Set status as ARM_MATH_SUCCESS */
    status = ARM_MATH_SUCCESS;

    /* Return to application */
    return status;
}

/*******************************************************************************************************************//**
 * Perform the biquad cascade direct form I filter in Q31 via MACL module.
 *
 * @param[in]   S            Points to an instance of the Q31 Biquad cascade structure.
 * @param[in]   pSrc         Points to the block of input data.
 * @param[out]  pDst         Points to the block of output data.
 * @param[in]   blockSize    Number of samples to process.
 **********************************************************************************************************************/
void arm_biquad_cascade_df1_q31 (const arm_biquad_casd_df1_inst_q31 * S,
                                 const q31_t                        * pSrc,
                                 q31_t                              * pDst,
                                 uint32_t                             blockSize)
{
    R_BSP_MaclBiquadCsdDf1Q31(S, pSrc, pDst, blockSize);
}

/*******************************************************************************************************************//**
 * Perform the convolution in Q31 via MACL module.
 *
 * @param[in]   pSrcA           Points to the first input sequence.
 * @param[in]   srcALen         Length of the first input sequence.
 * @param[in]   pSrcB           Points to the second input sequence.
 * @param[in]   srcBLen         Length of the second input sequence.
 * @param[out]  pDst            Points to the location where the output result is written.  Length srcALen+srcBLen-1.
 **********************************************************************************************************************/
void arm_conv_q31 (const q31_t * pSrcA, uint32_t srcALen, const q31_t * pSrcB, uint32_t srcBLen, q31_t * pDst)
{
    R_BSP_MaclConvQ31(pSrcA, srcALen, pSrcB, srcBLen, pDst);
}

/*******************************************************************************************************************//**
 * Perform the partial convolution in Q31 via MACL module.
 *
 * @param[in]   pSrcA            Points to the first input sequence.
 * @param[in]   srcALen          Length of the first input sequence.
 * @param[in]   pSrcB            Points to the second input sequence.
 * @param[in]   srcBLen          Length of the second input sequence.
 * @param[out]  pDst             Points to the location where the output result is written.
 * @param[in]   firstIndex       Is the first output sample to start with.
 * @param[in]   numPoints        Is the number of output points to be computed.
 **********************************************************************************************************************/
arm_status arm_conv_partial_q31 (const q31_t * pSrcA,
                                 uint32_t      srcALen,
                                 const q31_t * pSrcB,
                                 uint32_t      srcBLen,
                                 q31_t       * pDst,
                                 uint32_t      firstIndex,
                                 uint32_t      numPoints)
{
    arm_status status;                 // Status of the partial convolution

    status = R_BSP_MaclConvPartialQ31(pSrcA, srcALen, pSrcB, srcBLen, pDst, firstIndex, numPoints);

    /* Return to application */
    return status;
}

/*******************************************************************************************************************//**
 * Perform the Q31 FIR Decimate Q31 via MACL module.
 *
 * @param[in]   S              Points to an instance of the Q31 FIR decimator structure.
 * @param[in]   pSrc           Points to the block of input data.
 * @param[out]  pDst           Points to the block of output data.
 * @param[in]   blockSize      Number of samples to process.
 **********************************************************************************************************************/
void arm_fir_decimate_q31 (const arm_fir_decimate_instance_q31 * S, const q31_t * pSrc, q31_t * pDst,
                           uint32_t blockSize)
{
    R_BSP_MaclFirDecimateQ31(S, pSrc, pDst, blockSize);
}

/*******************************************************************************************************************//**
 * Perform the Q31 FIR interpolator via MACL module.
 *
 * @param[in]   S             Points to an instance of the Q31 FIR interpolator structure.
 * @param[in]   pSrc          Points to the block of input data.
 * @param[out]  pDst          Points to the block of output data.
 * @param[in]   blockSize     Number of samples to process.
 **********************************************************************************************************************/
void arm_fir_interpolate_q31 (const arm_fir_interpolate_instance_q31 * S,
                              const q31_t                            * pSrc,
                              q31_t                                  * pDst,
                              uint32_t                                 blockSize)
{
    R_BSP_MaclFirInterpolateQ31(S, pSrc, pDst, blockSize);
}

/*******************************************************************************************************************//**
 * Perform the Q31 Correlate via MACL module.
 *
 * @param[in]   pSrcA     Points to the first input sequence.
 * @param[in]   srcALen   Length of the first input sequence.
 * @param[in]   pSrcB     Points to the second input sequence.
 * @param[in]   srcBLen   Length of the second input sequence.
 * @param[out]  pDst      Points to the location where the output result is written.  Length 2 * max(srcALen, srcBLen) - 1.
 **********************************************************************************************************************/
void arm_correlate_q31 (const q31_t * pSrcA, uint32_t srcALen, const q31_t * pSrcB, uint32_t srcBLen, q31_t * pDst)
{
    R_BSP_MaclCorrelateQ31(pSrcA, srcALen, pSrcB, srcBLen, pDst);
}

/*******************************************************************************************************************//**
 * Perform the Q31 FIR Sparse filter via MACL module.
 *
 * @param[in]   S              Points to an instance of the Q31 sparse FIR structure.
 * @param[in]   pSrc           Points to the block of input data.
 * @param[out]  pDst           Points to the block of output data.
 * @param[in]   pScratchIn     Points to a temporary buffer of size blockSize.
 * @param[in]   blockSize      Number of input samples to process.
 **********************************************************************************************************************/
void arm_fir_sparse_q31 (arm_fir_sparse_instance_q31 * S,
                         const q31_t                 * pSrc,
                         q31_t                       * pDst,
                         q31_t                       * pScratchIn,
                         uint32_t                      blockSize)
{
    R_BSP_MaclFirSparseQ31(S, pSrc, pDst, pScratchIn, blockSize);
}

/*******************************************************************************************************************//**
 * Perform the Q31 normalized LMS filter via MACL module.
 *
 * @param[in]   S             Points to an instance of the Q31 normalized LMS filter structure.
 * @param[in]   pSrc          Points to the block of input data.
 * @param[in]   pRef          Points to the block of reference data.
 * @param[out]  pOut          Points to the block of output data.
 * @param[out]  pErr          Points to the block of error data.
 * @param[in]   blockSize     Number of samples to process.
 **********************************************************************************************************************/
void arm_lms_norm_q31 (arm_lms_norm_instance_q31 * S,
                       const q31_t               * pSrc,
                       q31_t                     * pRef,
                       q31_t                     * pOut,
                       q31_t                     * pErr,
                       uint32_t                    blockSize)
{
    R_BSP_MaclLmsNormQ31(S, pSrc, pRef, pOut, pErr, blockSize);
}

/*******************************************************************************************************************//**
 * Perform the Q31 LMS filter via MACL module.
 *
 * @param[in]   S             Points to an instance of the Q31 LMS filter structure.
 * @param[in]   pSrc          Points to the block of input data.
 * @param[in]   pRef          Points to the block of reference data.
 * @param[out]  pOut          Points to the block of output data.
 * @param[out]  pErr          Points to the block of error data.
 * @param[in]   blockSize     Number of samples to process.
 **********************************************************************************************************************/
void arm_lms_q31 (const arm_lms_instance_q31 * S,
                  const q31_t                * pSrc,
                  q31_t                      * pRef,
                  q31_t                      * pOut,
                  q31_t                      * pErr,
                  uint32_t                     blockSize)
{
    R_BSP_MaclLmsQ31(S, pSrc, pRef, pOut, pErr, blockSize);
}

/*******************************************************************************************************************//**
 * Perform the Q31 FIR filter via MACL module.
 *
 * @param[in]   S            Points to an instance of the Q31 FIR filter structure.
 * @param[in]   pSrc         Points to the block of input data.
 * @param[out]  pErr         Points to the block of output data.
 * @param[in]   blockSize    Number of samples to process.
 **********************************************************************************************************************/
void arm_fir_q31 (const arm_fir_instance_q31 * S, const q31_t * pSrc, q31_t * pDst, uint32_t blockSize)
{
    R_BSP_MaclFirQ31(S, pSrc, pDst, blockSize);
}

#endif

/******************************************************************************************************************//**
 * @} (end addtogroup RM_CMSIS_DSP)
 **********************************************************************************************************************/
