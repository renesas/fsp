/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef HW_SCE_P_SUB_FUNC_HEADER_FILE
#define HW_SCE_P_SUB_FUNC_HEADER_FILE

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

typedef enum e_rsip_sel_bit_length
{
    RSIP_SEL_BIT_LENGTH_256,
    RSIP_SEL_BIT_LENGTH_384,
} rsip_sel_bit_length_t;

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
void HW_SCE_p_func_sub001(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);
void HW_SCE_p_func_sub002(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3);
void HW_SCE_p_func_sub003(uint32_t ARG1);
void HW_SCE_p_func_sub004(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3);
void HW_SCE_p_func_sub005(uint32_t ARG1, uint32_t ARG2);
void HW_SCE_p_func_sub006(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3);
void HW_SCE_p_func_sub007(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3);
void HW_SCE_p_func_sub008(uint32_t ARG1, uint32_t ARG2);
void HW_SCE_p_func_sub009(uint32_t ARG1, uint32_t ARG2);
void HW_SCE_p_func_sub010(uint32_t ARG1, uint32_t ARG2);
void HW_SCE_p_func_sub011(uint32_t ARG1, uint32_t ARG2);
void HW_SCE_p_func_sub012(void);
void HW_SCE_p_func_sub013(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3);
void HW_SCE_p_func_sub014(uint32_t ARG1);
void HW_SCE_p_func_sub015(uint32_t ARG1, uint32_t ARG2);
void HW_SCE_p_func_sub016(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3);
void HW_SCE_p_func_sub017(uint32_t ARG1, uint32_t ARG2);
void HW_SCE_p_func_sub018(uint32_t ARG1, uint32_t ARG2);
void HW_SCE_p_func_sub019(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3);
void HW_SCE_p_func_sub020(uint32_t ARG1);
void HW_SCE_p_func_sub021(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3);
void HW_SCE_p_func_sub022(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3);
void HW_SCE_p_func_sub100(const uint32_t        ARG1[],
                          const uint32_t        ARG2[],
                          const uint32_t        PARAM[],
                          rsip_sel_bit_length_t bit_len);

#endif                                 /* HW_SCE_P_SUB_FUNC_HEADER_FILE */
