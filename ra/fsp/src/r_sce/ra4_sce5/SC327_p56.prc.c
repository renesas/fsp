/////////////////////////////////////////////////////////////////////////
// <SC32#7 AES-256 Encryption/Decryption with CTR Mode(hidden key)>    //
// Procedure number: 56                                                //
// File name      : SC327_p56L.prc                                     //
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

fsp_err_t HW_SCE_AES_256CtrEncryptUsingEncryptedKey (const uint32_t * InData_KeyIndex,
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
    
    WR1_PROG(REG_84H, 0x00005601);
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
    
    SC327_function001(0xf4dd0091, 0xde6e825b, 0x11519c66, 0x1731b5bd);
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
    
    SC327_function001(0xd6bec71a, 0xda103f6c, 0x1fc0144a, 0x2e5670a0);
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
    
    SC327_function001(0x383b8b89, 0x99c0f9c3, 0xeb968170, 0x5ada0489);
    WR1_PROG(REG_1CH, 0x00400000);
    WR1_PROG(REG_1D0H, 0x00000000);
    
    if(CHCK_STS(REG_1CH, 22, 1)) {
        
        WR1_PROG(REG_1C0H, 0x00130000);
        
        SC327_function003(0x7c596d6a, 0x65686894, 0x10cbc85d, 0x1a306466);
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
        
        SC327_function001(0x32336f9e, 0x3ebb8088, 0xb5f5b800, 0x7cb919c2);
        //Host DMA Setting(if use DMA)
        //Transfer DATA is 128bits(4words) for each request
        //DMA request count is (MAX_CNT/4) times
        //DMA request signal are WRRDYB_0,RDRDYB_0
        //Input,Output Register is REG_A0H
        
        WR1_PROG(REG_B0H, 0x700000C0);
        WR1_PROG(REG_A4H, 0x000086be); //Enable request signals(WRRDYB_0,RDRDYB_0)
        
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
        
        SC327_function001(0xdc44d6b8, 0x94d27396, 0x4a20c168, 0xb909203b);
        WR1_PROG(REG_1CH, 0x00400000);
        WR1_PROG(REG_1D0H, 0x00000000);
        
        if(CHCK_STS(REG_1CH, 22, 1)) {
            
            WR1_PROG(REG_1CH, 0x002d0000);
            
            SC327_function001(0xc2d2bde3, 0x81cd5cd0, 0xe7c0f607, 0x69428381);
            WR1_PROG(REG_1CH, 0x00400000);
            WR1_PROG(REG_1D0H, 0x00000000);
            
            if(CHCK_STS(REG_1CH, 22, 1)) {
                WR1_PROG(REG_00H, 0x00000113);
                WAIT_STS(REG_00H, 25, 0);
                WR1_PROG(REG_1CH, 0x00001800);
                
                SC327_function002(0xc7813ec4, 0x022e7f05, 0x3a36ce29, 0x64013d21);
            }
            else {
                
                SC327_function002(0x2c918d3e, 0x6082a051, 0x9f9ebb3d, 0x41206453);
            }
            
            WR1_PROG(REG_1C0H, 0x00130000);
            
            SC327_function003(0x936e6550, 0xc0e4a36b, 0x7f9dd721, 0x422349e9);
            WR1_PROG(REG_1BCH, 0x00000040);
            WAIT_STS(REG_18H, 12, 0);
            
            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else {
            
            SC327_function001(0x1bf0cfff, 0xde1e48a3, 0x1dc9dc6c, 0x242d67ff);
            
            WR1_PROG(REG_104H, 0x00000051);
            WR1_PROG(REG_A4H, 0x00000684);
            WAIT_STS(REG_104H, 31, 1);
            WR1_PROG(REG_100H, 0x00000000);
            
            WR1_PROG(REG_04H, 0x00000113);
            WAIT_STS(REG_04H, 30, 1);
            RD4_ADDR(REG_A0H, &OutData_IV[0]);
            
            WR1_PROG(REG_1C0H, 0x00130000);
            
            SC327_function003(0x01710cc8, 0x83b68fd6, 0x29a82594, 0xb36cb8a7);
            WR1_PROG(REG_1BCH, 0x00000040);
            WAIT_STS(REG_18H, 12, 0);
            
            return FSP_SUCCESS;
        }
    }
    
}

