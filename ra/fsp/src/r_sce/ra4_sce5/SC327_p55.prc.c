/////////////////////////////////////////////////////////////////////////
// <SC32#7 AES-256 Decryption with CBC Mode(hidden key)>               //
// Procedure number: 55                                                //
// File name      : SC327_p55L.prc                                     //
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
// polling        : 815 + (MAX_CNT/4-1)*61 cycle                       //
// polling access :  28 + (MAX_CNT/4-1)*2  times                       //
// write access   : 102 + (MAX_CNT-4) times                            //
// read  access   :  11 + (MAX_CNT-4) times                            //
/////////////////////////////////////////////////////////////////////////

#include "hw_sce_private.h"
#include "hw_sce_aes_private.h"
#include "SCE_ProcCommon.h"

fsp_err_t HW_SCE_AES_256CbcDecryptUsingEncryptedKey (const uint32_t * InData_KeyIndex,
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
    
    WR1_PROG(REG_84H, 0x00005501);
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
    
    SC327_function001(0x8764756f, 0xeb65efab, 0x7ef4c4d9, 0x0e963488);
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
    
    SC327_function001(0x8ef40ee2, 0x45caabc3, 0xb32443f1, 0x0d605092);
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
    
    SC327_function001(0xcaf8a10c, 0x5722c21a, 0x708bb595, 0x32b07d00);
    WR1_PROG(REG_1CH, 0x00400000);
    WR1_PROG(REG_1D0H, 0x00000000);
    
    if(CHCK_STS(REG_1CH, 22, 1)) {
        
        WR1_PROG(REG_1C0H, 0x00130000);
        
        SC327_function003(0x50d3ccb5, 0x90357c7b, 0x03b3d74c, 0x033195e3);
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
        
        SC327_function001(0x21a5a4bb, 0x72693592, 0xa2db0fb8, 0x277da523);
        //Host DMA Setting(if use DMA)
        //Transfer DATA is 128bits(4words) for each request
        //DMA request count is (MAX_CNT/4) times
        //DMA request signal are WRRDYB_0,RDRDYB_0
        //Input,Output Register is REG_A0H
        
        WR1_PROG(REG_B0H, 0x700000C0);
        WR1_PROG(REG_A4H, 0x0000c9ae); //Enable request signals(WRRDYB_0,RDRDYB_0)
        
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
        
        SC327_function001(0x5665517c, 0xfbae2735, 0x42c32760, 0x2d43762b);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);
        
        if(CHCK_STS(REG_1CH, 22, 1)) {
            
            WR1_PROG(REG_1CH, 0x002d0000);
            
            SC327_function001(0x1b4f3b4e, 0xabfb5742, 0xa56959e3, 0x70085c34);
            WR1_PROG(REG_1CH, 0x00400000);
            WR1_PROG(REG_1D0H, 0x00000000);
            
            if(CHCK_STS(REG_1CH, 22, 1)) {
                WR1_PROG(REG_00H, 0x00000113);
                WAIT_STS(REG_00H, 25, 0);
                WR1_PROG(REG_1CH, 0x00001800);
                
                SC327_function002(0xaed23403, 0x690ab5aa, 0x82ad14a1, 0x4ecc281b);
            }
            else {
                
                SC327_function002(0xe1b46353, 0x36480949, 0xc2ad2f12, 0x594ebe0f);
            }
            
            WR1_PROG(REG_1C0H, 0x00130000);
            
            SC327_function003(0x1e5e88a4, 0x4bd7f87b, 0xa740bd47, 0x1a502c9e);
            WR1_PROG(REG_1BCH, 0x00000040);
            WAIT_STS(REG_18H, 12, 0);
            
            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else {
            
            SC327_function001(0x1ea7cb04, 0x14aa9d99, 0xe4a1bd9d, 0x37dc99a7);
            
            WR1_PROG(REG_104H, 0x00000051);
            WR1_PROG(REG_A4H, 0x00000684);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, 0x00000000);
            
            WR1_PROG(REG_04H, 0x00000113);
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_A0H, &OutData_IV[0]);
            
            WR1_PROG(REG_1C0H, 0x00130000);
            
            SC327_function003(0x85f05049, 0x44a4b0fc, 0x1764cbba, 0xeb918882);
            WR1_PROG(REG_1BCH, 0x00000040);
            WAIT_STS(REG_18H, 12, 0);
            
            return FSP_SUCCESS;
        }
    }
    
}

