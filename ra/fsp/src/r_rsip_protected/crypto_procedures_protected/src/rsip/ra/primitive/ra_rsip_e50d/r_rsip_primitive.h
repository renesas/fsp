/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_RSIP_PRIMITIVE_H
#define R_RSIP_PRIMITIVE_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <stdint.h>
#include "r_rsip_err.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define RSIP_PRV_WORD_SIZE_S_RAM     (32U)
#define RSIP_PRV_WORD_SIZE_S_HEAP    (940U)

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

extern uint32_t         S_RAM[RSIP_PRV_WORD_SIZE_S_RAM];
extern uint32_t         S_HEAP[RSIP_PRV_WORD_SIZE_S_HEAP];
extern uint32_t const * S_INST2;

extern uint32_t const DomainParam_NIST_P192[];
extern uint32_t const DomainParam_NIST_P224[];
extern uint32_t const DomainParam_NIST_P256[];
extern uint32_t const DomainParam_NIST_P384[];
extern uint32_t const DomainParam_NIST_P521[];
extern uint32_t const DomainParam_Ed25519[];
extern uint32_t const DomainParam_Brainpool_256r1[];
extern uint32_t const DomainParam_Brainpool_384r1[];
extern uint32_t const DomainParam_Brainpool_512r1[];
extern uint32_t const DomainParam_Koblitz_secp256k1[];
extern uint32_t       INST_DATA_SIZE;

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/

void r_rsip_func008(void);
void r_rsip_func016(uint32_t ARG1);
void r_rsip_func017(uint32_t ARG1);
void r_rsip_func027(const uint32_t ARG1[]);
void r_rsip_func028(const uint32_t ARG1[]);
void r_rsip_func030(void);
void r_rsip_func031(const uint32_t ARG1[]);
void r_rsip_func040(void);
void r_rsip_func043(void);
void r_rsip_func044(void);
void r_rsip_func048(const uint32_t ARG1[]);
void r_rsip_func049(const uint32_t ARG1[]);
void r_rsip_func052(void);
void r_rsip_func053(void);
void r_rsip_func054(void);
void r_rsip_func055(void);
void r_rsip_func057(const uint32_t ARG1[], const uint32_t ARG2[], uint32_t ARG3[]);
void r_rsip_func058(const uint32_t ARG1[], uint32_t ARG2);
void r_rsip_func059(void);
void r_rsip_func061(const uint32_t ARG1, const uint32_t ARG2[]);
void r_rsip_func062(const uint32_t ARG1, uint32_t ARG2[]);
void r_rsip_func063(const uint32_t ARG1, const uint32_t ARG2[]);
void r_rsip_func065(const uint32_t ARG1, uint32_t ARG2[]);
void r_rsip_func066(void);
void r_rsip_func068(void);
void r_rsip_func070(const uint32_t ARG1[]);
void r_rsip_func071(const uint32_t ARG1[]);
void r_rsip_func073(const uint32_t ARG1[]);
void r_rsip_func074(void);
void r_rsip_func075(void);
void r_rsip_func076(void);
void r_rsip_func077(void);
void r_rsip_func078(const uint32_t ARG1[]);
void r_rsip_func079(const uint32_t ARG1[]);
void r_rsip_func081(void);
void r_rsip_func082(void);
void r_rsip_func083(const uint32_t ARG1[]);
void r_rsip_func086(const uint32_t ARG1[]);
void r_rsip_func087(const uint32_t ARG1[]);
void r_rsip_func088(void);
void r_rsip_func089(void);
void r_rsip_func090(void);
void r_rsip_func091(void);
void r_rsip_func092(void);
void r_rsip_func100(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);
void r_rsip_func101(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);
void r_rsip_func102(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);
void r_rsip_func103(void);
void r_rsip_func113(void);
void r_rsip_func202(void);
void r_rsip_func214(void);
void r_rsip_func215(void);
void r_rsip_func216(void);
void r_rsip_func302(void);
void r_rsip_func303(void);
void r_rsip_func304(void);
void r_rsip_func305(void);
void r_rsip_func310(void);
void r_rsip_func311(void);
void r_rsip_func312(void);
void r_rsip_func313(void);
void r_rsip_func314(void);
void r_rsip_func315(void);
void r_rsip_func316(void);
void r_rsip_func317(void);
void r_rsip_func318(void);
void r_rsip_func319(void);
void r_rsip_func320(void);
void r_rsip_func321(void);
void r_rsip_func322(void);
void r_rsip_func323(void);
void r_rsip_func324(void);
void r_rsip_func401(const uint32_t ARG1[]);
void r_rsip_func402(void);
void r_rsip_func403(void);
void r_rsip_func404(void);
void r_rsip_func405(void);
void r_rsip_func406(const uint32_t ARG1[]);
void r_rsip_func407(const uint32_t ARG1[]);
void r_rsip_func408(void);
void r_rsip_func501(uint32_t ARG1[], uint32_t ARG2);

rsip_ret_t r_rsip_p47i(const uint32_t InData_Cmd[],
                       const uint32_t InData_KeyIndex[],
                       const uint32_t InData_IVType[],
                       const uint32_t InData_IV[]);
void       r_rsip_p47u(uint32_t const InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p47f(void);
rsip_ret_t r_rsip_p89i(const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
void       r_rsip_p89u(const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p89f(void);
rsip_ret_t r_rsip_p50i(const uint32_t InData_Cmd[],
                       const uint32_t InData_KeyIndex[],
                       const uint32_t InData_IVType[],
                       const uint32_t InData_IV[]);
void       r_rsip_p50u(const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p50f(void);

void       r_rsip_p00(void);
rsip_ret_t r_rsip_p11(const uint32_t InData_KeyIndex[],
                      const uint32_t InData_MsgDgst[],
                      const uint32_t InData_DomainParam[],
                      uint32_t       OutData_Signature[]);
rsip_ret_t r_rsip_p12(const uint32_t InData_KeyIndex[],
                      const uint32_t InData_MsgDgst[],
                      const uint32_t InData_Signature[],
                      const uint32_t InData_DomainParam[]);
rsip_ret_t r_rsip_p13(const uint32_t InData_DomainParam[],
                      uint32_t       OutData_PubKeyIndex[],
                      uint32_t       OutData_PrivKeyIndex[]);
rsip_ret_t r_rsip_p1a(const uint32_t InData_DomainParam[],
                      uint32_t       OutData_PubKeyIndex[],
                      uint32_t       OutData_PrivKeyIndex[]);
rsip_ret_t r_rsip_p18(const uint32_t InData_PrivKeyIndex[],
                      const uint32_t InData_PubKeyIndex[],
                      const uint32_t InData_Msg[],
                      const uint32_t InData_MsgLen[],
                      const uint32_t InData_DomainParam[],
                      uint32_t       OutData_Signature[],
                      uint64_t       MAX_CNT);
rsip_ret_t r_rsip_p19(const uint32_t InData_KeyIndex[],
                      const uint32_t InData_Msg[],
                      const uint32_t InData_MsgLen[],
                      const uint32_t InData_Signature[],
                      const uint32_t InData_DomainParam[],
                      uint64_t       MAX_CNT);
void       r_rsip_p29a(const uint32_t InData_DataA[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p29f(const uint32_t InData_Text[],
                       const uint32_t InData_DataALen[],
                       const uint32_t InData_TextLen[],
                       uint32_t       OutData_Text[],
                       uint32_t       OutData_DataT[]);
rsip_ret_t r_rsip_p29i(const uint32_t InData_KeyIndex[], const uint32_t InData_IVType[], const uint32_t InData_IV[]);
void       r_rsip_p29t(void);
void       r_rsip_p29u(const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
void       r_rsip_p32a(const uint32_t InData_DataA[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p32f(const uint32_t InData_Text[],
                       const uint32_t InData_DataT[],
                       const uint32_t InData_DataALen[],
                       const uint32_t InData_TextLen[],
                       const uint32_t InData_DataTLen[],
                       uint32_t       OutData_Text[]);
rsip_ret_t r_rsip_p32i(const uint32_t InData_KeyIndex[], const uint32_t InData_IVType[], const uint32_t InData_IV[]);
void       r_rsip_p32t(void);
void       r_rsip_p32u(const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
void       r_rsip_p83a(const uint32_t InData_DataA[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p83f(const uint32_t InData_Text[],
                       const uint32_t InData_TextLen[],
                       const uint32_t InData_DataALen[],
                       uint32_t       OutData_Text[],
                       uint32_t       OutData_DataT[]);
rsip_ret_t r_rsip_p83i(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
void       r_rsip_p83t(void);
void       r_rsip_p83u(const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
void       r_rsip_p85a(const uint32_t InData_DataA[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p85f(const uint32_t InData_Text[],
                       const uint32_t InData_DataT[],
                       const uint32_t InData_DataALen[],
                       const uint32_t InData_TextLen[],
                       const uint32_t InData_DataTLen[],
                       uint32_t       OutData_Text[]);
rsip_ret_t r_rsip_p85i(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
void       r_rsip_p85t(void);
void       r_rsip_p85u(const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
void       r_rsip_p34a(const uint32_t InData_DataA[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p34f(const uint32_t InData_Text[],
                       const uint32_t InData_TextLen[],
                       const uint32_t InData_DataALen[],
                       uint32_t       OutData_Text[],
                       uint32_t       OutData_DataT[]);
rsip_ret_t r_rsip_p34i(const uint32_t InData_KeyIndex[], const uint32_t InData_IVType[], const uint32_t InData_IV[]);
void       r_rsip_p34t(void);
void       r_rsip_p34u(const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
void       r_rsip_p36a(const uint32_t InData_DataA[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p36f(const uint32_t InData_Text[],
                       const uint32_t InData_TextLen[],
                       const uint32_t InData_DataALen[],
                       const uint32_t InData_DataT[],
                       const uint32_t InData_DataTLen[],
                       uint32_t       OutData_Text[]);
rsip_ret_t r_rsip_p36i(const uint32_t InData_KeyIndex[], const uint32_t InData_IVType[], const uint32_t InData_IV[]);
void       r_rsip_p36t(void);
void       r_rsip_p36u(const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p40(const uint32_t InData_LC[]);
rsip_ret_t r_rsip_p41f(const uint32_t InData_Cmd[],
                       const uint32_t InData_Text[],
                       const uint32_t InData_DataT[],
                       const uint32_t InData_DataTLen[],
                       uint32_t       OutData_DataT[]);
rsip_ret_t r_rsip_p41i(const uint32_t InData_KeyIndex[]);
void       r_rsip_p41u(const uint32_t InData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p87f(const uint32_t InData_Cmd[],
                       const uint32_t InData_Text[],
                       const uint32_t InData_DataT[],
                       const uint32_t InData_DataTLen[],
                       uint32_t       OutData_DataT[]);
rsip_ret_t r_rsip_p87i(const uint32_t InData_KeyIndex[]);
void       r_rsip_p87u(const uint32_t InData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p44f(const uint32_t InData_Cmd[],
                       const uint32_t InData_Text[],
                       const uint32_t InData_DataT[],
                       const uint32_t InData_DataTLen[],
                       uint32_t       OutData_DataT[]);
rsip_ret_t r_rsip_p44i(const uint32_t InData_KeyIndex[]);
void       r_rsip_p44u(const uint32_t InData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p20(uint32_t OutData_Text[]);
rsip_ret_t r_rsip_p6f(const uint32_t InData_LC[],
                      const uint32_t InData_Cmd[],
                      const uint32_t InData_IV[],
                      const uint32_t InData_InstData[],
                      uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_p73i(const uint32_t InData_HashType[], const uint32_t InData_MsgLen[]);
rsip_ret_t r_rsip_p73r(const uint32_t InData_HashType[], const uint32_t InData_State[]);
rsip_ret_t r_rsip_p73u(const uint32_t InData_Msg[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p73s(uint32_t OutData_State[]);
rsip_ret_t r_rsip_p73f(const uint32_t InData_Msg[], uint32_t MAX_CNT, uint32_t OutData_MsgDigest[]);
rsip_ret_t r_rsip_p81(void);
rsip_ret_t r_rsip_p82(void);
rsip_ret_t r_rsip_p95f(const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t OutData_MAC[]);
rsip_ret_t r_rsip_p95i(const uint32_t InData_KeyType[],
                       const uint32_t InData_DataType[],
                       const uint32_t InData_Cmd[],
                       const uint32_t InData_TextLen[],
                       const uint32_t InData_KeyIndex[],
                       const uint32_t InData_IV[],
                       const uint32_t InData_Header[],
                       const uint32_t InData_SeqNum[],
                       uint32_t       Header_Len);
void       r_rsip_p95u(const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p98f(const uint32_t InData_Text[], const uint32_t InData_MAC[], uint32_t OutData_Text[]);
rsip_ret_t r_rsip_p98i(const uint32_t InData_KeyType[],
                       const uint32_t InData_DataType[],
                       const uint32_t InData_Cmd[],
                       const uint32_t InData_TextLen[],
                       const uint32_t InData_MACLength[],
                       const uint32_t InData_KeyIndex[],
                       const uint32_t InData_IV[],
                       const uint32_t InData_Header[],
                       const uint32_t InData_SeqNum[],
                       uint32_t       Header_Len);
void       r_rsip_p98u(const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_pa7f(const uint32_t InData_Text[],
                       const uint32_t InData_TextLen[],
                       uint32_t       OutData_Text[],
                       uint32_t       OutData_MAC[]);
rsip_ret_t r_rsip_pa7i(const uint32_t InData_KeyIndex[],
                       const uint32_t InData_IV[],
                       const uint32_t InData_Header[],
                       uint32_t       Header_Len);
void       r_rsip_pa7u(const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_pb0f(const uint32_t InData_Text[],
                       const uint32_t InData_TextLen[],
                       const uint32_t InData_MAC[],
                       const uint32_t InData_MACLength[],
                       uint32_t       OutData_Text[]);
rsip_ret_t r_rsip_pb0i(const uint32_t InData_KeyIndex[],
                       const uint32_t InData_IV[],
                       const uint32_t InData_Header[],
                       uint32_t       Header_Len);
void       r_rsip_pb0u(const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_pa1f(const uint32_t InData_Text[],
                       const uint32_t InData_TextLen[],
                       uint32_t       OutData_Text[],
                       uint32_t       OutData_MAC[]);
rsip_ret_t r_rsip_pa1i(const uint32_t InData_KeyType[],
                       const uint32_t InData_KeyIndex[],
                       const uint32_t InData_IV[],
                       const uint32_t InData_Header[],
                       uint32_t       Header_Len);
void       r_rsip_pa1u(const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_pa4f(const uint32_t InData_Text[],
                       const uint32_t InData_TextLen[],
                       const uint32_t InData_MAC[],
                       const uint32_t InData_MACLength[],
                       uint32_t       OutData_Text[]);
rsip_ret_t r_rsip_pa4i(const uint32_t InData_KeyType[],
                       const uint32_t InData_KeyIndex[],
                       const uint32_t InData_IV[],
                       const uint32_t InData_Header[],
                       uint32_t       Header_Len);
void       r_rsip_pa4u(const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_pb3f(const uint32_t InData_TextBitLen[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
rsip_ret_t r_rsip_pb3i(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
void       r_rsip_pb3u(const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_pb6f(const uint32_t InData_TextBitLen[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
rsip_ret_t r_rsip_pb6i(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
void       r_rsip_pb6u(const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_pb9f(const uint32_t InData_TextBitLen[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
rsip_ret_t r_rsip_pb9i(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
void       r_rsip_pb9u(const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_pc2f(const uint32_t InData_TextBitLen[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
rsip_ret_t r_rsip_pc2i(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
void       r_rsip_pc2u(const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p21(const uint32_t InData_HV[],
                      const uint32_t InData_IV[],
                      const uint32_t InData_Text[],
                      uint32_t       OutData_DataT[],
                      uint32_t       MAX_CNT);
rsip_ret_t r_rsip_p07(uint32_t OutData_KeyIndex[]);
rsip_ret_t r_rsip_p15(uint32_t OutData_KeyIndex[]);
rsip_ret_t r_rsip_p08(uint32_t OutData_KeyIndex[]);
rsip_ret_t r_rsip_p16(uint32_t OutData_KeyIndex[]);
rsip_ret_t r_rsip_p17(uint32_t OutData_KeyIndex[]);
rsip_ret_t r_rsip_p0a(uint32_t OutData_KeyIndex[]);
rsip_ret_t r_rsip_p0b(uint32_t OutData_KeyIndex[]);
rsip_ret_t r_rsip_p3c(uint32_t OutData_KeyIndex[]);
rsip_ret_t r_rsip_p3d(uint32_t OutData_KeyIndex[]);
rsip_ret_t r_rsip_p56(const uint32_t InData_KeyIndex[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
rsip_ret_t r_rsip_p57(const uint32_t InData_KeyIndex[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
rsip_ret_t r_rsip_p79(const uint32_t InData_KeyIndex[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
rsip_ret_t r_rsip_p7a(const uint32_t InData_KeyIndex[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
rsip_ret_t r_rsip_p7b(const uint32_t InData_KeyIndex[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
rsip_ret_t r_rsip_p7c(const uint32_t InData_KeyIndex[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
rsip_ret_t r_rsip_pf0(const uint32_t InData_CurveType[],
                      const uint32_t InData_Cmd[],
                      const uint32_t InData_KeyIndex[],
                      const uint32_t InData_MsgDgst[],
                      const uint32_t InData_DomainParam[],
                      uint32_t       OutData_Signature[]);
rsip_ret_t r_rsip_pf1(const uint32_t InData_CurveType[],
                      const uint32_t InData_Cmd[],
                      const uint32_t InData_KeyIndex[],
                      const uint32_t InData_MsgDgst[],
                      const uint32_t InData_Signature[],
                      const uint32_t InData_DomainParam[]);
rsip_ret_t r_rsip_pf5(const uint32_t InData_CurveType[],
                      const uint32_t InData_KeyIndex[],
                      const uint32_t InData_MsgDgst[],
                      const uint32_t InData_DomainParam[],
                      uint32_t       OutData_Signature[]);
rsip_ret_t r_rsip_pf6(const uint32_t InData_CurveType[],
                      const uint32_t InData_KeyIndex[],
                      const uint32_t InData_MsgDgst[],
                      const uint32_t InData_Signature[],
                      const uint32_t InData_DomainParam[]);
rsip_ret_t r_rsip_p7d(const uint32_t InData_KeyIndex[],
                      const uint32_t InData_MsgDgst[],
                      const uint32_t InData_DomainParam[],
                      uint32_t       OutData_Signature[]);
rsip_ret_t r_rsip_p7e(const uint32_t InData_KeyIndex[],
                      const uint32_t InData_MsgDgst[],
                      const uint32_t InData_Signature[],
                      const uint32_t InData_DomainParam[]);
rsip_ret_t r_rsip_pf4(const uint32_t InData_CurveType[],
                      const uint32_t InData_Cmd[],
                      const uint32_t InData_DomainParam[],
                      uint32_t       OutData_PubKeyIndex[],
                      uint32_t       OutData_PrivKeyIndex[]);
rsip_ret_t r_rsip_pf9(const uint32_t InData_CurveType[],
                      const uint32_t InData_DomainParam[],
                      uint32_t       OutData_PubKeyIndex[],
                      uint32_t       OutData_PrivKeyIndex[]);
rsip_ret_t r_rsip_p7f(const uint32_t InData_DomainParam[],
                      uint32_t       OutData_PubKeyIndex[],
                      uint32_t       OutData_PrivKeyIndex[]);
rsip_ret_t r_rsip_p75(const uint32_t InData_KeyIndex[],
                      const uint32_t InData_Cmd[],
                      const uint32_t InData_Msg[],
                      const uint32_t InData_MsgLen[],
                      const uint32_t InData_MAC[],
                      const uint32_t InData_length[],
                      const uint32_t InData_State[],
                      uint32_t       OutData_MAC[],
                      uint32_t       OutData_State[],
                      uint32_t       MAX_CNT);
rsip_ret_t r_rsip_p75i(const uint32_t InData_KeyIndex[],
                       const uint32_t InData_HashType[],
                       const uint32_t InData_MsgLen[],
                       uint32_t       KEY_INDEX_SIZE);
rsip_ret_t r_rsip_p75r(const uint32_t InData_KeyIndex[],
                       const uint32_t InData_HashType[],
                       const uint32_t InData_State[],
                       uint32_t       KEY_INDEX_SIZE);
rsip_ret_t r_rsip_p75u(const uint32_t InData_Msg[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p75s(uint32_t OutData_State[]);
rsip_ret_t r_rsip_p75f(const uint32_t InData_Cmd[],
                       const uint32_t InData_Msg[],
                       const uint32_t InData_MAC[],
                       const uint32_t InData_length[],
                       uint32_t       MAX_CNT,
                       uint32_t       OutData_MAC[]);
rsip_ret_t r_rsip_p31(const uint32_t InData_HashType[],
                      const uint32_t InData_Msg[],
                      const uint32_t InData_MsgLen[],
                      uint32_t       OutData_MsgDigest[],
                      uint32_t       MAX_CNT);
rsip_ret_t r_rsip_p2b(const uint32_t MAX_CNT, uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);
rsip_ret_t r_rsip_p2c(const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_DOTFSEED[]);
rsip_ret_t r_rsip_p2d(const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_DOTFSEED[]);
rsip_ret_t r_rsip_p2e(const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_DOTFSEED[]);
rsip_ret_t r_rsip_p3a(const uint32_t MAX_CNT, uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);
rsip_ret_t r_rsip_p3b(const uint32_t MAX_CNT, uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);

rsip_ret_t r_rsip_p8f(const uint32_t InData_Cmd[],
                      const uint32_t InData_KeyIndex[],
                      const uint32_t InData_WrappedKeyType[],
                      const uint32_t InData_WrappedKeyIndex[],
                      uint32_t       OutData_Text[],
                      uint32_t       KEY_INDEX_SIZE,
                      uint32_t       WRAPPED_KEY_SIZE);
rsip_ret_t r_rsip_p90(const uint32_t InData_KeyType[],
                      const uint32_t InData_Cmd[],
                      const uint32_t InData_KeyIndex[],
                      const uint32_t InData_WrappedKeyType[],
                      const uint32_t InData_Text[],
                      uint32_t       OutData_KeyIndex[],
                      uint32_t       WRAPPED_KEY_SIZE,
                      uint32_t       KEY_INDEX_SIZE);

rsip_ret_t r_rsip_pe1(const uint32_t InData_Sel_KeyType[],
                      const uint32_t InData_Certificate[],
                      const uint32_t InData_CertificateLength[],
                      const uint32_t InData_CertificatePubKey[],
                      const uint32_t InData_EncCertificateInfo[],
                      uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_pe2(const uint32_t InData_PubKeyType[],
                      const uint32_t InData_PubKey[],
                      const uint32_t InData_KeyIndex[],
                      const uint32_t InData_DomainParam[],
                      uint32_t       OutData_EncSecret[]);
rsip_ret_t r_rsip_p4e(const uint32_t InData_PubKeyType[],
                      const uint32_t InData_PubKey[],
                      const uint32_t InData_KeyIndex[],
                      const uint32_t InData_DomainParam[],
                      uint32_t       OutData_EncSecret[]);
rsip_ret_t r_rsip_p4f(const uint32_t InData_PubKeyType[],
                      const uint32_t InData_PubKey[],
                      const uint32_t InData_KeyIndex[],
                      const uint32_t InData_DomainParam[],
                      uint32_t       OutData_EncSecret[]);
rsip_ret_t r_rsip_pe3(const uint32_t InData_HashType[], const uint32_t InData_EncSecret[], uint32_t OutData_EncMsg[]);
rsip_ret_t r_rsip_pe4(const uint32_t InData_HashType[], const uint32_t InData_EncSecret[], uint32_t OutData_KeyIndex[]);
rsip_ret_t r_rsip_pe5e(const uint32_t InData_EncMsg[], uint32_t MAX_CNT2);
rsip_ret_t r_rsip_pe5f(const uint32_t InData_Msg[],
                       const uint32_t InData_EncMsg[],
                       uint32_t       OutData_KDFInfo[],
                       uint32_t       MAX_CNT,
                       uint32_t       MAX_CNT2);
rsip_ret_t r_rsip_pe5i(const uint32_t InData_KeyType[],
                       const uint32_t InData_KeyIndex[],
                       const uint32_t InData_HashType[],
                       const uint32_t InData_MsgLen[]);
rsip_ret_t r_rsip_pe5r(const uint32_t InData_KeyType[],
                       const uint32_t InData_KeyIndex[],
                       const uint32_t InData_HashType[],
                       const uint32_t InData_State[]);
rsip_ret_t r_rsip_pe5s(uint32_t OutData_State[]);
rsip_ret_t r_rsip_pe5u(const uint32_t InData_Msg[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_pe6(const uint32_t InData_HashType[],
                      const uint32_t InData_KDFInfo[],
                      const uint32_t InData_KDFInfo_Count[],
                      const uint32_t InData_OutDataLength[],
                      uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_pe7(const uint32_t InData_HashType[],
                      const uint32_t InData_KDFInfo[],
                      const uint32_t InData_KDFInfo_Count[],
                      const uint32_t InData_OutDataType[],
                      const uint32_t InData_OutDataLocation[],
                      const uint32_t InData_SeqNum[],
                      uint32_t       OutData_HMACKeyIndex[],
                      uint32_t       OutData_KeyIndex[],
                      uint32_t       OutData_EncIV[]);
rsip_ret_t r_rsip_peef(uint32_t OutData_EncCertificateInfo[]);
rsip_ret_t r_rsip_peei(const uint32_t InData_KeyIndex[],
                       const uint32_t InData_MsgDgst[],
                       const uint32_t InData_Signature[],
                       const uint32_t InData_DomainParam[]);
rsip_ret_t r_rsip_p51f(uint32_t OutData_EncCertificateInfo[]);
rsip_ret_t r_rsip_p51i(const uint32_t InData_KeyIndex[],
                       const uint32_t InData_MsgDgst[],
                       const uint32_t InData_Signature[],
                       const uint32_t InData_DomainParam[]);
rsip_ret_t r_rsip_p52f(uint32_t OutData_EncCertificateInfo[]);
rsip_ret_t r_rsip_p52i(const uint32_t InData_KeyIndex[],
                       const uint32_t InData_MsgDgst[],
                       const uint32_t InData_Signature[],
                       const uint32_t InData_DomainParam[]);

rsip_ret_t r_rsip_p0c(const uint32_t InData_CurrentVer[], const uint32_t InData_NextVer[]);
rsip_ret_t r_rsip_p0d(const uint32_t InData_KeyCertificate[],
                      const uint32_t InData_KeyCertificateLength[],
                      const uint32_t InData_KeyCertificateSignature[],
                      const uint32_t InData_KeyCertificatePubKey[],
                      const uint32_t InData_ImgPkHash[],
                      const uint32_t InData_OemRootPkHashIndex[],
                      const uint32_t InData_CodeCertificate[],
                      const uint32_t InData_CodeCertificateLength[],
                      const uint32_t InData_CodeCertificateSignature[],
                      const uint32_t InData_CodeCertificatePubKey[],
                      const uint32_t InData_Image[],
                      const uint32_t InData_DomainParam[],
                      uint32_t       MAX_CNT,
                      uint32_t       OutData_MAC[]);
rsip_ret_t r_rsip_p0e(void);

#endif                                 /* R_RSIP_PRIMITIVE_H */
