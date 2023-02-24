/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

#include "hw_sce_ra_private.h"

void HW_SCE_Aes192EncryptDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[],
                                           const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        HW_SCE_p_func100(0x7f928370U, 0xaa486c0aU, 0x4e8f5fe7U, 0x6171b8b4U);

        WR1_PROG(REG_1444H, 0x00020061U);

        WR1_PROG(REG_182CH, 0x40000010U);
        WR1_PROG(REG_1824H, 0x0a008106U);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        HW_SCE_p_func100(0xcc66d49aU, 0x9acbaa84U, 0x4cf367f8U, 0x34270eccU);

        WR1_PROG(REG_1444H, 0x00020061U);

        WR1_PROG(REG_182CH, 0x40000010U);
        WR1_PROG(REG_1824H, 0x0a00810eU);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        HW_SCE_p_func100(0xe05f0c6aU, 0xc134cd35U, 0x8e587a55U, 0xcdb81fb1U);

        WR1_PROG(REG_1444H, 0x00020061U);

        WR1_PROG(REG_182CH, 0x40000010U);
        WR1_PROG(REG_1824H, 0x0e008506U);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        HW_SCE_p_func100(0x8407e485U, 0xf9751c03U, 0x694deeb4U, 0x6fbe56a6U);

        WR1_PROG(REG_1444H, 0x00020061U);

        WR1_PROG(REG_182CH, 0x40000010U);
        WR1_PROG(REG_1824H, 0x0900890eU);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000004U)
    {
        WR1_PROG(REG_1444H, 0x000003c2U);
        HW_SCE_p_func100(0x83e882d3U, 0x1c9dda4aU, 0x8c43c698U, 0xf60f3092U);

        WR1_PROG(REG_1444H, 0x00020061U);

        WR1_PROG(REG_182CH, 0x40000010U);
        WR1_PROG(REG_1824H, 0x07008d06U);
        WR1_PROG(REG_1408H, 0x000c1000U);
    }
    else
    {
        ;
    }

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

    WAIT_STS(REG_1408H, 30, 1);
    RD4_ADDR(REG_1420H, &OutData_Text[MAX_CNT - 4]);

    if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000000U)
    {
        HW_SCE_p_func214();

        HW_SCE_p_func101(0x24247570U, 0xb24cbc7dU, 0x409c2091U, 0xd5962a9eU);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000001U)
    {
        HW_SCE_p_func214();

        HW_SCE_p_func101(0x8bcb030cU, 0xfe165fedU, 0xe1b21f39U, 0xf291783fU);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000002U)
    {
        HW_SCE_p_func214();

        HW_SCE_p_func101(0x094c1352U, 0x27fc39d7U, 0x0b1cfbfeU, 0x694a734fU);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000003U)
    {
        HW_SCE_p_func214();

        HW_SCE_p_func101(0xf0408e8eU, 0xf8249f96U, 0x418f0479U, 0x485cc893U);
    }
    else if (RD1_MASK(REG_1440H, 0xffffffffU) == 0x00000004U)
    {
        HW_SCE_p_func214();

        HW_SCE_p_func101(0xadad7da5U, 0x03181adbU, 0xd2c507abU, 0x747dee88U);
    }
    else
    {
        ;
    }
}

