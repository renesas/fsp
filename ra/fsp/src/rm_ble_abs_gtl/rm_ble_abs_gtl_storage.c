/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 ***********************************************************************************************************************/
#include "rm_ble_abs_gtl_storage.h"
#ifdef CRYPTO_ENABLED
 #include "rm_ble_abs_gtl_sw_aes_api.h"
#endif

/***********************************************************************************************************************
 * NOTES
 * ----------------------------------------------------
 * Both variables described below are used in the VEE driver.
 * User needs to set appropriate names using the Configurator.
 * These are stored in hal_data.h
 * g_vee_ctrl is the control structure for the VEE driver
 * g_vee_cfg is the configuration structure for the VEE driver
 *
 * The name of the VEE driver instance must be set in the Configurator.
 * ra_gen\ble_thread.h
 * the name for the should be set to: extern const rm_vee_instance_t g_vee;
 ***********************************************************************************************************************/
#ifdef ENABLE_STORAGE

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

/* capture callback event.*/
static volatile bool g_write_flag = false;

/* Capture the vee_flash status*/
rm_vee_status_t p_status = {(rm_vee_state_t) ZERO_VALUE, ZERO_VALUE, ZERO_VALUE, ZERO_VALUE};

extern rm_vee_flash_instance_ctrl_t g_vee_ctrl;
extern rm_vee_cfg_t                 g_vee_cfg;

 #ifdef CRYPTO_ENABLED
extern crypto_env_t rm_ble_abs_gtl_aes_env;
uint8_t             usr_key[16] =
{
    0x3d, 0xaf, 0xba, 0x42, 0x9d, 0x9e, 0xb4, 0x30, 0xb4, 0x22, 0xda, 0x80, 0x2c, 0x9f, 0xac, 0x41
};
 #endif

/*******************************************************************************************************************//**
 *  Wrappper for memory allocate function.
 *
 * @param[in]  size     Size of memory to be allocated (in bytes)
 * @retval NULL         Memory not allocated
 * @retval Address      Address of memory allocated
 **********************************************************************************************************************/
static void * rm_ble_gtl_malloc (uint32_t size)
{
 #if (BSP_CFG_RTOS == 2)               /* FreeRTOS */
    return pvPortMalloc(size);
 #elif (BSP_CFG_RTOS == 0)             /* Baremetal */
    void * p_mem = NULL;
    p_mem = malloc(size);
    memset(p_mem, 0, size);

    return p_mem;
 #else

    return NULL;                       // ThreadX is not supported, so this is a placeholder
 #endif
}

/*******************************************************************************************************************//**
 *  Wrapper for free memory allocation function.
 *
 * @param[in]  p_mem    Pointer to memory to be freed
 **********************************************************************************************************************/
static void rm_ble_gtl_free (void * p_mem)
{
 #if (BSP_CFG_RTOS == 2)               /* FreeRTOS */
    vPortFree(p_mem);
 #elif (BSP_CFG_RTOS == 0)             /* Baremetal */
    free(p_mem);
 #else

    return NULL;                       // ThreadX is not supported, so this is a placeholder
 #endif
}

/*******************************************************************************************************************//**
 *  Generate a blocking delay.
 *
 * @param[in]  ms       Length of delay in milliseconds
 **********************************************************************************************************************/
static void rm_ble_gtl_delay (uint32_t ms)
{
 #if (BSP_CFG_RTOS == 2)               /* FreeRTOS */
    vTaskDelay(pdMS_TO_TICKS(ms));
 #elif (BSP_CFG_RTOS == 1)             /* ThreadX */
    tx_thread_sleep((ms * TX_TIMER_TICKS_PER_SECOND) / R_BLE_GTL_MS_PER_SECOND);
 #elif (BSP_CFG_RTOS == 0)             /* Baremetal */
    R_BSP_SoftwareDelay(ms, BSP_DELAY_UNITS_MILLISECONDS);
 #endif
}

/*******************************************************************************************************************//**
 * Wait for the Virtual EEPROM callback to indicate that it has finished writing data
 * and vee flash is in ready state.
 * @retval     fsp_err_t   Status of the operation.
 * @note        This function waits for the Virtual EEPROM callback to indicate that it has finished writing data
 * and vee flash is in ready state. If the callback event does not occur within a certain time, it returns a timeout error.
 **********************************************************************************************************************/
fsp_err_t wr_timeout (uint8_t delay_ms)
{
    fsp_err_t err            = FSP_SUCCESS;
    int32_t   write_time_out = delay_ms;

    /* Wait for the Virtual EEPROM callback to indicate that it has finished writing data
     * and vee flash is in ready state. */
    do
    {
        /* Delay 1ms each time */
        rm_ble_gtl_delay(1);

        /* Get the current status of the driver.*/
        err = RM_VEE_FLASH_StatusGet(&g_vee_ctrl, &p_status);
        if (FSP_SUCCESS != err)
        {
            return err;
        }
    } while ((RM_VEE_STATE_READY != p_status.state) && (ZERO_VALUE < --write_time_out));

    if (ZERO_VALUE == write_time_out)
    {
        return FSP_ERR_TIMEOUT;
    }

    /* Reset the flag.*/
    g_write_flag = false;

    return err;
}

/*******************************************************************************************************************//**
 * @brief       This functions performs refresh on vee_flash.
 * @param[IN]   None
 * @retval      FSP_SUCCESS                  Upon successful refresh
 * @retval      Any Other Error code apart from FSP_SUCCESS
 **********************************************************************************************************************/
fsp_err_t rm_ble_abs_gtl_storage_refresh_operation (void)
{
    fsp_err_t err             = FSP_SUCCESS;
    int32_t   status_time_out = INT32_MAX;

    /* force refresh and wait to complete */
    err = RM_VEE_FLASH_Refresh(&g_vee_ctrl);
    if (FSP_SUCCESS != err)
    {
        return err;
    }

    do
    {
        /* Get the current status of the driver.*/
        err = RM_VEE_FLASH_StatusGet(&g_vee_ctrl, &p_status);
        if (FSP_SUCCESS != err)
        {
            return err;
        }
    } while ((RM_VEE_STATE_READY != p_status.state) && (ZERO_VALUE < --status_time_out));

    if (ZERO_VALUE == status_time_out)
    {
        err = FSP_ERR_TIMEOUT;
    }
    else
    {
        /* Reset the flag.*/
        g_write_flag = false;
    }

    return err;
}

/**********************************************************************************************************************
 *  Executed at start of the application.
 *  This function initializes the VEE driver and formats the flash if necessary.
 * @param[in]  none
 * @param[out] num_of_entries  Number of entries in the flash.
 **********************************************************************************************************************/
fsp_err_t rm_ble_abs_gtl_storage_init (uint8_t * num_of_entries)
{
    fsp_err_t                err = FSP_SUCCESS;
    uint8_t                  dummy_boot_data[sizeof(rm_ble_abs_gtl_strg_boot)] = {0};
    uint8_t                * p_ref_data = NULL;
    rm_ble_abs_gtl_strg_boot boot_data;

    /* Open the RM_VEE_FLASH driver module.*/
    err = RM_VEE_FLASH_Open(&g_vee_ctrl, &g_vee_cfg);
    if ((FSP_SUCCESS == err) || (FSP_ERR_ALREADY_OPEN == err))
    {
        // Read the boot sector data from flash
        RM_VEE_FLASH_StatusGet(&g_vee_ctrl, &p_status);
        err = RM_VEE_FLASH_RecordPtrGet(&g_vee_ctrl, REF_DATA_IDX, (uint8_t **) &p_ref_data, NULL);
        memcpy(&boot_data, p_ref_data, sizeof(rm_ble_abs_gtl_strg_boot));

 #ifdef CRYPTO_ENABLED
        rm_ble_abs_gtl_aes_init(NULL, NULL, NULL); // all null use default
        rm_ble_abs_gtl_aes_env.keyset_func(usr_key, NULL, AES_MODE_128_);
 #endif

        // Check if the magic number is valid
        if ((boot_data.sec_data_mng_info.magic_num != BLE_ABS_SECURE_DATA_MAGIC_NUMBER) || (err != FSP_SUCCESS))
        {
            // The flash has Not been formatted yet or the magic number is not valid.
            err = RM_VEE_FLASH_Format(&g_vee_ctrl, NULL);
            if (FSP_SUCCESS != err)
            {
                return err;
            }

            // Init the reference sector data
            memset(dummy_boot_data, ZERO_VALUE, sizeof(rm_ble_abs_gtl_strg_boot));
            err = RM_VEE_FLASH_StatusGet(&g_vee_ctrl, &p_status);
            if (FSP_SUCCESS != err)
            {
                return err;
            }

            err =
                RM_VEE_FLASH_RecordWrite(&g_vee_ctrl, REF_DATA_IDX, dummy_boot_data, sizeof(rm_ble_abs_gtl_strg_boot));
            if (FSP_SUCCESS != err)
            {
                return err;
            }

            err = wr_timeout(5);
            if (FSP_SUCCESS != err)
            {
                return err;
            }

            *num_of_entries = 0;       // Set the number of entries to 0 since the flash has been formatted
        }
        else
        {
            *num_of_entries = boot_data.sec_data_mng_info.bond_cnt;
        }
    }

    return err;
}

/**********************************************************************************************************************
 * Read bonding information from flash.
 * @param[in]  num_of_entries   Number of entries to read (retrieved from the security data management information).
 * @param[out] addr             Address to store the read data.
 * @retval     fsp_err_t        Status of the operation.
 **********************************************************************************************************************/
fsp_err_t rm_ble_abs_gtl_read_bond_data (uint8_t num_of_entries, uint8_t ** addr, uint16_t * data_size)
{
    fsp_err_t err              = FSP_SUCCESS;
    void    * p_record_data    = NULL;
    uint8_t * p_ref_data       = rm_ble_gtl_malloc(BOND_DATA_TL_SIZE);
    uint8_t * p_ref_data_start = NULL;
    uint32_t  out_len          = 0;
    *data_size = 0;
 #ifdef CRYPTO_ENABLED
    uint8_t decrypted[BOND_DATA_SINGLE] = {0}; // Buffer to hold decrypted data
 #endif
    if (NULL == p_ref_data)
    {
        return FSP_ERR_OUT_OF_MEMORY;          // Memory allocation failed
    }

    p_ref_data_start = p_ref_data;             // Get starting address

    // Check if the number of entries exceeds the maximum allowed
    if (num_of_entries > BLE_ABS_CFG_NUMBER_BONDING)
    {
        rm_ble_gtl_free(p_ref_data);
        p_ref_data_start = NULL;

        return FSP_ERR_INVALID_ARGUMENT;
    }

    for (uint32_t rec_id = 1; rec_id <= num_of_entries; rec_id++)
    {
        err = RM_VEE_FLASH_RecordPtrGet(&g_vee_ctrl, rec_id, (uint8_t **) &p_record_data, &out_len);
        if (FSP_SUCCESS == err)
        {
 #ifdef CRYPTO_ENABLED

            // The bond data len cannot exceed 254 bytes.
            err = rm_ble_abs_gtl_aes_env.decrypt_func(decrypted,
                                                      sizeof(decrypted),
                                                      (uint8_t *) p_record_data,
                                                      out_len,
                                                      usr_key);
            out_len -= AES_BLOCK_SIZE;
            memcpy(p_ref_data, decrypted, out_len);
 #else
            memcpy(p_ref_data, p_record_data, out_len);
 #endif
            p_ref_data += out_len;
            *data_size += (uint16_t) out_len; // Update the total length of data read
        }
        else
        {
            rm_ble_gtl_free(p_ref_data);
            p_ref_data_start = NULL;

            return err;
        }
    }

    *addr = p_ref_data_start;          // Update address to point to the start of the data

    return err;
}

/***********************************************************************************************************************
 * This function releases the buffer allocated for bonding information.
 * @param[in]  p_sec_data   Pointer to the security data buffer to be released.
 **********************************************************************************************************************/
fsp_err_t rm_ble_abs_gtl_storage_rel_buf (uint8_t * p_sec_data)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ble_gtl_free(p_sec_data);

    return err;
}

/***********************************************************************************************************************
 * This function writes the bonding information to a Virtual EEPROM Record.
 * @param[in]  idx         Index of the record to write.
 * @param[in]  data_addr   Pointer to the data to write.
 * @param[in]  data_size   Size of the data to write.
 * @retval     fsp_err_t   Status of the operation.
 * @note        This function waits for the Virtual EEPROM callback to indicate that it has finished writing data
 * and vee flash is in ready state. If the callback event does not occur within a certain time, it returns a timeout error.
 **********************************************************************************************************************/
fsp_err_t rm_ble_abs_gtl_storage_write_bond_data (uint8_t idx, uint8_t * data_addr, uint16_t data_size)
{
    fsp_err_t err = FSP_SUCCESS;
    if (data_size != BOND_DATA_SINGLE)
    {
        return FSP_ERR_INVALID_ARGUMENT;
    }

 #ifdef CRYPTO_ENABLED
    uint8_t * plain_data      = rm_ble_gtl_malloc(data_size);
    uint8_t * cipher_datatext = rm_ble_gtl_malloc(data_size + AES_BLOCK_SIZE);
    memset(plain_data, ZERO_VALUE, data_size);
    memset(cipher_datatext, ZERO_VALUE, data_size);

    memcpy(plain_data, data_addr, data_size);
    err = rm_ble_abs_gtl_aes_env.encrypt_func(cipher_datatext,
                                              data_size + AES_BLOCK_SIZE,
                                              plain_data,
                                              data_size,
                                              usr_key,
                                              NULL); // NULL = use default IV

    err = RM_VEE_FLASH_RecordWrite(&g_vee_ctrl, idx, cipher_datatext, data_size + AES_BLOCK_SIZE);
 #else

    /* Write the data to a Virtual EEPROM Record. */
    err = RM_VEE_FLASH_RecordWrite(&g_vee_ctrl, idx, data_addr, data_size);
 #endif
    if (FSP_SUCCESS != err)
    {
 #ifdef CRYPTO_ENABLED
        rm_ble_gtl_free(plain_data);
        rm_ble_gtl_free(cipher_datatext);
 #endif

        return err;
    }

    // Block until the write operation is complete, else the buffers may be freed too early.
    err = wr_timeout(5);
 #ifdef CRYPTO_ENABLED
    rm_ble_gtl_free(plain_data);
    rm_ble_gtl_free(cipher_datatext);
 #endif

    return err;
}

/***********************************************************************************************************************
 * Update the number of bonds in the reference data.
 * This function updates the bond count in the reference data and writes it back to flash.
 * @param[in]  act_num_bond   The actual number of bonds to update.
 * @retval     fsp_err_t      Status of the operation.
 **********************************************************************************************************************/
fsp_err_t rm_ble_abs_gtl_storage_update_bond_num (uint8_t act_num_bond)
{
    fsp_err_t                err            = FSP_SUCCESS;
    rm_ble_abs_gtl_strg_boot boot_data      = {0};
    uint8_t   ref_data_write[REF_DATA_SIZE] = {0};
    uint8_t * p_ref_data_read               = NULL;

    /* Get the reference data pointer */
    err = RM_VEE_FLASH_RecordPtrGet(&g_vee_ctrl, REF_DATA_IDX, &p_ref_data_read, NULL);
    if (FSP_SUCCESS != err)
    {
        return err;
    }

    /* Read the existing boot data */
    memcpy(&boot_data, p_ref_data_read, sizeof(rm_ble_abs_gtl_strg_boot));

    /* Update the bond count */
    boot_data.sec_data_mng_info.bond_cnt = act_num_bond;

    if ((boot_data.sec_data_mng_info.magic_num != BLE_ABS_SECURE_DATA_MAGIC_NUMBER) && (act_num_bond == 1))
    {
        /* If the magic number is not valid, set it to the correct value */
        boot_data.sec_data_mng_info.magic_num = BLE_ABS_SECURE_DATA_MAGIC_NUMBER;
    }
    else
    {
        /* If the magic number is valid, do nothing */
    }

    /* Write the updated boot data back to flash */
    memcpy(&ref_data_write, &boot_data, REF_DATA_SIZE);
    err = RM_VEE_FLASH_StatusGet(&g_vee_ctrl, &p_status);
    if (FSP_SUCCESS != err)
    {
        return err;
    }

    err = RM_VEE_FLASH_RecordWrite(&g_vee_ctrl, REF_DATA_IDX, ref_data_write, REF_DATA_SIZE);
    if (FSP_SUCCESS != err)
    {
        return err;
    }

    err = wr_timeout(5);

    return err;
}

/***********************************************************************************************************************
 *  @brief        User defined callback function
 *  @param[IN]    p_args
 *  @retval       None
 **********************************************************************************************************************/
void vee_callback (rm_vee_callback_args_t * p_args)
{
    if ((NULL != p_args) && (RM_VEE_STATE_READY == p_args->state))
    {
        g_write_flag = true;
    }
}

/***********************************************************************************************************************
 *  @brief        This function formats the flash memory.
 *  @note         It opens the VEE driver, performs a manual format operation, and checks the status of the driver.
 *  @retval       fsp_err_t   Status of the operation.
 **********************************************************************************************************************/
fsp_err_t rm_ble_abs_gtl_storage_format_operation (void)
{
    fsp_err_t err      = FSP_SUCCESS;
    uint8_t   ref_data = ZERO_VALUE;

    err = RM_VEE_FLASH_Open(&g_vee_ctrl, &g_vee_cfg);
    if ((FSP_SUCCESS != err) && (FSP_ERR_ALREADY_OPEN != err))
    {
        return err;
    }

    /* Start a manual format operation.*/
    err = RM_VEE_FLASH_Format(&g_vee_ctrl, &ref_data);
    if (FSP_SUCCESS != err)
    {
        return err;
    }

    /* Get the current status of the driver.*/
    err = RM_VEE_FLASH_StatusGet(&g_vee_ctrl, &p_status);
    if (FSP_SUCCESS != err)
    {
        return err;
    }

    /* Compare Last ID written with Default ID.*/
    if (DEFAULT_ID == p_status.last_id)
    {
        // Format operation was successful
    }
    else
    {
        err = FSP_ERR_NOT_ERASED;
    }

    return err;
}

/***********************************************************************************************************************
 *  @brief        This function removes all bond data from the flash memory.
 *  @retval       fsp_err_t   Status of the operation.
 **********************************************************************************************************************/
fsp_err_t rm_ble_abs_gtl_storage_rem_all_bond_data (void)
{
    fsp_err_t                err            = FSP_SUCCESS;
    rm_ble_abs_gtl_strg_boot boot_data      = {0};
    uint8_t   ref_data_write[REF_DATA_SIZE] = {0};
    uint8_t * p_ref_data_read               = NULL;

    /* Get the reference data pointer */
    err = RM_VEE_FLASH_RecordPtrGet(&g_vee_ctrl, REF_DATA_IDX, &p_ref_data_read, NULL);
    if (FSP_SUCCESS != err)
    {
        return err;
    }

    /* Read the existing boot data */
    memcpy(&boot_data, p_ref_data_read, sizeof(rm_ble_abs_gtl_strg_boot));

    /* Update the bond count */
    boot_data.sec_data_mng_info.bond_cnt = ZERO_VALUE;

    /* Format the flash */
    rm_ble_abs_gtl_storage_format_operation();

    /* Write the updated boot data back to flash */
    memcpy(&ref_data_write, &boot_data, REF_DATA_SIZE);
    err = RM_VEE_FLASH_RecordWrite(&g_vee_ctrl, REF_DATA_IDX, ref_data_write, REF_DATA_SIZE);
    if (FSP_SUCCESS != err)
    {
        return err;
    }

    err = wr_timeout(5);

    return err;
}

/***********************************************************************************************************************
 *  @brief        This function removes specific bond data from the flash memory.
 *  @param[in]    idx         Index of the bond data to remove.
 *  @retval       fsp_err_t   Status of the operation.
 **********************************************************************************************************************/
fsp_err_t rm_ble_abs_gtl_storage_rem_specific_bond_data (uint8_t idx)
{
    // Copy new DB from RAM
    // Update the bond count in the reference data
    FSP_PARAMETER_NOT_USED(idx);

    return FSP_SUCCESS;
}

/***********************************************************************************************************************
 *  @brief        This function retrieves the Bluetooth device address from the flash memory.
 *  @param[out]   bd_address  Pointer to store the Bluetooth device address.
 *  @retval       fsp_err_t   Status of the operation.
 **********************************************************************************************************************/
fsp_err_t rm_ble_abs_gtl_storage_get_addr (st_ble_dev_addr_t * bd_address)
{
    fsp_err_t                err             = FSP_SUCCESS;
    rm_ble_abs_gtl_strg_boot boot_data       = {0};
    uint8_t                * p_ref_data_read = NULL;

    /* Open the RM_VEE_FLASH driver module.*/
    err = RM_VEE_FLASH_Open(&g_vee_ctrl, &g_vee_cfg);
    if ((FSP_SUCCESS != err) || (FSP_ERR_ALREADY_OPEN == err))
    {
        return err;
    }

    /* Get the reference data pointer */
    err = RM_VEE_FLASH_RecordPtrGet(&g_vee_ctrl, REF_DATA_IDX, &p_ref_data_read, NULL);
    if (FSP_SUCCESS != err)
    {
        return err;
    }

    /* Read the existing boot data */
    memcpy(&boot_data, p_ref_data_read, sizeof(rm_ble_abs_gtl_strg_boot));
    if (boot_data.sec_data_mng_info.magic_num != BLE_ABS_SECURE_DATA_MAGIC_NUMBER)
    {
        err = FSP_ERR_NOT_FOUND;
        memset(bd_address, 0x00, BLE_BD_ADDR_LEN); // Clear the address
        return err;
    }

    /* Copy the address */
    memcpy(bd_address->addr, &boot_data.loc_dev_sec_data.loc_ident_addr.addr, BLE_BD_ADDR_LEN);
    bd_address->type = boot_data.loc_dev_sec_data.loc_ident_addr.type;

    return err;
}

/***********************************************************************************************************************
 * @brief        This function sets the Bluetooth device address in the flash memory.
 * @param[in]    bd_address  Pointer to the Bluetooth device address to set.
 * @retval       fsp_err_t   Status of the operation.
 **********************************************************************************************************************/
fsp_err_t rm_ble_abs_gtl_storage_set_addr (st_ble_dev_addr_t * bd_address)
{
    fsp_err_t                err            = FSP_SUCCESS;
    rm_ble_abs_gtl_strg_boot boot_data      = {0};
    uint8_t   ref_data_write[REF_DATA_SIZE] = {0};
    uint8_t * p_ref_data_read               = NULL;

    /* Open the RM_VEE_FLASH driver module.*/
    err = RM_VEE_FLASH_Open(&g_vee_ctrl, &g_vee_cfg);
    if ((FSP_SUCCESS != err) || (FSP_ERR_ALREADY_OPEN == err))
    {
        return err;
    }

    /* Get the reference data pointer */
    err = RM_VEE_FLASH_RecordPtrGet(&g_vee_ctrl, REF_DATA_IDX, &p_ref_data_read, NULL);
    if (FSP_SUCCESS != err)
    {
        return err;
    }

    /* Read the existing boot data */
    memcpy(&boot_data, p_ref_data_read, sizeof(rm_ble_abs_gtl_strg_boot));
    if (boot_data.sec_data_mng_info.magic_num != BLE_ABS_SECURE_DATA_MAGIC_NUMBER)
    {
        /* If the magic number is not valid, set it to the correct value */
        boot_data.sec_data_mng_info.magic_num          = BLE_ABS_SECURE_DATA_MAGIC_NUMBER; // Set the magic number to indicate valid data
        boot_data.sec_data_mng_info.bond_cnt           = 0;                                // Reset the bond count
        boot_data.loc_dev_sec_data.loc_ident_addr.type = BLE_GAP_ADDR_PUBLIC;              // Set default address type
        memset(boot_data.loc_dev_sec_data.loc_ident_addr.addr, 0x00, BLE_BD_ADDR_LEN);     // Clear the address
    }

    /* Update the Bluetooth device address */
    memcpy(&boot_data.loc_dev_sec_data.loc_ident_addr.addr, bd_address->addr, BLE_BD_ADDR_LEN);
    boot_data.loc_dev_sec_data.loc_ident_addr.type = bd_address->type;

    /* Write the updated boot data back to flash */
    memcpy(&ref_data_write, &boot_data, REF_DATA_SIZE);
    err = RM_VEE_FLASH_RecordWrite(&g_vee_ctrl, REF_DATA_IDX, ref_data_write, REF_DATA_SIZE);
    if (FSP_SUCCESS != err)
    {
        return err;
    }

    err = wr_timeout(5);

    return err;
}

/***********************************************************************************************************************
 * @brief        This function updates the crypto key value
 * @param[in]    key        Pointer to the new crypto key.
 * @param[in]    key_size   Size of the crypto key.
 * @retval       fsp_err_t  Status of the operation.
 **********************************************************************************************************************/
fsp_err_t rm_ble_abs_gtl_storage_upd_crypto_key (uint8_t * key, uint8_t key_size)
{
    fsp_err_t err = FSP_SUCCESS;

 #ifdef CRYPTO_ENABLED
    memcpy(usr_key, key, key_size);
 #else
    FSP_PARAMETER_NOT_USED(key);
    FSP_PARAMETER_NOT_USED(key_size);
 #endif

    return err;
}

#endif                                 // ENABLE_STORAGE
