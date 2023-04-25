#include "SCE_ProcCommon.h"

#ifndef HW_SCE_RA_PRIVATE_HEADER_FILE
#define HW_SCE_RA_PRIVATE_HEADER_FILE

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
/* Version Number of API. */
#define SCE_VERSION_MAJOR    (1U)
#define SCE_VERSION_MINOR    (9U)

/* Various information. */
#define HW_SCE_SRAM_WORD_SIZE   (32U)
#define HW_SCE_SINST_WORD_SIZE  (140U)
#define HW_SCE_SINST2_WORD_SIZE (16U)
#define HW_SCE_SHEAP_WORD_SIZE  (1504U)
#define HW_SCE_MAC_SIZE         (16U)

/* For AES operation. */
#define HW_SCE_AES128_KEY_INDEX_WORD_SIZE     (12U)
#define HW_SCE_AES192_KEY_INDEX_WORD_SIZE     (16U)
#define HW_SCE_AES256_KEY_INDEX_WORD_SIZE     (16U)
#define HW_SCE_AES128_KEY_WORD_SIZE           (4U)
#define HW_SCE_AES192_KEY_WORD_SIZE           (8U)
#define HW_SCE_AES256_KEY_WORD_SIZE           (8U)
#define HW_SCE_AES128_KEY_BYTE_SIZE           (16U)
#define HW_SCE_AES192_KEY_BYTE_SIZE           (32U)
#define HW_SCE_AES256_KEY_BYTE_SIZE           (32U)
#define HW_SCE_AES_BLOCK_BYTE_SIZE            (16U)
#define HW_SCE_AES_BLOCK_BIT_SIZE             (128U)
#define HW_SCE_AES_CBC_IV_BYTE_SIZE           (16U)
#define HW_SCE_AES_CTR_ICOUNTER_BYTE_SIZE     (16U)
#define HW_SCE_AES_GCM_AAD_BLOCK_BYTE_SIZE    (16U)
#define HW_SCE_AES_CCM_B_FORMAT_BYTE_SIZE     (128U)
#define HW_SCE_AES_CCM_COUNTER_BYTE_SIZE      (16U)
#define HW_SCE_AES128XTS_KEY_BYTE_SIZE        (32U)
#define HW_SCE_AES256XTS_KEY_BYTE_SIZE        (64U)
#define HW_SCE_AES_XTS_IV_BYTE_SIZE           (16U)

/* For TDES operation. */
#define HW_SCE_TDES_KEY_INDEX_WORD_SIZE       (16U)
#define HW_SCE_TDES_BLOCK_BYTE_SIZE           (8U)
#define HW_SCE_TDES_CBC_IV_BYTE_SIZE          (8U)
#define HW_SCE_TDES_KEY_WORD_SIZE             (8U)
#define HW_SCE_TDES_KEY_BYTE_SIZE             (32U)

/* For ARC4 operation. */
#define HW_SCE_ARC4_KEY_INDEX_WORD_SIZE       (72U)
#define HW_SCE_ARC4_KEY_WORD_SIZE             (64U)
#define HW_SCE_ARC4_KEY_BYTE_SIZE             (256U)
#define HW_SCE_ARC4_BLOCK_BYTE_SIZE           (16U)

/* For SHA operation. */
#define HW_SCE_SHA1_HASH_LENGTH_BYTE_SIZE      (20U)
#define HW_SCE_SHA256_HASH_LENGTH_BYTE_SIZE    (32U)
#define HW_SCE_SHA384_HASH_LENGTH_BYTE_SIZE    (48U)

/* For MD5 operation. */
#define HW_SCE_MD5_HASH_LENGTH_BYTE_SIZE       (16U)

/* For HMAC operation. */
#define HW_SCE_HMAC_KEY_INDEX_BYTE_SIZE        (32U)
#define HW_SCE_HMAC_KEY_INDEX_WORD_SIZE        (8U)

/* For RSA operation. */
#define HW_SCE_RSA_1024_KEY_N_LENGTH_BYTE_SIZE                  (128U)
#define HW_SCE_RSA_1024_KEY_E_LENGTH_BYTE_SIZE                  (4U)
#define HW_SCE_RSA_1024_KEY_D_LENGTH_BYTE_SIZE                  (128U)
#define HW_SCE_RSA_2048_KEY_N_LENGTH_BYTE_SIZE                  (256U)
#define HW_SCE_RSA_2048_KEY_E_LENGTH_BYTE_SIZE                  (4U)
#define HW_SCE_RSA_2048_KEY_D_LENGTH_BYTE_SIZE                  (256U)
#define HW_SCE_RSA_3072_KEY_N_LENGTH_BYTE_SIZE                  (96  * 4U)
#define HW_SCE_RSA_3072_KEY_E_LENGTH_BYTE_SIZE                  (4U)
#define HW_SCE_RSA_3072_KEY_D_LENGTH_BYTE_SIZE                  (96  * 4U)
#define HW_SCE_RSA_4096_KEY_N_LENGTH_BYTE_SIZE                  (128 * 4U)
#define HW_SCE_RSA_4096_KEY_E_LENGTH_BYTE_SIZE                  (4U)
#define HW_SCE_RSA_4096_KEY_D_LENGTH_BYTE_SIZE                  (128 * 4U)
#define HW_SCE_RSA_1024_PUBLIC_KEY_MANAGEMENT_INFO1_WORD_SIZE   (1U)
#define HW_SCE_RSA_1024_PUBLIC_KEY_MANAGEMENT_INFO2_WORD_SIZE   (36U)
#define HW_SCE_RSA_1024_PRIVATE_KEY_MANAGEMENT_INFO1_WORD_SIZE  (1U)
#define HW_SCE_RSA_1024_PRIVATE_KEY_MANAGEMENT_INFO2_WORD_SIZE  (68U)
#define HW_SCE_RSA_2048_PUBLIC_KEY_MANAGEMENT_INFO1_WORD_SIZE   (1U)
#define HW_SCE_RSA_2048_PUBLIC_KEY_MANAGEMENT_INFO2_WORD_SIZE   (68U)
#define HW_SCE_RSA_2048_PRIVATE_KEY_MANAGEMENT_INFO1_WORD_SIZE  (1U)
#define HW_SCE_RSA_2048_PRIVATE_KEY_MANAGEMENT_INFO2_WORD_SIZE  (132U)
#define HW_SCE_RSA_3072_PUBLIC_KEY_MANAGEMENT_INFO1_WORD_SIZE   (1U)
#define HW_SCE_RSA_3072_PUBLIC_KEY_MANAGEMENT_INFO2_WORD_SIZE   (19U)
#define HW_SCE_RSA_3072_PRIVATE_KEY_MANAGEMENT_INFO1_WORD_SIZE  (1U)
#define HW_SCE_RSA_3072_PRIVATE_KEY_MANAGEMENT_INFO2_WORD_SIZE  (132U)
#define HW_SCE_RSA_4096_PUBLIC_KEY_MANAGEMENT_INFO1_WORD_SIZE   (1U)
#define HW_SCE_RSA_4096_PUBLIC_KEY_MANAGEMENT_INFO2_WORD_SIZE   (19U)
#define HW_SCE_RSA_4096_PRIVATE_KEY_MANAGEMENT_INFO1_WORD_SIZE  (1U)
#define HW_SCE_RSA_4096_PRIVATE_KEY_MANAGEMENT_INFO2_WORD_SIZE  (132U)
#define HW_SCE_RSA_KEY_GENERATION_DUMMY_BYTE_SIZE               (12U)
#define HW_SCE_RSA1024_NE_KEY_BYTE_SIZE                         (144U)
#define HW_SCE_RSA1024_ND_KEY_BYTE_SIZE                         (256U)
#define HW_SCE_RSA2048_NE_KEY_BYTE_SIZE                         (272U)
#define HW_SCE_RSA2048_ND_KEY_BYTE_SIZE                         (512U)
#define HW_SCE_RSA3072_NE_KEY_BYTE_SIZE                         (96  * 4 + 16U)
#define HW_SCE_RSA3072_ND_KEY_BYTE_SIZE                         (192 * 4U)
#define HW_SCE_RSA4096_NE_KEY_BYTE_SIZE                         (128 * 4 + 16U)
#define HW_SCE_RSA4096_ND_KEY_BYTE_SIZE                         (256 * 4U)
#define HW_SCE_RSA1024_NE_KEY_INDEX_WORD_SIZE                   (73U)
#define HW_SCE_RSA1024_ND_KEY_INDEX_WORD_SIZE                   (101U)
#define HW_SCE_RSA2048_NE_KEY_INDEX_WORD_SIZE                   (137U)
#define HW_SCE_RSA2048_ND_KEY_INDEX_WORD_SIZE                   (197U)
#define HW_SCE_RSA3072_NE_KEY_INDEX_WORD_SIZE                   (137U)
#define HW_SCE_RSA3072_ND_KEY_INDEX_WORD_SIZE                   (197U)
#define HW_SCE_RSA4096_NE_KEY_INDEX_WORD_SIZE                   (137U)
#define HW_SCE_RSA4096_ND_KEY_INDEX_WORD_SIZE                   (197U)
#define HW_SCE_RSA1024_RANDOM_PUBLIC_KEY_INDEX_WORD_SIZE        (76U)
#define HW_SCE_RSA1024_RANDOM_PRIVATE_KEY_INDEX_WORD_SIZE       (104U)
#define HW_SCE_RSA2048_RANDOM_PUBLIC_KEY_INDEX_WORD_SIZE        (140U)
#define HW_SCE_RSA2048_RANDOM_PRIVATE_KEY_INDEX_WORD_SIZE       (200U)
//#define HW_SCE_RSA3072_RANDOM_PUBLIC_KEY_INDEX_WORD_SIZE        (140U)
//#define HW_SCE_RSA3072_RANDOM_PRIVATE_KEY_INDEX_WORD_SIZE       (200U)
//#define HW_SCE_RSA4096_RANDOM_PUBLIC_KEY_INDEX_WORD_SIZE        (140U)
//#define HW_SCE_RSA4096_RANDOM_PRIVATE_KEY_INDEX_WORD_SIZE       (200U)
#define HW_SCE_RSA_RSAES_PKCS_MIN_KEY_N_BYTE_SIZE               (11U)
#define HW_SCE_RSA_1024_DATA_BYTE_SIZE                          (128U)
#define HW_SCE_RSA_2048_DATA_BYTE_SIZE                          (256U)
#define HW_SCE_RSA_3072_DATA_BYTE_SIZE                          (96  * 4U)
#define HW_SCE_RSA_4096_DATA_BYTE_SIZE                          (128 * 4U)

/* RSA HASH type. */
#define HW_SCE_RSA_HASH_MD5                                     (0x01)  /* MD5     */
#define HW_SCE_RSA_HASH_SHA1                                    (0x02)  /* SHA-1   */
#define HW_SCE_RSA_HASH_SHA256                                  (0x03)  /* SHA-256 */

/* For ECC operation. */
//#define HW_SCE_ECC_KEY_LENGTH_BYTE_SIZE                     (32U)
//#define HW_SCE_ECC_PUBLIC_KEY_MANAGEMENT_INFO1_WORD_SIZE    (4U)
//#define HW_SCE_ECC_PUBLIC_KEY_MANAGEMENT_INFO2_WORD_SIZE    (4U)
//#define HW_SCE_ECC_PRIVATE_KEY_MANAGEMENT_INFO1_WORD_SIZE   (4U)
//#define HW_SCE_ECC_PRIVATE_KEY_MANAGEMENT_INFO2_WORD_SIZE   (12U)
//#define HW_SCE_ECC_PUBLIC_KEY_BYTE_SIZE                     (64U)
//#define HW_SCE_ECC_P384_PUBLIC_KEY_BYTE_SIZE                (96U)
//#define HW_SCE_ECC_PRIVATE_KEY_BYTE_SIZE                    (32U)
//#define HW_SCE_ECC_P384_PRIVATE_KEY_BYTE_SIZE               (48U)
//#define HW_SCE_ECDSA_DATA_BYTE_SIZE                         (64U)
//#define HW_SCE_ECDSA_P384_DATA_BYTE_SIZE                    (96U)
//#define HW_SCE_SHARED_SECRET_KEY_INDEX_WORD_SIZE            (16U)
//#define HW_SCE_ALGORITHM_ID_ENCODED_DATA_BYTE_SIZE          (7U)
#define HW_SCE_ECC_KEY_LENGTH_BYTE_SIZE                     (112U)
#define HW_SCE_ECC_PUBLIC_KEY_MANAGEMENT_INFO_WORD_SIZE     (4U)
#define HW_SCE_ECC_PRIVATE_KEY_MANAGEMENT_INFO_WORD_SIZE    (20U)
#define HW_SCE_ECC_PUBLIC_KEY_BYTE_SIZE                     (64U)
#define HW_SCE_ECC_P384_PUBLIC_KEY_BYTE_SIZE                (96U)
#define HW_SCE_ECC_PRIVATE_KEY_BYTE_SIZE                    (32U)
#define HW_SCE_ECC_P384_PRIVATE_KEY_BYTE_SIZE               (48U)
#define HW_SCE_ECDSA_DATA_BYTE_SIZE                         (64U)
#define HW_SCE_ECDSA_P384_DATA_BYTE_SIZE                    (96U)
#define HW_SCE_SHARED_SECRET_KEY_INDEX_WORD_SIZE            (16U)
#define HW_SCE_ALGORITHM_ID_ENCODED_DATA_BYTE_SIZE          (7U)

/* For KeyWrap. */
#define HW_SCE_KEYWRAP_AES128   (0U)
#define HW_SCE_KEYWRAP_AES256   (2U)

/* For TLS. */
#define HW_SCE_TLS_RSA_NE_KEY_BYTE_SIZE                     (272U)
#define HW_SCE_TLS_RSA_NE_KEY_INDEX_WORD_SIZE               (140U)
#define HW_SCE_TLS_ROOT_PUBLIC_KEY_WORD_SIZE                (140U)
#define HW_SCE_TLS_P256_ECC_KEY_WORD_SIZE                   (16U)
#define HW_SCE_TLS_EPHEMERAL_ECDH_PUBLIC_KEY_WORD_SIZE      (16U)
#define HW_SCE_TLS_MASTER_SECRET_WORD_SIZE                  (20U)
#define HW_SCE_TLS_GENERATE_MAC_KEY_WORD_SIZE               (16U)
#define HW_SCE_TLS_GENERATE_AES128_CRYPTO_KEY_WORD_SIZE     (12U)
#define HW_SCE_TLS_GENERATE_AES256_CRYPTO_KEY_WORD_SIZE     (16U)
#define HW_SCE_TLS_GENERATE_VERIFY_DATA_BYTE_SIZE           (12U)
#define HW_SCE_TLS_RSA_WITH_AES_128_CBC_SHA                 (0U)
#define HW_SCE_TLS_RSA_WITH_AES_256_CBC_SHA                 (1U)
#define HW_SCE_TLS_RSA_WITH_AES_128_CBC_SHA256              (2U)
#define HW_SCE_TLS_RSA_WITH_AES_256_CBC_SHA256              (3U)
#define HW_SCE_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256      (4U)
#define HW_SCE_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256        (5U)
#define HW_SCE_TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256      (6U)
#define HW_SCE_TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256        (7U)
#define HW_SCE_TLS_GENERATE_CLIENT_VERIFY                   (0U)
#define HW_SCE_TLS_GENERATE_SERVER_VERIFY                   (1U)
#define HW_SCE_TLS_PUBLIC_KEY_TYPE_RSA2048                  (0U)
#define HW_SCE_TLS_PUBLIC_KEY_TYPE_ECDSA_P256               (2U)

/* TLS-HMAC. */
#define HW_SCE_TLS_HMAC_KEY_INDEX_BYTE_SIZE                 (64U)
#define HW_SCE_TLS_HMAC_KEY_INDEX_WORD_SIZE                 (16U)

/* TLS-AES. */
#define HW_SCE_TLS_AES128_KEY_INDEX_WORD_SIZE               (12U)
#define HW_SCE_TLS_AES256_KEY_INDEX_WORD_SIZE               (16U)

/* Key update. */
#define HW_SCE_UPDATE_KEY_RING_INDEX_WORD_SIZE  (16U)

/* Firmware update. */
#define HW_SCE_FIRMWARE_MAC_BYTE_SIZE           (16U)
#if defined BSP_MCU_RX231 || defined BSP_MCU_RX23W
#define HW_SCE_SECURE_BOOT_AREA_TOP             (0xFFFF8000)
#else
#define HW_SCE_SECURE_BOOT_AREA_TOP             (0xFFFF0000)
#endif  /* defined BSP_MCU_RX231 || defined BSP_MCU_RX23W */

#define SCE_OEM_KEY_SIZE_DUMMY_INST_DATA_WORD                    (0)
#define SCE_OEM_KEY_SIZE_AES128_INST_DATA_WORD                   (8)
#define SCE_OEM_KEY_SIZE_AES192_INST_DATA_WORD                   (12)
#define SCE_OEM_KEY_SIZE_AES256_INST_DATA_WORD                   (12)
#define SCE_OEM_KEY_SIZE_AES128_XTS_INST_DATA_WORD               (12)
#define SCE_OEM_KEY_SIZE_AES256_XTS_INST_DATA_WORD               (20)

#define SCE_OEM_KEY_SIZE_RSA1024_PUBLICK_KEY_INST_DATA_WORD      (40)
#define SCE_OEM_KEY_SIZE_RSA1024_PRIVATE_KEY_INST_DATA_WORD      (68)
#define SCE_OEM_KEY_SIZE_RSA2048_PUBLICK_KEY_INST_DATA_WORD      (72)
#define SCE_OEM_KEY_SIZE_RSA2048_PRIVATE_KEY_INST_DATA_WORD      (132)
#define SCE_OEM_KEY_SIZE_RSA3072_PUBLICK_KEY_INST_DATA_WORD      (104)
#define SCE_OEM_KEY_SIZE_RSA3072_PRIVATE_KEY_INST_DATA_WORD      (196)
#define SCE_OEM_KEY_SIZE_RSA4096_PUBLICK_KEY_INST_DATA_WORD      (136)
#define SCE_OEM_KEY_SIZE_RSA4096_PRIVATE_KEY_INST_DATA_WORD      (260)

#define SCE_OEM_KEY_SIZE_ECCP192_PUBLICK_KEY_INST_DATA_WORD      (20)
#define SCE_OEM_KEY_SIZE_ECCP192_PRIVATE_KEY_INST_DATA_WORD      (12)
#define SCE_OEM_KEY_SIZE_ECCP224_PUBLICK_KEY_INST_DATA_WORD      (20)
#define SCE_OEM_KEY_SIZE_ECCP224_PRIVATE_KEY_INST_DATA_WORD      (12)
#define SCE_OEM_KEY_SIZE_ECCP256_PUBLICK_KEY_INST_DATA_WORD      (20)
#define SCE_OEM_KEY_SIZE_ECCP256_PRIVATE_KEY_INST_DATA_WORD      (12)
#define SCE_OEM_KEY_SIZE_ECCP384_PUBLICK_KEY_INST_DATA_WORD      (28)
#define SCE_OEM_KEY_SIZE_ECCP384_PRIVATE_KEY_INST_DATA_WORD      (16)
#define SCE_OEM_KEY_SIZE_HMAC_SHA224_INST_DATA_WORD              (12)
#define SCE_OEM_KEY_SIZE_HMAC_SHA256_INST_DATA_WORD              (12)
#define SCE_OEM_KEY_SIZE_ECCP256R1_PUBLICK_KEY_INST_DATA_WORD    (20)
#define SCE_OEM_KEY_SIZE_ECCP256R1_PRIVATE_KEY_INST_DATA_WORD    (12)
#define SCE_OEM_KEY_SIZE_ECCP384R1_PUBLICK_KEY_INST_DATA_WORD    (28)
#define SCE_OEM_KEY_SIZE_ECCP384R1_PRIVATE_KEY_INST_DATA_WORD    (16)
#define SCE_OEM_KEY_SIZE_ECCP512R1_PUBLICK_KEY_INST_DATA_WORD    (36)
#define SCE_OEM_KEY_SIZE_ECCP512R1_PRIVATE_KEY_INST_DATA_WORD    (20)
#define SCE_OEM_KEY_SIZE_ECCSECP256K1_PUBLICK_KEY_INST_DATA_WORD (20)
#define SCE_OEM_KEY_SIZE_ECCSECP256K1_PRIVATE_KEY_INST_DATA_WORD (12)
#define SCE_OEM_KEY_SIZE_ECCP521_PUBLICK_KEY_INST_DATA_WORD      (44)
#define SCE_OEM_KEY_SIZE_ECCP521_PRIVATE_KEY_INST_DATA_WORD      (24)

/**********************************************************************************************************************
 External global variables
 *********************************************************************************************************************/
extern uint32_t const S_FLASH2[];
extern uint32_t S_INST[HW_SCE_SINST_WORD_SIZE];
extern uint32_t S_INST2[HW_SCE_SINST2_WORD_SIZE];
extern uint32_t S_RAM[HW_SCE_SRAM_WORD_SIZE];
extern uint32_t S_HEAP[HW_SCE_SHEAP_WORD_SIZE];


extern uint32_t INST_DATA_SIZE;
extern uint32_t KEY_INDEX_SIZE;

 /* OEM Command */
 typedef enum e_sce_oem_cmd
 {
     SCE_OEM_CMD_AES128 = 5,
     SCE_OEM_CMD_AES192,
     SCE_OEM_CMD_AES256,
     SCE_OEM_CMD_AES128_XTS,
     SCE_OEM_CMD_AES256_XTS,
     SCE_OEM_CMD_RSA1024_PUBLIC,
     SCE_OEM_CMD_RSA1024_PRIVATE,
     SCE_OEM_CMD_RSA2048_PUBLIC,
     SCE_OEM_CMD_RSA2048_PRIVATE,
     SCE_OEM_CMD_RSA3072_PUBLIC,
     SCE_OEM_CMD_RSA3072_PRIVATE,
     SCE_OEM_CMD_RSA4096_PUBLIC,
     SCE_OEM_CMD_RSA4096_PRIVATE,
     SCE_OEM_CMD_ECC_P192_PUBLIC,
     SCE_OEM_CMD_ECC_P192_PRIVATE,
     SCE_OEM_CMD_ECC_P224_PUBLIC,
     SCE_OEM_CMD_ECC_P224_PRIVATE,
     SCE_OEM_CMD_ECC_P256_PUBLIC,
     SCE_OEM_CMD_ECC_P256_PRIVATE,
     SCE_OEM_CMD_ECC_P384_PUBLIC,
     SCE_OEM_CMD_ECC_P384_PRIVATE,
     SCE_OEM_CMD_HMAC_SHA224,
     SCE_OEM_CMD_HMAC_SHA256,
     SCE_OEM_CMD_ECC_P256R1_PUBLIC,
     SCE_OEM_CMD_ECC_P256R1_PRIVATE,
     SCE_OEM_CMD_ECC_P384R1_PUBLIC,
     SCE_OEM_CMD_ECC_P384R1_PRIVATE,
     SCE_OEM_CMD_ECC_P512R1_PUBLIC,
     SCE_OEM_CMD_ECC_P512R1_PRIVATE,
     SCE_OEM_CMD_ECC_SECP256K1_PUBLIC,
     SCE_OEM_CMD_ECC_SECP256K1_PRIVATE,
     SCE_OEM_CMD_ECC_P521_PUBLIC,
     SCE_OEM_CMD_ECC_P521_PRIVATE,
     SCE_OEM_CMD_ED25519_PUBLIC,
     SCE_OEM_CMD_ED25519_PRIVATE,
     SCE_OEM_CMD_RSA2048_PUBLIC_FOR_TLS = 254,
     SCE_OEM_CMD_NUM
 } sce_oem_cmd_t;

/* --------------------- SCE control procedure related ---------------------- */
void HW_SCE_p_func008(void);
void HW_SCE_p_func027(uint32_t ARG1);
void HW_SCE_p_func028(uint32_t ARG1);
void HW_SCE_p_func031(const uint32_t ARG1[]);
void HW_SCE_p_func043(void);
void HW_SCE_p_func044(void);
void HW_SCE_p_func048(const uint32_t ARG1[]);
void HW_SCE_p_func049(const uint32_t ARG1[]);
void HW_SCE_p_func057(const uint32_t ARG1[], const uint32_t ARG2[], uint32_t ARG3[]);
void HW_SCE_p_func058(const uint32_t ARG1[], uint32_t ARG2);
void HW_SCE_p_func059(void);
void HW_SCE_p_func060(void);
void HW_SCE_p_func061(const uint32_t ARG1, const uint32_t ARG2[]);
void HW_SCE_p_func062(const uint32_t ARG1, uint32_t ARG2[]);
void HW_SCE_p_func063(const uint32_t ARG1, const uint32_t ARG2[]);
void HW_SCE_p_func065(const uint32_t ARG1, uint32_t ARG2[]);
void HW_SCE_p_func066(void);
void HW_SCE_p_func068(void);
void HW_SCE_p_func070(uint32_t ARG1);
void HW_SCE_p_func071(uint32_t ARG1);
void HW_SCE_p_func073(uint32_t ARG1);
void HW_SCE_p_func074(void);
void HW_SCE_p_func075(void);
void HW_SCE_p_func076(void);
void HW_SCE_p_func077(void);
void HW_SCE_p_func078(uint32_t ARG1);
void HW_SCE_p_func079(uint32_t ARG1);
void HW_SCE_p_func081(void);
void HW_SCE_p_func082(void);
void HW_SCE_p_func086(uint32_t ARG1);
void HW_SCE_p_func087(uint32_t ARG1);
void HW_SCE_p_func088(void);
void HW_SCE_p_func089(void);
void HW_SCE_p_func090(void);
void HW_SCE_p_func091(void);
void HW_SCE_p_func092(void);
void HW_SCE_p_func093(const uint32_t ARG1[], uint32_t ARG2[]);
void HW_SCE_p_func094(uint32_t ARG1, const uint32_t ARG2[]);
void HW_SCE_p_func095(uint32_t ARG1, const uint32_t ARG2[]);
void HW_SCE_p_func100(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);
void HW_SCE_p_func101(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);
void HW_SCE_p_func102(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);
void HW_SCE_p_func103(void);
void HW_SCE_p_func202(void);
void HW_SCE_p_func209(void);
void HW_SCE_p_func214(void);
void HW_SCE_p_func215(void);
void HW_SCE_p_func216(void);
void HW_SCE_SoftwareResetSub (void);
void HW_SCE_Aes128GcmEncryptUpdateAADSub (const uint32_t InData_DataA[], const uint32_t MAX_CNT);
void HW_SCE_Aes128GcmEncryptUpdateTransitionSub (void);
void HW_SCE_Aes128GcmEncryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
void HW_SCE_Aes128GcmDecryptUpdateAADSub (const uint32_t InData_DataA[], const uint32_t MAX_CNT);
void HW_SCE_Aes128GcmDecryptUpdateTransitionSub (void);
void HW_SCE_Aes128GcmDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
void HW_SCE_Aes192GcmDecryptUpdateAADSub (const uint32_t InData_DataA[], const uint32_t MAX_CNT);
void HW_SCE_Aes192GcmDecryptUpdateTransitionSub (void);
void HW_SCE_Aes192GcmDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
void HW_SCE_Aes256GcmEncryptUpdateAADSub (const uint32_t InData_DataA[], const uint32_t MAX_CNT);
void HW_SCE_Aes256GcmEncryptUpdateTransitionSub (void);
void HW_SCE_Aes256GcmEncryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
void HW_SCE_Aes256GcmDecryptUpdateAADSub (const uint32_t InData_DataA[], const uint32_t MAX_CNT);
void HW_SCE_Aes256GcmDecryptUpdateTransitionSub (void);
void HW_SCE_Aes256GcmDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
void HW_SCE_Aes128EncryptDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
void HW_SCE_Aes256EncryptDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
void HW_SCE_Aes192GcmEncryptUpdateTransitionSub (void);
void HW_SCE_Aes128CcmEncryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
void HW_SCE_Aes128CcmDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128GcmEncryptFinalSub(const uint32_t InData_Text[], const uint32_t InData_TextLen[], const uint32_t InData_DataALen[], uint32_t OutData_Text[], uint32_t OutData_DataT[]);
fsp_err_t HW_SCE_Aes128GcmEncryptInitSub(const uint32_t InData_KeyType[], const uint32_t InData_DataType[], const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_IV[], const uint32_t InData_SeqNum[]);
fsp_err_t HW_SCE_Aes128GcmDecryptFinalSub(const uint32_t InData_Text[], const uint32_t InData_TextLen[], const uint32_t InData_DataALen[], const uint32_t InData_DataT[], const uint32_t InData_DataTLen[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Aes128GcmDecryptInitSub(const uint32_t InData_KeyType[], const uint32_t InData_DataType[], const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_IV[], const uint32_t InData_SeqNum[]);
fsp_err_t HW_SCE_Aes192GcmDecryptFinalSub(const uint32_t InData_Text[], const uint32_t InData_TextLen[], const uint32_t InData_DataALen[], const uint32_t InData_DataT[], const uint32_t InData_DataTLen[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Aes192GcmDecryptInitSub(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
fsp_err_t HW_SCE_Aes256GcmEncryptFinalSub(const uint32_t InData_Text[], const uint32_t InData_TextLen[], const uint32_t InData_DataALen[], uint32_t OutData_Text[], uint32_t OutData_DataT[]);
fsp_err_t HW_SCE_Aes256GcmEncryptInitSub(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
fsp_err_t HW_SCE_Aes256GcmDecryptFinalSub(const uint32_t InData_Text[], const uint32_t InData_TextLen[], const uint32_t InData_DataALen[], const uint32_t InData_DataT[], const uint32_t InData_DataTLen[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Aes256GcmDecryptInitSub(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
fsp_err_t HW_SCE_LoadHukSub(const uint32_t InData_LC[]);
fsp_err_t HW_SCE_Aes128CmacFinalSub(const uint32_t InData_Cmd[], const uint32_t InData_Text[], const uint32_t InData_DataT[], const uint32_t InData_DataTLen[], uint32_t OutData_DataT[]);
fsp_err_t HW_SCE_Aes128CmacInitSub(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[]);
void HW_SCE_Aes128CmacUpdateSub(const uint32_t InData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256CmacFinalSub(const uint32_t InData_Cmd[], const uint32_t InData_Text[], const uint32_t InData_DataT[], const uint32_t InData_DataTLen[], uint32_t OutData_DataT[]);
fsp_err_t HW_SCE_Aes256CmacInitSub(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[]);
void HW_SCE_Aes256CmacUpdateSub(const uint32_t InData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128EncryptDecryptFinalSub(void);
fsp_err_t HW_SCE_Aes128EncryptDecryptInitSub (const uint32_t InData_KeyType[], const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
fsp_err_t HW_SCE_Aes256EncryptDecryptFinalSub(void);
fsp_err_t HW_SCE_Aes256EncryptDecryptInitSub (const uint32_t InData_KeyType[], const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
fsp_err_t HW_SCE_GenerateRandomNumberSub (uint32_t OutData_Text[]);
fsp_err_t HW_SCE_GenerateOemKeyIndexSub (const uint32_t InData_KeyType[], const uint32_t InData_Cmd[], const uint32_t InData_SharedKeyIndex[], const uint32_t InData_SessionKey[], const uint32_t InData_IV[], const uint32_t InData_InstData[], uint32_t OutData_KeyIndex[]);
fsp_err_t HW_SCE_OemKeyIndexValidationSub (const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[]);
fsp_err_t HW_SCE_SelfCheck1Sub(void);
fsp_err_t HW_SCE_SelfCheck2Sub(void);
void HW_SCE_Aes192GcmEncryptUpdateAADSub(const uint32_t InData_DataA[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes192GcmEncryptFinalSub(const uint32_t InData_Text[], const uint32_t InData_TextLen[], const uint32_t InData_DataALen[], uint32_t OutData_Text[], uint32_t OutData_DataT[]);
fsp_err_t HW_SCE_Aes192GcmEncryptInitSub(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
void HW_SCE_Aes192GcmEncryptUpdateSub(const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes192CmacFinalSub(const uint32_t InData_Cmd[], const uint32_t InData_Text[], const uint32_t InData_DataT[], const uint32_t InData_DataTLen[], uint32_t OutData_DataT[]);
fsp_err_t HW_SCE_Aes192CmacInitSub(const uint32_t InData_KeyIndex[]);
void HW_SCE_Aes192CmacUpdateSub(const uint32_t InData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes192EncryptDecryptFinalSub(void);
fsp_err_t HW_SCE_Aes192EncryptDecryptInitSub (const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
void HW_SCE_Aes192EncryptDecryptUpdateSub (const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128CcmEncryptFinalSub(const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t OutData_MAC[]);
fsp_err_t HW_SCE_Aes128CcmEncryptInitSub(const uint32_t InData_KeyType[], const uint32_t InData_DataType[], const uint32_t InData_Cmd[], const uint32_t InData_TextLen[], const uint32_t InData_KeyIndex[], const uint32_t InData_IV[], const uint32_t InData_Header[], const uint32_t InData_SeqNum[], const uint32_t Header_Len);
fsp_err_t HW_SCE_Aes128CcmDecryptFinalSub(const uint32_t InData_Text[], const uint32_t InData_MAC[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Aes128CcmDecryptInitSub(const uint32_t InData_KeyType[], const uint32_t InData_DataType[], const uint32_t InData_Cmd[], const uint32_t InData_TextLen[], const uint32_t InData_MACLength[], const uint32_t InData_KeyIndex[], const uint32_t InData_IV[], const uint32_t InData_Header[], const uint32_t InData_SeqNum[], const uint32_t Header_Len);
fsp_err_t HW_SCE_Aes256CcmEncryptFinalSub(const uint32_t InData_Text[], const uint32_t InData_TextLen[], uint32_t OutData_Text[], uint32_t OutData_MAC[]);
fsp_err_t HW_SCE_Aes256CcmEncryptInitSub(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[], const uint32_t InData_IV[], const uint32_t InData_Header[], const uint32_t Header_Len);
void HW_SCE_Aes256CcmEncryptUpdateSub(const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256CcmDecryptFinalSub(const uint32_t InData_Text[], const uint32_t InData_TextLen[], const uint32_t InData_MAC[], const uint32_t InData_MACLength[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Aes256CcmDecryptInitSub(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[], const uint32_t InData_IV[], const uint32_t InData_Header[], const uint32_t Header_Len);
void HW_SCE_Aes256CcmDecryptUpdateSub(const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes192CcmEncryptFinalSub(const uint32_t InData_Text[], const uint32_t InData_TextLen[], uint32_t OutData_Text[], uint32_t OutData_MAC[]);
fsp_err_t HW_SCE_Aes192CcmEncryptInitSub(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[], const uint32_t InData_Header[], const uint32_t Header_Len);
void HW_SCE_Aes192CcmEncryptUpdateSub(const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes192CcmDecryptFinalSub(const uint32_t InData_Text[], const uint32_t InData_TextLen[], const uint32_t InData_MAC[], const uint32_t InData_MACLength[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Aes192CcmDecryptInitSub(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[], const uint32_t InData_Header[], const uint32_t Header_Len);
void HW_SCE_Aes192CcmDecryptUpdateSub(const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128XtsEncryptFinalSub(const uint32_t InData_TextBitLen[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Aes128XtsEncryptInitSub(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
void HW_SCE_Aes128XtsEncryptUpdateSub(const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128XtsDecryptFinalSub(const uint32_t InData_TextBitLen[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Aes128XtsDecryptInitSub(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
void HW_SCE_Aes128XtsDecryptUpdateSub(const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256XtsEncryptFinalSub(const uint32_t InData_TextBitLen[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Aes256XtsEncryptInitSub(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
void HW_SCE_Aes256XtsEncryptUpdateSub(const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256XtsDecryptFinalSub(const uint32_t InData_TextBitLen[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Aes256XtsDecryptInitSub(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
void HW_SCE_Aes256XtsDecryptUpdateSub(const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128GctrFinalSub(void);
fsp_err_t HW_SCE_Aes128GctrInitSub(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
void HW_SCE_Aes128GctrUpdateSub(const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes256GctrFinalSub(void);
fsp_err_t HW_SCE_Aes256GctrInitSub(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
void HW_SCE_Aes256GctrUpdateSub(const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes192GctrFinalSub(void);
fsp_err_t HW_SCE_Aes192GctrInitSub(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
void HW_SCE_Aes192GctrUpdateSub(const uint32_t InData_Text[], uint32_t OutData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_GhashSub (const uint32_t InData_HV[], const uint32_t InData_IV[], const uint32_t InData_Text[], uint32_t OutData_DataT[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_ShaGenerateMessageDigestSub (const uint32_t InData_HashType[], const uint32_t InData_Cmd[], const uint32_t InData_Msg[], const uint32_t InData_MsgLen[], const uint32_t InData_State[], uint32_t OutData_MsgDigest[], uint32_t OutData_State[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_GenerateAes128RandomKeyIndexSub (uint32_t OutData_KeyIndex[]);
fsp_err_t HW_SCE_GenerateAes192RandomKeyIndexSub (uint32_t OutData_KeyIndex[]);
fsp_err_t HW_SCE_GenerateAes256RandomKeyIndexSub (uint32_t OutData_KeyIndex[]);
fsp_err_t HW_SCE_GenerateAes128XtsRandomKeyIndexSub (uint32_t OutData_KeyIndex[]);
fsp_err_t HW_SCE_GenerateAes256XtsRandomKeyIndexSub (uint32_t OutData_KeyIndex[]);
fsp_err_t HW_SCE_Rsa1024ModularExponentEncryptSub(const uint32_t InData_KeyIndex[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Rsa1024ModularExponentDecryptSub(const uint32_t InData_KeyIndex[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Rsa2048ModularExponentEncryptSub(const uint32_t InData_KeyIndex[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Rsa2048ModularExponentDecryptSub(const uint32_t InData_KeyIndex[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Rsa3072ModularExponentEncryptSub(const uint32_t InData_KeyIndex[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Rsa3072ModularExponentDecryptSub(const uint32_t InData_KeyIndex[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Rsa4096ModularExponentEncryptSub(const uint32_t InData_KeyIndex[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_Rsa4096ModularExponentDecryptSub(const uint32_t InData_KeyIndex[], const uint32_t InData_Text[], uint32_t OutData_Text[]);
fsp_err_t HW_SCE_EcdsaSignatureGenerateSub(const uint32_t InData_CurveType[], const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_MsgDgst[], uint32_t OutData_Signature[]);
fsp_err_t HW_SCE_EcdsaSignatureVerificationSub(const uint32_t InData_CurveType[], const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_MsgDgst[], const uint32_t InData_Signature[]);
fsp_err_t HW_SCE_Ecc256ScalarMultiplicationSub(const uint32_t InData_CurveType[], const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_PubKey[], uint32_t OutData_R[]);
fsp_err_t HW_SCE_EcdsaP384SignatureGenerateSub(const uint32_t InData_CurveType[], const uint32_t InData_KeyIndex[], const uint32_t InData_MsgDgst[], uint32_t OutData_Signature[]);
fsp_err_t HW_SCE_EcdsaP384SignatureVerificationSub(const uint32_t InData_CurveType[], const uint32_t InData_KeyIndex[], const uint32_t InData_MsgDgst[], const uint32_t InData_Signature[]);
fsp_err_t HW_SCE_Ecc384ScalarMultiplicationSub(const uint32_t InData_CurveType[], const uint32_t InData_KeyIndex[], const uint32_t InData_PubKey[], uint32_t OutData_R[]);
fsp_err_t HW_SCE_EcdsaP512SignatureGenerateSub(const uint32_t InData_KeyIndex[], const uint32_t InData_MsgDgst[], uint32_t OutData_Signature[]);
fsp_err_t HW_SCE_EcdsaP512SignatureVerificationSub(const uint32_t InData_KeyIndex[], const uint32_t InData_MsgDgst[], const uint32_t InData_Signature[]);
fsp_err_t HW_SCE_Ecc512ScalarMultiplicationSub(const uint32_t InData_KeyIndex[], const uint32_t InData_PubKey[], uint32_t OutData_R[]);
fsp_err_t HW_SCE_EcdsaP521SignatureGenerateSub(const uint32_t InData_KeyIndex[], const uint32_t InData_MsgDgst[], uint32_t OutData_Signature[]);
fsp_err_t HW_SCE_EcdsaP521SignatureVerificationSub(const uint32_t InData_KeyIndex[], const uint32_t InData_MsgDgst[], const uint32_t InData_Signature[]);
fsp_err_t HW_SCE_Ecc521ScalarMultiplicationSub(const uint32_t InData_KeyIndex[], const uint32_t InData_PubKey[], uint32_t OutData_R[]);
fsp_err_t HW_SCE_GenerateEccRandomKeyIndexSub(const uint32_t InData_CurveType[], const uint32_t InData_Cmd[], uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);
fsp_err_t HW_SCE_GenerateEccP384RandomKeyIndexSub(const uint32_t InData_CurveType[], uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);
fsp_err_t HW_SCE_GenerateEccP512RandomKeyIndexSub(uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);
fsp_err_t HW_SCE_GenerateEccP521RandomKeyIndexSub(uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);
fsp_err_t HW_SCE_Sha256HmacInitSub(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[], const uint32_t InData_Cmd[], const uint32_t InData_MsgLen[]);
void HW_SCE_Sha256HmacUpdateSub(const uint32_t InData_Msg[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Sha256HmacFinalSub(const uint32_t InData_Cmd[], const uint32_t InData_MAC[], const uint32_t InData_MACLength[], uint32_t OutData_MAC[]);
fsp_err_t HW_SCE_Sha224HmacInitSub(const uint32_t InData_KeyIndex[], const uint32_t InData_MsgLen[]);
void HW_SCE_Sha224HmacUpdateSub(const uint32_t InData_Msg[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Sha224HmacFinalSub (const uint32_t InData_Cmd[], const uint32_t InData_MAC[], const uint32_t InData_MACLength[], uint32_t OutData_MAC[]);
fsp_err_t HW_SCE_IntegrityCheckSub(const uint32_t InData_Data[], const uint32_t InData_DataLen[], const uint32_t InData_MAC[], const uint32_t MAX_CNT);

uint32_t change_endian_long (uint32_t data);

fsp_err_t HW_SCE_Aes128CmacInit(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[]);
fsp_err_t HW_SCE_Aes192CmacInit(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[]);
fsp_err_t HW_SCE_Aes256CmacInit(const uint32_t InData_KeyType[], const uint32_t InData_KeyIndex[]);
void HW_SCE_Aes128CmacUpdate(const uint32_t InData_Text[], const uint32_t MAX_CNT);
void HW_SCE_Aes192CmacUpdate(const uint32_t InData_Text[], const uint32_t MAX_CNT);
void HW_SCE_Aes256CmacUpdate(const uint32_t InData_Text[], const uint32_t MAX_CNT);
fsp_err_t HW_SCE_Aes128CmacFinal(const uint32_t InData_Cmd[],
                                 const uint32_t InData_Text[],
                                 const uint32_t InData_DataT[],
                                 const uint32_t InData_DataTLen[],
                                 uint32_t       OutData_DataT[]);
fsp_err_t HW_SCE_Aes192CmacFinal(const uint32_t InData_Cmd[],
                                 const uint32_t InData_Text[],
                                 const uint32_t InData_DataT[],
                                 const uint32_t InData_DataTLen[],
                                 uint32_t       OutData_DataT[]);
fsp_err_t HW_SCE_Aes256CmacFinal(const uint32_t InData_Cmd[],
                                 const uint32_t InData_Text[],
                                 const uint32_t InData_DataT[],
                                 const uint32_t InData_DataTLen[],
                                 uint32_t       OutData_DataT[]);

#endif /* HW_SCE_RA_PRIVATE_HEADER_FILE */
