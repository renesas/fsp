/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

void HW_SCE_Aes128GcmDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    HW_SCE_p_func100(0xa4a57ffbU, 0x255e5ab8U, 0x8cdd131eU, 0xd202720dU);

    WR1_PROG(REG_1444H, 0x00020061U);
    WR1_PROG(REG_182CH, 0x00018020U);
    WR1_PROG(REG_1824H, 0x07008d06U);
    WR1_PROG(REG_1408H, 0x000c1000U);

    WAIT_STS(REG_1444H, 31, 1);
    WR4_ADDR(REG_1420H, &InData_Text[0]);
    for (iLoop = 4U; iLoop < MAX_CNT; )
    {
        WAIT_STS(REG_1444H, 31, 1);
        WR4_ADDR(REG_1420H, &InData_Text[iLoop]);
        WAIT_STS(REG_1408H, 30, 1);
        RD4_ADDR(REG_1420H, &OutData_Text[iLoop - 4]);
        iLoop = iLoop + 4U;
    }

    WR1_PROG(REG_1458H, 0x00000000U);
    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &OutData_Text[iLoop - 4]);

    HW_SCE_p_func202();

    HW_SCE_p_func101(0x05fa92b2U, 0xcd538548U, 0x0f21e78cU, 0xf9b8322eU);
}
