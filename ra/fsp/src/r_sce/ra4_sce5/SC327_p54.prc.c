/////////////////////////////////////////////////////////////////////////
// <SC32#7 AES-256 Encryption with CBC Mode(hidden key)>               //
// Procedure number: 54                                                //
// File name      : SC327_p54L.prc                                     //
// State Diagram  : main(FSM1)                                         //
// Start State    : main03                                             //
// End State      : main03                                             //
// Input Data     : InData_KeyIndex[13]                                //
//                : InData_IV[4]                                       //
//                : InData_Text[MAX_CNT]                               //
// Output Data    : OutData_Text[MAX_CNT]                              //
//                : (MAX_CNT is Multiples of four.)                    //
//                : OutData_IV[4]                                      //
// Return Value   : Pass, Fail, HRK_Invalid_Index or Resource_Conflict //
//---------------------------------------------------------------------//
// total cycle    : polling + write access + read access               //
// polling        : 753 + (MAX_CNT/4-1)*61 cycle                       //
// polling access :  28 + (MAX_CNT/4-1)*2  times                       //
// write access   : 102 + (MAX_CNT-4) times                            //
// read  access   :  11 + (MAX_CNT-4) times                            //
/////////////////////////////////////////////////////////////////////////

#include "hw_sce_private.h"
#include "hw_sce_aes_private.h"
#include "SCE_ProcCommon.h"

fsp_err_t HW_SCE_AES_256CbcEncryptUsingEncryptedKey (const uint32_t * InData_KeyIndex,
                                                     const uint32_t * InData_IV,
                                                           uint32_t   num_words,
                                                     const uint32_t * InData_Text,
                                                           uint32_t * OutData_Text,
                                                           uint32_t * OutData_IV)
{
    uint32_t iLoop, MAX_CNT = num_words;

    if(RD1_MASK(REG_1BCH, 0x0000001f) != 0x0000000) {
        // Busy now then retry later;
        // Because  1_xxxx other processing box is in duty.
        //          x_1xxx resource D is in duty,then retry after you released D.
        //          x_x1xx resource C is in duty,then retry after you released C.
        //          x_xx1x resource B is in duty,then retry after you released B.
        //          x_xxx1 resource A is in duty,then retry after you released A.
        // A,B,C,D: see TrustedSystem datasheet
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    
    WR1_PROG(REG_84H, 0x00005401);
    WR1_PROG(REG_108H, 0x00000000);
    
    WR1_PROG(REG_1C0H, 0x00130013);
    
    WR1_PROG(REG_B0H, 0x10000000);
    WR1_PROG(REG_A4H, 0x00008884);
    WAIT_STS(REG_00H, 21, 1);
    WR1_ADDR(REG_A0H, &InData_KeyIndex[0]);
    WR1_PROG(REG_B0H, 0x00000000);
    
    WR1_PROG(REG_A4H, 0x600c3a0d);
    WR1_PROG(REG_00H, 0x00001113);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    
    WR1_PROG(REG_A4H, 0x400c0a0c);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x615e8e97);
    
    SC327_function001(0x45b03e79, 0x507b8d45, 0x1507784d, 0xe75d43fe);
    WR1_PROG(REG_B0H, 0x10000100);
    WR1_PROG(REG_A4H, 0x00008887);
    WAIT_STS(REG_00H, 21, 1);
    WR4_ADDR(REG_A0H, &InData_KeyIndex[1]);
    WAIT_STS(REG_00H, 21, 1);
    WR4_ADDR(REG_A0H, &InData_KeyIndex[5]);
    WR1_PROG(REG_B0H, 0x00000000);
    
    WR1_PROG(REG_A4H, 0x42f8063d);
    WR1_PROG(REG_00H, 0x00001113);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    
    SC327_function001(0x0a2c55f6, 0x999118a1, 0x781c17a2, 0x660d3a7e);
    WR1_PROG(REG_A4H, 0x40f9063d);
    WR1_PROG(REG_00H, 0x00001113);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    
    WR1_PROG(REG_B0H, 0x10000000);
    WR1_PROG(REG_A4H, 0x400086bd);
    WAIT_STS(REG_00H, 21, 1);
    WR4_ADDR(REG_A0H, &InData_KeyIndex[9]);
    WR1_PROG(REG_B0H, 0x00000000);
    
    WR1_PROG(REG_A4H, 0x00900c45);
    WR1_PROG(REG_00H, 0x00001113);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    
    SC327_function001(0x59fd64dc, 0xa86ea758, 0xfefc1fe2, 0x9cfe2221);
    WR1_PROG(REG_1CH, 0x00400000);
    WR1_PROG(REG_1D0H, 0x00000000);
    
    if(CHCK_STS(REG_1CH, 22, 1)) {
        
        WR1_PROG(REG_1C0H, 0x00130000);
        
        SC327_function003(0x32befef6, 0x3a48acb0, 0xd73a8150, 0x36993017);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_18H, 12, 0);
        return FSP_ERR_CRYPTO_SCE_HRK_INVALID_INDEX;
    }
    else {
        
        WR1_PROG(REG_B0H, 0x10000000);
        WR1_PROG(REG_A4H, 0x00048805);
        WAIT_STS(REG_00H, 21, 1);
        WR4_ADDR(REG_A0H, &InData_IV[0]);
        WR1_PROG(REG_B0H, 0x00000000);
        
        SC327_function001(0xfc9e0b24, 0xd2fca48c, 0x6198faa8, 0xea8ce3d1);
        //Host DMA Setting(if use DMA)
        //Transfer DATA is 128bits(4words) for each request
        //DMA request count is (MAX_CNT/4) times
        //DMA request signal are WRRDYB_0,RDRDYB_0
        //Input,Output Register is REG_A0H
        
        WR1_PROG(REG_B0H, 0x700000C0);
        WR1_PROG(REG_A4H, 0x00008c9e); //Enable request signals(WRRDYB_0,RDRDYB_0)
        
        // if you use DMA, you may release cpu
        
        //if use polling
        //=====<polling_start>=====
        WAIT_STS(REG_00H, 21, 1);
        WR4_ADDR(REG_A0H, &InData_Text[0]);
        for (iLoop = 4; iLoop < MAX_CNT ; iLoop = iLoop + 4) {
            WAIT_STS(REG_00H, 21, 1);
            WR4_ADDR(REG_A0H, &InData_Text[iLoop]);
            WAIT_STS(REG_00H, 16, 1);
            RD4_ADDR(REG_A0H, &OutData_Text[iLoop-4]);
        }
        WAIT_STS(REG_00H, 16, 1);
        RD4_ADDR(REG_A0H, &OutData_Text[MAX_CNT-4]);
        //=====<polling_end>=====
        
        WR1_PROG(REG_1CH, 0x002c0000);
        WR1_PROG(REG_1CH, 0x002d0000);
        WR1_PROG(REG_B0H, 0x00000001);
        WR1_PROG(REG_1D0H, 0x00000000);
        WR1_PROG(REG_A4H, 0x00008000); //Disable request signal(WRRDYB_0,RDRDYB_0)
        
        SC327_function001(0x76fa3cfc, 0x10400fd3, 0x06a14a7d, 0x62ce33a3);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);
        
        if(CHCK_STS(REG_1CH, 22, 1)) {
            
            WR1_PROG(REG_1CH, 0x002d0000);
            
            SC327_function001(0xfe664105, 0xe0c876ab, 0x2bafc338, 0xc51d8493);
            WR1_PROG(REG_1CH, 0x00400000);
            WR1_PROG(REG_1D0H, 0x00000000);
            
            if(CHCK_STS(REG_1CH, 22, 1)) {
                WR1_PROG(REG_00H, 0x00000113);
                WAIT_STS(REG_00H, 25, 0);
                WR1_PROG(REG_1CH, 0x00001800);
                
                SC327_function002(0xa433673b, 0x01e694ef, 0x621bdbd1, 0x1f177fbf);
            }
            else {
                
                SC327_function002(0xddea1628, 0xa9025871, 0x64c1a474, 0x0165f211);
            }
            
            WR1_PROG(REG_1C0H, 0x00130000);
            
            SC327_function003(0x8cc5d16f, 0x4e60c2c0, 0xc8480a81, 0x47c12d2f);
            WR1_PROG(REG_1BCH, 0x00000040);
            WAIT_STS(REG_18H, 12, 0);
            
            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else {
            
            SC327_function001(0xaeb5363a, 0x4af13cf2, 0x1b4675df, 0x0a78f989);
            
            WR1_PROG(REG_104H, 0x00000051);
            WR1_PROG(REG_A4H, 0x00000684);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, 0x00000000);
            
            WR1_PROG(REG_04H, 0x00000113);
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_A0H, &OutData_IV[0]);
            
            WR1_PROG(REG_1C0H, 0x00130000);
            
            SC327_function003(0x53d2b519, 0x1efd7c00, 0x62294886, 0xc20710bc);
            WR1_PROG(REG_1BCH, 0x00000040);
            WAIT_STS(REG_18H, 12, 0);
            
            return FSP_SUCCESS;
        }
    }
    
}

