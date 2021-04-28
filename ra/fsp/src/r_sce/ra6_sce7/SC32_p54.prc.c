/////////////////////////////////////////////////////////////////////////
// <SC32#2 AES-256 Encryption with CBC Mode(hidden key)>               //
// Procedure number: 54                                                //
// File name      : SC32_p54L.prc                                      //
// State Diagram  : main(FSM1)                                         //
// Start State    : main03                                             //
// End State      : main03                                             //
// Input Data     : InData_KeyIndex[13]                                //
//                : InData_IV[4]                                       //
//                : InData_Text[MAX_CNT]                               //
// Output Data    : OutData_Text[MAX_CNT]                              //
//                : (MAX_CNT is Multiples of four.)                    //
//                  OutData_IV[4]                                      //
// Return Value   : Pass, Fail, HRK_Invalid_Index or Resource_Conflict //
//---------------------------------------------------------------------//
// total cycle    : polling + write access + read access               //
// polling        : 230 + (MAX_CNT/4-1)*11 cycle                       //
// polling access :  25 + (MAX_CNT/4-1)*2  times                       //
// write access   :  91 + (MAX_CNT-4) times                            //
// read  access   :   8 + (MAX_CNT-4) times                            //
/////////////////////////////////////////////////////////////////////////

#include "SCE_ProcCommon.h"
#include "hw_sce_aes_private.h"

fsp_err_t HW_SCE_AES_256CbcEncryptUsingEncryptedKey(const uint32_t *InData_KeyIndex,
                                                    const uint32_t *InData_IV,
                                                    const uint32_t num_words,
                                                    const uint32_t *InData_Text,
                                                          uint32_t *OutData_Text,
                                                          uint32_t *OutData_IV)
{
    uint32_t iLoop, MAX_CNT = num_words;

    if(RD1_MASK(REG_1BCH, 0x0000001f) != 0x0000000) {
        // Busy now then retry later;
        // Because  1_xxxx other processing box is in duty.
        //          x_1xxx resource D is in duty,then retry after you released D.
        //          x_x1xx resource C is in duty,then retry after you released C.
        //          x_xx1x resource B is in duty,then retry after you released B.
        //          x_xxx1 resource A is in duty,then retry after you released A.
        // A,B,C,D: see Primitive Level Procedures datasheet
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }
    
    WR1_PROG(REG_84H, 0x00005401);
    WR1_PROG(REG_108H, 0x00000000);
    
    WR1_PROG(REG_1C0H, 0x00130013);
    
    WR1_PROG(REG_1CH, 0x00000081);
    WR1_PROG(REG_A4H, 0x200c3b0c);
    WAIT_STS(REG_00H, 21, 1);
    WR1_ADDR(REG_A0H, &InData_KeyIndex[0]);
    
    WR1_PROG(REG_A4H, 0x000c0b0c);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x615e8e97);
    
    SC32_function001(0xa09e9b38, 0x9b3cbe08, 0x8ad81b45, 0x4711aa19);
    WR1_PROG(REG_1CH, 0x00000084);
    WR1_PROG(REG_A4H, 0x02f8073d);
    WAIT_STS(REG_00H, 21, 1);
    WR4_ADDR(REG_A0H, &InData_KeyIndex[1]);
    
    SC32_function001(0x4c22cc47, 0x2e1c374a, 0xb2cd54a2, 0x1e9ee356);
    WR1_PROG(REG_1CH, 0x00000084);
    WR1_PROG(REG_A4H, 0x00f9073d);
    WAIT_STS(REG_00H, 21, 1);
    WR4_ADDR(REG_A0H, &InData_KeyIndex[5]);
    
    WR1_PROG(REG_1CH, 0x00000084);
    WR1_PROG(REG_A4H, 0x000007bd);
    WAIT_STS(REG_00H, 21, 1);
    WR4_ADDR(REG_A0H, &InData_KeyIndex[9]);
    
    WR1_PROG(REG_A4H, 0x00900c45);
    WR1_PROG(REG_00H, 0x00001113);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    
    SC32_function001(0xbb9c1f5c, 0xab66357d, 0xd79cdf73, 0x4e876c7d);
    WR1_PROG(REG_1CH, 0x00400000);
    WR1_PROG(REG_1D0H, 0x00000000);
    
    if(CHCK_STS(REG_1CH, 22, 1)) {
        
        WR1_PROG(REG_1C0H, 0x00130000);
        
        SC32_function003(0x837d3787, 0x9f9af818, 0x352b25d5, 0x45f1af87);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_18H, 12, 0);
        return FSP_ERR_CRYPTO_SCE_HRK_INVALID_INDEX;
    }
    else {
        
        WR1_PROG(REG_1CH, 0x00000084);
        WR1_PROG(REG_A4H, 0x00040805);
        WAIT_STS(REG_00H, 21, 1);
        WR4_ADDR(REG_A0H, &InData_IV[0]);
        
        SC32_function001(0xbcbee745, 0xe315314a, 0x664e8e18, 0xeac3cb2a);
        //Host DMA Setting(if use DMA)
        //Transfer DATA is 128bits(4words) for each request
        //DMA request count is (MAX_CNT/4) times
        //DMA request signal are WRRDYB_0,RDRDYB_0
        //Input,Output Register is REG_A0H
        
        WR1_PROG(REG_B0H, 0x700000C0);
        WR1_PROG(REG_A4H, 0x00008e96); //Enable request signals(WRRDYB_0,RDRDYB_0)
        
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
        
        SC32_function001(0xb7617305, 0xad78ba30, 0xf85ea7fa, 0x92bf0363);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);
        
        if(CHCK_STS(REG_1CH, 22, 1)) {
            
            WR1_PROG(REG_1C0H, 0x00130000);
            
            SC32_function003(0x72281dbf, 0x94f16d17, 0x3a2b7ca2, 0xe90f1bb1);
            WR1_PROG(REG_1BCH, 0x00000040);
            WAIT_STS(REG_18H, 12, 0);
            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else {
            
            SC32_function001(0xef844e15, 0x8424bbb9, 0x505c14bd, 0xe22b86b9);
            
            WR1_PROG(REG_104H, 0x00000051);
            WR1_PROG(REG_A4H, 0x00000c84);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, 0x00000000);
            
            WR1_PROG(REG_04H, 0x00000113);
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_A0H, &OutData_IV[0]);
            
            WR1_PROG(REG_1C0H, 0x00130000);
            
            SC32_function003(0x542b110b, 0x450c0dc9, 0xccf370a7, 0x310890e0);
            WR1_PROG(REG_1BCH, 0x00000040);
            WAIT_STS(REG_18H, 12, 0);
            
            return FSP_SUCCESS;
        }
    }
}

