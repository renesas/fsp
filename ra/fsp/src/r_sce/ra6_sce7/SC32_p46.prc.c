/////////////////////////////////////////////////////////////////////////
// <SC32#2 AES-128 Encryption/Decryption with CTR Mode(hidden key)>    //
// Procedure number: 46                                                //
// File name      : SC32_p46L.prc                                      //
// State Diagram  : main(FSM1)                                         //
// Start State    : main03                                             //
// End State      : main03                                             //
// Input Data     : InData_KeyIndex[9]                                 //
//                : InData_IV[4]                                       //
//                : InData_Text[MAX_CNT]                               //
// Output Data    : OutData_Text[MAX_CNT]                              //
//                : (MAX_CNT is Multiples of four.)                    //
//                  OutData_IV[4]                                      //
// Return Value   : Pass, Fail, HRK_Invalid_Index or Resource_Conflict //
//---------------------------------------------------------------------//
// total cycle    : polling + write access + read access               //
// polling        : 189 + (MAX_CNT/4-1)*11 cycle                       //
// polling access :  22 + (MAX_CNT/4-1)*2  times                       //
// write access   :  80 + (MAX_CNT-4) times                            //
// read  access   :  11 + (MAX_CNT-4) times                            //
/////////////////////////////////////////////////////////////////////////

#include "SCE_ProcCommon.h"
#include "hw_sce_aes_private.h"

fsp_err_t HW_SCE_AES_128CtrEncryptUsingEncryptedKey(const uint32_t *InData_KeyIndex,
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
    
    WR1_PROG(REG_84H, 0x00004601);
    WR1_PROG(REG_108H, 0x00000000);
    
    WR1_PROG(REG_1C0H, 0x00130013);
    
    WR1_PROG(REG_1CH, 0x00000081);
    WR1_PROG(REG_A4H, 0x200c3b0c);
    WAIT_STS(REG_00H, 21, 1);
    WR1_ADDR(REG_A0H, &InData_KeyIndex[0]);
    
    WR1_PROG(REG_A4H, 0x000c0b0c);
    WAIT_STS(REG_104H, 31, 1);
    WR1_PROG(REG_100H, 0x4e2279db);
    
    SC32_function001(0xacfe69bd, 0x97ebb3ce, 0x65370b2b, 0x0c386aa7);
    WR1_PROG(REG_1CH, 0x00000084);
    WR1_PROG(REG_A4H, 0x02f8073d);
    WAIT_STS(REG_00H, 21, 1);
    WR4_ADDR(REG_A0H, &InData_KeyIndex[1]);
    
    WR1_PROG(REG_1CH, 0x00000084);
    WR1_PROG(REG_A4H, 0x000007bd);
    WAIT_STS(REG_00H, 21, 1);
    WR4_ADDR(REG_A0H, &InData_KeyIndex[5]);
    
    WR1_PROG(REG_A4H, 0x00900c45);
    WR1_PROG(REG_00H, 0x00001113);
    WAIT_STS(REG_00H, 25, 0);
    WR1_PROG(REG_1CH, 0x00001800);
    
    SC32_function001(0xd7c71cfb, 0x24ec9fdd, 0xb0940c02, 0xef5d27b3);
    WR1_PROG(REG_1CH, 0x00400000);
    WR1_PROG(REG_1D0H, 0x00000000);
    
    if(CHCK_STS(REG_1CH, 22, 1)) {
        
        WR1_PROG(REG_1C0H, 0x00130000);
        
        SC32_function003(0x22c51204, 0xbc4920c6, 0x55c4a7cb, 0x3e9c13d0);
        WR1_PROG(REG_1BCH, 0x00000040);
        WAIT_STS(REG_18H, 12, 0);
        return FSP_ERR_CRYPTO_SCE_HRK_INVALID_INDEX;
    }
    else {
        
        WR1_PROG(REG_1CH, 0x00000084);
        WR1_PROG(REG_A4H, 0x00040805);
        WAIT_STS(REG_00H, 21, 1);
        WR4_ADDR(REG_A0H, &InData_IV[0]);
        
        SC32_function001(0x22c0d4a0, 0x3b4515b0, 0xed21158e, 0x0413484c);
        //Host DMA Setting(if use DMA)
        //Transfer DATA is 128bits(4words) for each request
        //DMA request count is (MAX_CNT/4) times
        //DMA request signal are WRRDYB_0,RDRDYB_0
        //Input,Output Register is REG_A0H
        
        WR1_PROG(REG_B0H, 0x300000C0);
        WR1_PROG(REG_A4H, 0x000087b6); //Enable request signals(WRRDYB_0,RDRDYB_0)
        
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
        
        SC32_function001(0x78527618, 0x8fdc0c16, 0x430dcc1d, 0xa2bf29bf);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);
        
        if(CHCK_STS(REG_1CH, 22, 1)) {
            
            WR1_PROG(REG_1C0H, 0x00130000);
            
            SC32_function003(0xd774dbab, 0x05df5a89, 0x3c00c77f, 0x2d2c6139);
            WR1_PROG(REG_1BCH, 0x00000040);
            WAIT_STS(REG_18H, 12, 0);
            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else {
            
            SC32_function001(0xac073653, 0xece861d8, 0x2e50bb50, 0xafeb1fd3);
            
            WR1_PROG(REG_104H, 0x00000051);
            WR1_PROG(REG_A4H, 0x00000c84);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, 0x00000000);
            
            WR1_PROG(REG_04H, 0x00000113);
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_A0H, &OutData_IV[0]);
            
            WR1_PROG(REG_1C0H, 0x00130000);
            
            SC32_function003(0x6d539fc4, 0x98f67287, 0xbfb604b1, 0x60e5858b);
            WR1_PROG(REG_1BCH, 0x00000040);
            WAIT_STS(REG_18H, 12, 0);
            
            return FSP_SUCCESS;
        }
    }
}

