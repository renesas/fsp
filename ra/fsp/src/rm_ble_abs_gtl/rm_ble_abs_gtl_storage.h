/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_BLE_ABS_GTL_STORAGE_H
#define RM_BLE_ABS_GTL_STORAGE_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_ble_gtl_security.h"
#include <stdint.h>
#include <stdlib.h>
#include "r_ble_api.h"
#include "FreeRTOS.h"
#include "task.h"
#ifdef ENABLE_STORAGE
 #include "rm_vee_flash.h"
 #include "rm_ble_abs_gtl_cfg.h"
#endif

/* Security data management information */
typedef struct rm_ble_abs_gtl_strg_mng_info
{
    uint32_t magic_num;
    uint8_t  bond_cnt;
    uint8_t  padding[3];
} rm_ble_abs_gtl_strg_mng_info_t;

/* Local device security data */
typedef struct rm_ble_abs_gtl_strg_sec_data
{
    uint8_t           loc_irk[BLE_GAP_IRK_SIZE];
    uint8_t           loc_csrk[BLE_GAP_CSRK_SIZE];
    st_ble_dev_addr_t loc_ident_addr;
    uint8_t           padding[1];      // Padding for alignment to ensure proper memory layout
} rm_ble_abs_gtl_strg_sec_data_t;

/***********************************************************************************************************************
 * Boot structure for BLE ABS GTL storage
 **********************************************************************************************************************/
typedef struct rm_ble_abs_gtl_strg_boot
{
    rm_ble_abs_gtl_strg_mng_info_t sec_data_mng_info; // Security data management information
    rm_ble_abs_gtl_strg_sec_data_t loc_dev_sec_data;  // Local device security data
} rm_ble_abs_gtl_strg_boot;

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define CRYPTO_ENABLED                                // Uncomment this line to enable cryptographic operations
#define REF_DATA_IDX                        (10U)     // Reference data index
#define DEFAULT_ID                          (65535U)
#define REF_DATA_SIZE                       (48U)
#define BLE_ABS_SECURE_DATA_MAGIC_NUMBER    (0x12345678)
#define ZERO_VALUE                          (0x00)
#define BOND_DATA_SINGLE                    sizeof(sec_ble_gap_bond_info_t)
#define BOND_DATA_TL_SIZE                   (BLE_ABS_CFG_NUMBER_BONDING * BOND_DATA_SINGLE) // Maximum size for bond data)

/***********************************************************************************************************************
 * Public Function Prototypes
 ***********************************************************************************************************************/
fsp_err_t rm_ble_abs_gtl_storage_init(uint8_t * num_of_entries);
fsp_err_t rm_ble_abs_gtl_read_bond_data(uint8_t num_of_entries, uint8_t ** addr, uint16_t * data_size);
fsp_err_t rm_ble_abs_gtl_storage_write_bond_data(uint8_t idx, uint8_t * data_addr, uint16_t data_size);
fsp_err_t rm_ble_abs_gtl_storage_update_bond_num(uint8_t act_num_bond);
fsp_err_t rm_ble_abs_gtl_storage_rel_buf(uint8_t * p_sec_data);
fsp_err_t rm_ble_abs_gtl_storage_format_operation(void);
fsp_err_t rm_ble_abs_gtl_storage_refresh_operation(void);

#ifdef ENABLE_STORAGE
void vee_callback(rm_vee_callback_args_t * p_args);

#endif
fsp_err_t rm_ble_abs_gtl_storage_rem_all_bond_data(void);
fsp_err_t rm_ble_abs_gtl_storage_rem_specific_bond_data(uint8_t idx);
fsp_err_t rm_ble_abs_gtl_storage_get_addr(st_ble_dev_addr_t * bd_address);
fsp_err_t rm_ble_abs_gtl_storage_set_addr(st_ble_dev_addr_t * bd_address);
fsp_err_t wr_timeout(uint8_t delay_ms);
fsp_err_t rm_ble_abs_gtl_storage_upd_crypto_key(uint8_t * key, uint8_t key_size);

#endif                                 // End of include guard
