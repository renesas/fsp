/* ${REA_DISCLAIMER_PLACEHOLDER}7F */

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

#define RSIP_PRV_WORD_SIZE_S_RAM     (2U)
#define RSIP_PRV_WORD_SIZE_S_HEAP    (16U)

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

extern uint32_t         S_RAM[RSIP_PRV_WORD_SIZE_S_RAM];
extern uint32_t         S_HEAP[RSIP_PRV_WORD_SIZE_S_HEAP];
extern uint32_t const * S_INST2;

extern uint32_t const DomainParam_NIST_P256[];
extern uint32_t const DomainParam_NIST_P384[];
extern uint32_t const DomainParam_Brainpool_256r1[];
extern uint32_t const DomainParam_Brainpool_384r1[];
extern uint32_t const DomainParam_Koblitz_secp256k1[];
extern uint32_t       INST_DATA_SIZE;

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/

void r_rsip_func008(void);
void r_rsip_func027(const uint32_t ARG1[]);
void r_rsip_func028(const uint32_t ARG1[]);
void r_rsip_func029(const uint32_t ARG1[]);
void r_rsip_func030(void);
void r_rsip_func040(void);
void r_rsip_func043(void);
void r_rsip_func044(void);
void r_rsip_func048(const uint32_t ARG1[]);
void r_rsip_func049(const uint32_t ARG1[]);
void r_rsip_func056(void);
void r_rsip_func057(const uint32_t ARG1[], const uint32_t ARG2[], uint32_t ARG3[]);
void r_rsip_func070(const uint32_t ARG1[]);
void r_rsip_func071(const uint32_t ARG1[]);
void r_rsip_func073(const uint32_t ARG1[]);
void r_rsip_func074(void);
void r_rsip_func075(void);
void r_rsip_func076(void);
void r_rsip_func077(void);
void r_rsip_func081(void);
void r_rsip_func088(void);
void r_rsip_func089(void);
void r_rsip_func100(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);
void r_rsip_func101(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);
void r_rsip_func102(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);
void r_rsip_func103(void);
void r_rsip_func143(void);
void r_rsip_func205(void);
void r_rsip_func206(void);
void r_rsip_func407(const uint32_t ARG1[]);
void r_rsip_func410(const uint32_t ARG1[]);
void r_rsip_func430(const uint32_t ARG1[], const uint32_t ARG2);
void r_rsip_func440(const uint32_t ARG1[]);
void r_rsip_func441(const uint32_t ARG1[]);
void r_rsip_func501(const uint32_t ARG1[], const uint32_t ARG2);
void r_rsip_func510(const uint32_t ARG1[], const uint32_t ARG2[]);

void       r_rsip_p00(void);
rsip_ret_t r_rsip_p81(void);
rsip_ret_t r_rsip_p82(void);
rsip_ret_t r_rsip_p40(const uint32_t InData_LC[]);
rsip_ret_t r_rsip_p6f(const uint32_t InData_LC[],
                      const uint32_t InData_Cmd[],
                      const uint32_t InData_IV[],
                      const uint32_t InData_InstData[],
                      uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_p07(uint32_t OutData_KeyIndex[]);
rsip_ret_t r_rsip_p08(uint32_t OutData_KeyIndex[]);
rsip_ret_t r_rsip_pf4(const uint32_t InData_CurveType[],
                      const uint32_t InData_DomainParam[],
                      uint32_t       OutData_PubKeyIndex[],
                      uint32_t       OutData_PrivKeyIndex[]);
rsip_ret_t r_rsip_pf9(const uint32_t InData_CurveType[],
                      const uint32_t InData_DomainParam[],
                      uint32_t       OutData_PubKeyIndex[],
                      uint32_t       OutData_PrivKeyIndex[]);
rsip_ret_t r_rsip_p20(uint32_t OutData_Text[]);
rsip_ret_t r_rsip_p21(const uint32_t InData_HV[],
                      const uint32_t InData_IV[],
                      const uint32_t InData_Text[],
                      uint32_t       OutData_DataT[],
                      uint32_t       MAX_CNT);
rsip_ret_t r_rsip_p47i(const uint32_t InData_Cmd[],
                       const uint32_t InData_KeyIndex[],
                       const uint32_t InData_IVType[],
                       const uint32_t InData_IV[]);
void       r_rsip_p47u(const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p47f(void);
rsip_ret_t r_rsip_p50i(const uint32_t InData_Cmd[],
                       const uint32_t InData_KeyIndex[],
                       const uint32_t InData_IVType[],
                       const uint32_t InData_IV[]);
void       r_rsip_p50u(const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p50f(void);
rsip_ret_t r_rsip_p29i(const uint32_t InData_KeyIndex[], const uint32_t InData_IVType[], const uint32_t InData_IV[]);
void       r_rsip_p29a(const uint32_t InData_DataA[], uint32_t MAX_CNT);
void       r_rsip_p29t(void);
void       r_rsip_p29u(const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p29f(const uint32_t InData_Text[],
                       const uint32_t InData_DataALen[],
                       const uint32_t InData_TextLen[],
                       uint32_t       OutData_Text[],
                       uint32_t       OutData_DataT[]);
rsip_ret_t r_rsip_p32i(const uint32_t InData_KeyIndex[], const uint32_t InData_IVType[], const uint32_t InData_IV[]);
void       r_rsip_p32a(const uint32_t InData_DataA[], uint32_t MAX_CNT);
void       r_rsip_p32t(void);
void       r_rsip_p32u(const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p32f(const uint32_t InData_Text[],
                       const uint32_t InData_DataT[],
                       const uint32_t InData_DataALen[],
                       const uint32_t InData_TextLen[],
                       const uint32_t InData_DataTLen[],
                       uint32_t       OutData_Text[]);
rsip_ret_t r_rsip_p34i(const uint32_t InData_KeyIndex[], const uint32_t InData_IVType[], const uint32_t InData_IV[]);
void       r_rsip_p34a(const uint32_t InData_DataA[], uint32_t MAX_CNT);
void       r_rsip_p34t(void);
void       r_rsip_p34u(const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p34f(const uint32_t InData_Text[],
                       const uint32_t InData_DataALen[],
                       const uint32_t InData_TextLen[],
                       uint32_t       OutData_Text[],
                       uint32_t       OutData_DataT[]);
rsip_ret_t r_rsip_p36i(const uint32_t InData_KeyIndex[], const uint32_t InData_IVType[], const uint32_t InData_IV[]);
void       r_rsip_p36a(const uint32_t InData_DataA[], uint32_t MAX_CNT);
void       r_rsip_p36t(void);
void       r_rsip_p36u(const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p36f(const uint32_t InData_Text[],
                       const uint32_t InData_DataT[],
                       const uint32_t InData_DataALen[],
                       const uint32_t InData_TextLen[],
                       const uint32_t InData_DataTLen[],
                       uint32_t       OutData_Text[]);
rsip_ret_t r_rsip_p41i(const uint32_t InData_KeyIndex[]);
void       r_rsip_p41u(const uint32_t InData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p41f(const uint32_t InData_Cmd[],
                       const uint32_t InData_Text[],
                       const uint32_t InData_DataT[],
                       const uint32_t InData_DataTLen[],
                       uint32_t       OutData_DataT[]);
rsip_ret_t r_rsip_p44i(const uint32_t InData_KeyIndex[]);
void       r_rsip_p44u(const uint32_t InData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p44f(const uint32_t InData_Cmd[],
                       const uint32_t InData_Text[],
                       const uint32_t InData_DataT[],
                       const uint32_t InData_DataTLen[],
                       uint32_t       OutData_DataT[]);
rsip_ret_t r_rsip_p73i(const uint32_t InData_HashType[], const uint32_t InData_MsgLen[]);
rsip_ret_t r_rsip_p73u(const uint32_t InData_Msg[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p73f(const uint32_t InData_Msg[], uint32_t MAX_CNT, uint32_t OutData_MsgDigest[]);
rsip_ret_t r_rsip_p73s(uint32_t OutData_State[]);
rsip_ret_t r_rsip_p73r(const uint32_t InData_HashType[], const uint32_t InData_State[]);
rsip_ret_t r_rsip_pf0(const uint32_t InData_CurveType[],
                      const uint32_t InData_KeyIndex[],
                      const uint32_t InData_MsgDgst[],
                      const uint32_t InData_DomainParam[],
                      uint32_t       OutData_Signature[]);
rsip_ret_t r_rsip_pf1(const uint32_t InData_CurveType[],
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
rsip_ret_t r_rsip_p8f(const uint32_t InData_Cmd[],
                      const uint32_t InData_KeyIndex[],
                      const uint32_t InData_WrappedKeyType[],
                      const uint32_t InData_WrappedKeyIndex[],
                      uint32_t       OutData_Text[],
                      uint32_t       KEY_INDEX_SIZE,
                      uint32_t       WRAPPED_KEY_SIZE);
rsip_ret_t r_rsip_p90(const uint32_t InData_Cmd[],
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
rsip_ret_t r_rsip_pe3(const uint32_t InData_HashType[], const uint32_t InData_EncSecret[], uint32_t OutData_EncMsg[]);
rsip_ret_t r_rsip_pe7(const uint32_t InData_HashType[],
                      const uint32_t InData_KDFInfo[],
                      const uint32_t InData_KDFInfo_Count[],
                      const uint32_t InData_OutDataType[],
                      const uint32_t InData_OutDataLocation[],
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
rsip_ret_t r_rsip_pefi(const uint32_t InData_HashType[], const uint32_t InData_MsgLen[]);
rsip_ret_t r_rsip_pefr(const uint32_t InData_HashType[], const uint32_t InData_State[]);
rsip_ret_t r_rsip_pefu(const uint32_t InData_Msg1[],
                       const uint32_t InData_Msg1Length[],
                       const uint32_t InData_EncMsg[],
                       const uint32_t InData_EncMsgLength[],
                       const uint32_t InData_Msg2[],
                       const uint32_t InData_Msg2Length[]);
rsip_ret_t r_rsip_pefs(uint32_t OutData_State[]);
rsip_ret_t r_rsip_peff(const uint32_t InData_Msg1[],
                       const uint32_t InData_Msg1Length[],
                       const uint32_t InData_EncMsg[],
                       const uint32_t InData_EncMsgLength[],
                       const uint32_t InData_Msg2[],
                       const uint32_t InData_Msg2Length[],
                       uint32_t       OutData_KDFInfo[]);

#endif                                 /* R_RSIP_PRIMITIVE_H */
