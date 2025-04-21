/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
* \file             : r_sb_manifest.c
* \par version      : 1.00
* \par Product Name : Renesas-SB-Lib FSBL Custom
* \par Device(s)    : None(Independ devices)
* \par Description  : This file implements the Manifest module APIs.
***********************************************************************************************************************/

/*!***********************************************************
 * \addtogroup  SBLIBManifest
 * \{
 * \addtogroup  SBLIBManifestTypes             Manifest Types
 * \addtogroup  SBLIBManifestDefinesInternal   Manifest Internal Definitions
 * \addtogroup  SBLIBManifestTypesInternal     Manifest Internal Types
 * \addtogroup  SBLIBManifestAPIsInternal      Manifest Internal APIs
 * \}********************************************************/

/*=====================================================================================================================
 Includes <System Includes> , "Project Includes"
=====================================================================================================================*/
#include <stddef.h>
#include "r_sb_build_config.h"
#include "r_sb_api.h"
#include "r_sb_cmn.h"
#include "r_sb_manifest.h"

/*=====================================================================================================================
 Private macro definitions
=====================================================================================================================*/
/*!********************************************************************
 * \addtogroup SBLIBManifestDefinesInternal
 * \{
 * \addtogroup  group_manifest_common
 * \}*****************************************************************/
/**\addtogroup group_manifest_common ManifestCommon */
/*! \{*/
#define SB_PRV_MANI_TLV_LEN_OFFSET                      (SB_PRV_MANI_HEADER_SIZE)  /**< Manifest TLV length offset */
/** Start position of manifest TLV */
#define SB_PRV_MANI_TLV_TOP_OFFSET                      ((SB_PRV_MANI_TLV_LEN_OFFSET) + (SB_PRV_MANI_TLV_LEN_SIZE))

/** Magic number unique to Key Certificate */
#define SB_PRV_KEY_CERT_HEADER_MAGIC                    (0x6b657963UL)
/** Major and minor versions of key Certificate */
#define SB_PRV_KEY_CERT_HEADER_VERSION                  (0x00010000UL)

/** Magic number unique to Code Certificate */
#define SB_PRV_CODE_CERT_HEADER_MAGIC                   (0x636f6463UL)
/** Major and minor versions of Code Certificate */
#define SB_PRV_CODE_CERT_HEADER_VERSION                 (0x00010000UL)

#define SB_PRV_TLV_TL_TYPE_MASK                         (0xFFFFFF00UL)        /**< Type Mask of TLV Type & Length */
#define SB_PRV_TLV_TL_LEN_MASK                          (0x000000FFUL)        /**< Length Mask of TLV Type & Length */

#define SB_PRV_BYTES_OF_WORD                            (4UL)                 /**< Byte size in a WORD */
/*! \}*/

/*=====================================================================================================================
 Private type definitions
=====================================================================================================================*/
/*!********************************************************************
 * \addtogroup SBLIBManifestTypesInternal
 * \{******************************************************************/

/*! \}*/

/*=====================================================================================================================
 Public global variables
=====================================================================================================================*/

/*=====================================================================================================================
 Private global variables
=====================================================================================================================*/

/*=====================================================================================================================
 Private function prototypes
=====================================================================================================================*/

/*=====================================================================================================================
 Public function definitions
=====================================================================================================================*/
/**********************************************************************************************************************
* Function Name : r_sb_mani_set_key_cert_st
**********************************************************************************************************************/
/*!****************************************************************************************************************//**
 * \ingroup     SBLIBManifestAPIsInternal
 * \brief       Set value in key certificate structure
 * \param       [in]   p_key_cert           Start address of Key Certificate
 * \param       [out]  p_key_cert_st        Start address of Key Certificate Structure
 * \return
 *  - #SB_RET_SUCCESS:                          Successful completion
 *  - #SB_RET_ERR_INTERNAL_FAIL:                Internal processing failed
 * \par Global Variables
 *  - None
 * \par Call SB-Driver API
 *  - None
 * \par Precondition
 *  - None
 * \par Security components
 *  - yes
 * \par Detailed description
 *      - Set value in key certificate structure
 *      - Set the starting address of the header of the key certificate, the length of the TLV,
 *        and the starting address of the TLV
 *
 * Pseudo-code for the function can be found below.
 * -# Initialize the variable ret with #SB_RET_ERR_INTERNAL_FAIL
 * -# If (NULL != p_key_cert) && (NULL != p_key_cert_st)
 *   -# Cast the argument p_key_cert to #st_sb_key_cert_header_t* type and set it to p_key_cert_st->p_header
 *   -# Cast the #SB_PRV_MANI_TLV_LEN_OFFSET address of the argument p_key_cert to uint32_t* type and set it to
 *      p_key_cert_st->tlv_len
 *   -# Set p_key_cert_st->p_tlv_top to #SB_PRV_MANI_TLV_TOP_OFFSET address of argument p_key_cert
 *   -# Set ret to #SB_RET_SUCCESS
 * -# Else
 *   -# Do nothing
 * -# Return ret
 *
 * \callgraph
 *********************************************************************************************************************/
sb_ret_t r_sb_mani_set_key_cert_st(const uint8_t* const p_key_cert, st_sb_key_cert_t* const p_key_cert_st)
{
    sb_ret_t ret = SB_RET_ERR_INTERNAL_FAIL;

    if ((NULL != p_key_cert) && (NULL != p_key_cert_st))
    {
        /* Casting from pointer to pointer is no problem */
        p_key_cert_st->p_header = (const st_sb_key_cert_header_t*)p_key_cert;
        /* Casts that do not exceed the size of the type are fine */
        p_key_cert_st->tlv_len = *(const uint32_t*)(&p_key_cert[SB_PRV_MANI_TLV_LEN_OFFSET]);
        p_key_cert_st->p_tlv_top = &p_key_cert[SB_PRV_MANI_TLV_TOP_OFFSET];

        ret = SB_RET_SUCCESS;
    }
    else
    {
        /* If there are null arguments, return SB_RET_ERR_INTERNAL_FAIL */
    }

    return ret;
}
/**********************************************************************************************************************
* End of function r_sb_mani_set_key_cert_st()
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name : r_sb_mani_set_code_cert_st
**********************************************************************************************************************/
/*!****************************************************************************************************************//**
 * \ingroup     SBLIBManifestAPIsInternal
 * \brief       Set value in code certificate structure
 * \param       [in]   p_code_cert          Start address of Code Certificate
 * \param       [out]  p_code_cert_st       Start address of Code Certificate Structure
 * \return
 *  - #SB_RET_SUCCESS:                          Successful completion
 *  - #SB_RET_ERR_INTERNAL_FAIL:                Internal processing failed
 * \par Global Variables
 *  - None
 * \par Call SB-Driver API
 *  - None
 * \par Precondition
 *  - None
 * \par Security components
 *  - yes
 * \par Detailed description
 *      - Set value in code certificate structure
 *      - Set the starting address of the header of the code certificate, the length of the TLV,
 *        and the starting address of the TLV
 *
 * Pseudo-code for the function can be found below.
 * -# Initialize the variable ret with #SB_RET_ERR_INTERNAL_FAIL
 * -# If (NULL != p_code_cert) && (NULL != p_code_cert_st)
 *   -# Cast the argument p_code_cert to #st_sb_code_cert_header_t* type and set it to p_code_cert_st->p_header
 *   -# Cast the #SB_PRV_MANI_TLV_LEN_OFFSET address of the argument p_code_cert to uint32_t* type and set it to
 *      p_code_cert_st->tlv_len
 *   -# Set p_code_cert_st->p_tlv_top to #SB_PRV_MANI_TLV_TOP_OFFSET address of argument p_code_cert
 *   -# Set ret to #SB_RET_SUCCESS
 * -# Else
 *   -# Do nothing
 * -# Return ret
 *
 * \callgraph
 *********************************************************************************************************************/
sb_ret_t r_sb_mani_set_code_cert_st(const uint8_t* const p_code_cert, st_sb_code_cert_t* const p_code_cert_st)
{
    sb_ret_t ret = SB_RET_ERR_INTERNAL_FAIL;

    if ((NULL != p_code_cert) && (NULL != p_code_cert_st))
    {
        /* Casting from pointer to pointer is no problem */
        p_code_cert_st->p_header = (const st_sb_code_cert_header_t*)p_code_cert;
        /* Casts that do not exceed the size of the type are fine */
        p_code_cert_st->tlv_len = *(const uint32_t*)(&p_code_cert[SB_PRV_MANI_TLV_LEN_OFFSET]);
        p_code_cert_st->p_tlv_top = &p_code_cert[SB_PRV_MANI_TLV_TOP_OFFSET];

        ret = SB_RET_SUCCESS;
    }
    else
    {
        /* If there are null arguments, return SB_RET_ERR_INTERNAL_FAIL */
    }

    return ret;
}
/**********************************************************************************************************************
* End of function r_sb_mani_set_code_cert_st()
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name : r_sb_mani_chk_key_cert
**********************************************************************************************************************/
/*!****************************************************************************************************************//**
 * \ingroup     SBLIBManifestAPIsInternal
 * \brief       Check the setting value of the key certificate structure
 * \param       [in]   p_key_cert_st           Start address of Key Certificate Structure
 * \param       [in]   key_cert_len_max        Maximum byte length that Key Certificate can take
 * \return
 *  - #SB_RET_SUCCESS:                          Successful completion
 *  - #SB_RET_ERR_INTERNAL_FAIL:                Internal processing failed
 *  - #SB_RET_ERR_INVALID_ARG:                  Invalid argument entered
 *  - #SB_RET_ERR_MANI_INVALID_MAGIC:           Incorrect magic number is set
 *  - #SB_RET_ERR_MANI_UNSUPPORTED_VERSION:     Unsupported version is set
 *  - #SB_RET_ERR_MANI_OUT_OF_RANGE_LEN:        Out of range TLV Length is set
 * \par Global Variables
 *  - None
 * \par Call SB-Driver API
 *  - None
 * \par Precondition
 *  - None
 * \par Security components
 *  - yes
 * \par Detailed description
 *      - Check that the magic number in the key certificate header is the correct value
 *      - Check that the key certificate header's manifest version is the currently supported version
 *      - Check that Maximum byte length that Key Certificate can take is set within the normal range
 *      - Check that the length of the TLV is within the length of the key certificate
 *        excluding the header and size data length
 *
 * Pseudo-code for the function can be found below.
 * -# Initialize the variable ret with #SB_RET_ERR_INTERNAL_FAIL
 * -# If (NULL != p_key_cert_st) && (NULL != p_key_cert_st->p_header)
 *   -# If (#SB_PRV_KEY_CERT_HEADER_MAGIC == p_key_cert_st->p_header->magic)
 *     -# If (#SB_PRV_KEY_CERT_HEADER_VERSION == p_key_cert_st->p_header->manifest_version)
 *       -# If (key_cert_len_max >= #SB_MANIFEST_LEN_MIN) && (key_cert_len_max <= #SB_MANIFEST_LEN_MAX)
 *         -# If (p_key_cert_st->tlv_len <= (key_cert_len_max - #SB_PRV_MANI_HEADER_SIZE - #SB_PRV_MANI_TLV_LEN_SIZE))
 *           -# Set ret to #SB_RET_SUCCESS
 *         -# Else
 *           -# Set ret to #SB_RET_ERR_MANI_OUT_OF_RANGE_LEN
 *       -# Else
 *         -# Set ret to #SB_RET_ERR_INVALID_ARG
 *     -# Else
 *       -# Set ret to #SB_RET_ERR_MANI_UNSUPPORTED_VERSION
 *   -# Else
 *     -# Set ret to #SB_RET_ERR_MANI_INVALID_MAGIC
 * -# Else
 *   -# Do nothing
 * -# Return ret
 *
 * \callgraph
 *********************************************************************************************************************/
sb_ret_t r_sb_mani_chk_key_cert(const st_sb_key_cert_t* const p_key_cert_st, const uint32_t key_cert_len_max)
{
    sb_ret_t ret = SB_RET_ERR_INTERNAL_FAIL;

    /* Check NULL */
    if ((NULL != p_key_cert_st) && (NULL != p_key_cert_st->p_header))
    {
        /* Check magic */
        if (SB_PRV_KEY_CERT_HEADER_MAGIC == p_key_cert_st->p_header->magic)
        {
            /* Check version */
            if (SB_PRV_KEY_CERT_HEADER_VERSION == p_key_cert_st->p_header->manifest_version)
            {
                /* Check TLV len max */
                if ((key_cert_len_max >= SB_MANIFEST_LEN_MIN) && (key_cert_len_max <= SB_MANIFEST_LEN_MAX))
                {
                    /* Check TLV len */
                    if (p_key_cert_st->tlv_len <= ((key_cert_len_max - SB_PRV_MANI_HEADER_SIZE) -
                                                    SB_PRV_MANI_TLV_LEN_SIZE))
                    {
                        /* All checks passed. Set ret to the success code */
                        ret = SB_RET_SUCCESS;
                    }
                    else
                    {
                        /* Invalid TLV len */
                        ret = SB_RET_ERR_MANI_OUT_OF_RANGE_LEN;
                    }
                }
                else
                {
                    /* Invalid TLV len max */
                    ret = SB_RET_ERR_INVALID_ARG;
                }
            }
            else
            {
                /* Invalid version */
                ret = SB_RET_ERR_MANI_UNSUPPORTED_VERSION;
            }
        }
        else
        {
            /* Invalid magic */
            ret = SB_RET_ERR_MANI_INVALID_MAGIC;
        }
    }
    else
    {
        /* If there are null arguments, return SB_RET_ERR_INTERNAL_FAIL */
    }

    return ret;
}
/**********************************************************************************************************************
* End of function r_sb_mani_chk_key_cert()
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name : r_sb_mani_chk_code_cert
**********************************************************************************************************************/
/*!****************************************************************************************************************//**
 * \ingroup     SBLIBManifestAPIsInternal
 * \brief       Check the setting value of the code certificate structure
 * \param       [in]   p_code_cert_st          Start address of Code Certificate Structure
 * \param       [in]   code_cert_len_max       Maximum byte length that Code Certificate can take
 * \return
 *  - #SB_RET_SUCCESS:                          Successful completion
 *  - #SB_RET_ERR_INTERNAL_FAIL:                Internal processing failed
 *  - #SB_RET_ERR_INVALID_ARG:                  Invalid argument entered
 *  - #SB_RET_ERR_INVALID_ALIGNMENT:            Data entered with incorrect alignment
 *  - #SB_RET_ERR_MANI_INVALID_MAGIC:           Incorrect magic number is set
 *  - #SB_RET_ERR_MANI_UNSUPPORTED_VERSION:     Unsupported version is set
 *  - #SB_RET_ERR_MANI_OUT_OF_RANGE_LEN:        Out of range TLV Length is set
 *  - #SB_RET_ERR_MANI_INVALID_IMAGE_LEN:       An invalid image length is set
 * \par Global Variables
 *  - None
 * \par Call SB-Driver API
 *  - None
 * \par Precondition
 *  - None
 * \par Security components
 *  - yes
 * \par Detailed description
 *      - Check that the magic number in the code certificate header is the correct value
 *      - Check that the code certificate header's manifest version is the currently supported version
 *      - Check the image size is a multiple of 16
 *      - Check that Maximum byte length that Code Certificate can take is set within the normal range
 *      - Check that the length of the TLV is within the length of the code certificate
 *        excluding the header and size data length
 *
 * Pseudo-code for the function can be found below.
 * -# Initialize the variable ret with #SB_RET_ERR_INTERNAL_FAIL
 * -# If (NULL != p_code_cert_st) && (NULL != p_code_cert_st->p_header)
 *   -# If (#SB_PRV_CODE_CERT_HEADER_MAGIC == p_code_cert_st->p_header->magic)
 *     -# If (#SB_PRV_CODE_CERT_HEADER_VERSION == p_code_cert_st->p_header->manifest_version)
 *       -# If (p_code_cert_st->p_header->dest_addr & #SB_PRV_REMAINDER_DIV4) == 0UL
 *         -# If (p_code_cert_st->p_header->img_len & #SB_PRV_REMAINDER_DIV16) == 0UL
 *           -# If (code_cert_len_max >= #SB_MANIFEST_LEN_MIN) && (code_cert_len_max <= #SB_MANIFEST_LEN_MAX)
 *             -# If (p_code_cert_st->tlv_len <= ((code_cert_len_max - #SB_PRV_MANI_HEADER_SIZE) -
 *                                                 #SB_PRV_MANI_TLV_LEN_SIZE))
 *               -# Set ret to #SB_RET_SUCCESS.
 *             -# Else
 *               -# Set ret to #SB_RET_ERR_MANI_OUT_OF_RANGE_LEN
 *           -# Else
 *             -# Set ret to #SB_RET_ERR_INVALID_ARG
 *         -# Else
 *           -# Set ret to #SB_RET_ERR_MANI_INVALID_IMAGE_LEN
 *       -# Else
 *         -# Set ret to #SB_RET_ERR_INVALID_ALIGNMENT
 *     -# Else
 *       -# Set ret to #SB_RET_ERR_MANI_UNSUPPORTED_VERSION
 *   -# Else
 *     -# Set ret to #SB_RET_ERR_MANI_INVALID_MAGIC
 * -# Else
 *   -# Do nothing
 * -# Return ret
 *
 * \callgraph
 *********************************************************************************************************************/
sb_ret_t r_sb_mani_chk_code_cert(const st_sb_code_cert_t* const p_code_cert_st, const uint32_t code_cert_len_max)
{
    sb_ret_t ret = SB_RET_ERR_INTERNAL_FAIL;

    /* Check NULL */
    if ((NULL != p_code_cert_st) && (NULL != p_code_cert_st->p_header))
    {
        /* Check magic */
        if (SB_PRV_CODE_CERT_HEADER_MAGIC == p_code_cert_st->p_header->magic)
        {
            /* Check version */
            if (SB_PRV_CODE_CERT_HEADER_VERSION == p_code_cert_st->p_header->manifest_version)
            {
                /* Check image alignment */
                if ((p_code_cert_st->p_header->dest_addr & SB_PRV_REMAINDER_DIV4) == 0UL)
                {
                    /* Check image length */
                    if ((p_code_cert_st->p_header->img_len & SB_PRV_REMAINDER_DIV16) == 0UL)
                    {
                        /* Check TLV len max */
                        if ((code_cert_len_max >= SB_MANIFEST_LEN_MIN) && (code_cert_len_max <= SB_MANIFEST_LEN_MAX))
                        {
                            /* Check TLV len */
                            if (p_code_cert_st->tlv_len <= ((code_cert_len_max - SB_PRV_MANI_HEADER_SIZE) -
                                                            SB_PRV_MANI_TLV_LEN_SIZE))
                            {
                                /* All checks passed. Set ret to the success code */
                                ret = SB_RET_SUCCESS;
                            }
                            else
                            {
                                /* Invalid TLV len */
                                ret = SB_RET_ERR_MANI_OUT_OF_RANGE_LEN;
                            }
                        }
                        else
                        {
                            /* Invalid TLV len max */
                            ret = SB_RET_ERR_INVALID_ARG;
                        }
                    }
                    else
                    {
                        /* Invalid image length */
                        ret = SB_RET_ERR_MANI_INVALID_IMAGE_LEN;
                    }
                }
                else
                {
                    /* Invalid image alignment */
                    ret = SB_RET_ERR_INVALID_ALIGNMENT;
                }
            }
            else
            {
                /* Invalid version */
                ret = SB_RET_ERR_MANI_UNSUPPORTED_VERSION;
            }
        }
        else
        {
            /* Invalid magic */
            ret = SB_RET_ERR_MANI_INVALID_MAGIC;
        }
    }
    else
    {
        /* If there are null arguments, return SB_RET_ERR_INTERNAL_FAIL */
    }

    return ret;
}
/**********************************************************************************************************************
* End of function r_sb_mani_chk_code_cert()
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name : r_sb_mani_parse_tlvs
**********************************************************************************************************************/
/*!****************************************************************************************************************//**
 * \ingroup     SBLIBManifestAPIsInternal
 * \brief       Search TLV of specified type from TLV field
 * \param       [in]   p_top                   Start address of TLV field
 * \param       [in]   tlv_len                 TLV field length
 * \param       [in]   num_of_search_type      Number of search type
 * \param       [in]   p_search_types          Start address of search TLV type \n * Set the same number of search
 *                                             targets as the number specified in num_of_search_type
 * \param       [out]  p_tlvs                  Start address of the structure that stores the parsed TLV \n * Allocate
 *                                             the same number of arrays as the number specified in num_of_search_type
 * \return
 *  - #SB_RET_SUCCESS:                          Successful completion
 *  - #SB_RET_ERR_INTERNAL_FAIL:                Internal processing failed
 *  - #SB_RET_ERR_MANI_TLV_INVALID_LEN:         The length of the TLV field has a size that exceeds the end of
 *                                              the manifest.
 * \par Global Variables
 *  - None
 * \par Call SB-Driver API
 *  - None
 * \par Precondition
 *  - None
 * \par Security components
 *  - yes
 * \par Detailed description
 *      - Search TLV of specified type from TLV field
 *      - If the target type is found, set the value to p_tlvs at the same index as p_search_types
 *      - If the target type is not found, set NULL to val member of p_tlvs
 *      - Terminate search when all search targets are found or parsed to end of TLV field
 *      - Return #SB_RET_SUCCESS even if there is no target
 *      - If the end of the TLV field is exceeded during parsing, return #SB_RET_ERR_MANI_TLV_INVALID_LEN
 *
 * Pseudo-code for the function can be found below.
 * -# Initialize the variable ret with #SB_RET_ERR_INTERNAL_FAIL
 * -# If (NULL != p_top) && (NULL != p_search_types) && (NULL != p_tlvs)
 *   -# Set 0 to offset
 *   -# Set 0 to hit_cnt
 *   -# Loop while hit_cnt is smaller than num_of_search_type and offset is smaller than tlv_len
 *     -# Mask the type value from the Type & Length field and set it to type
 *     -# Mask the Length value of the Type & Length field, and set the value changed from WORD to BYTE to byte_len
 *     -# Set 0 to search_i
 *     -# Loop while search_i is less than num_of_search_type
 *       -# If (type & p_search_types[search_i].mask) ==
 *             (p_search_types[search_i].type & p_search_types[search_i].mask)
 *         -# If NULL == p_tlvs[search_i].p_val
 *           -# Set type to p_tlvs[i].type
 *           -# Set byte_len to p_tlvs[i].byte_len
 *           -# Set the start address of the value field to p_tlvs[i].p_val
 *           -# Increment hit_cnt
 *         -# Else
 *           -# Do nothing
 *         -# break
 *       -# Else
 *         -# Do nothing
 *       -# Increment search_i
 *     -# Add the value obtained by adding byte_len to #SB_PRV_TLV_TL_SIZE to offset
 *   -# If (offset > tlv_len)
 *     -# Set #SB_RET_ERR_MANI_TLV_INVALID_LEN to ret
 *   -# Else
 *     -# Set ret to #SB_RET_SUCCESS
 * -# Else
 *   -# Do nothing
 * -# Return ret
 *
 * \callgraph
 *********************************************************************************************************************/
sb_ret_t r_sb_mani_parse_tlvs(const uint8_t* const p_top, const uint32_t tlv_len, const uint32_t num_of_search_type,
                                const st_sb_search_tlv_type_t* const p_search_types, st_sb_tlv_t* const p_tlvs)
{
    sb_ret_t ret = SB_RET_ERR_INTERNAL_FAIL;

    uint32_t offset;
    uint32_t search_i;
    uint32_t type;
    uint32_t byte_len;
    uint32_t hit_cnt;

    if ((NULL != p_top) && (NULL != p_search_types) && (NULL != p_tlvs))
    {
        /* Initialize before parse */
        offset = 0UL;
        hit_cnt = 0UL;
        for (search_i = 0UL; search_i < num_of_search_type; search_i++)
        {
            p_tlvs[search_i].p_val = NULL;
        }

        while ((hit_cnt < num_of_search_type) && (offset < tlv_len))
        {
            /* Get Type&Length field */
            /* Casts that do not exceed the size of the type are fine */
            type = ((*(const uint32_t*)(&p_top[offset])) & SB_PRV_TLV_TL_TYPE_MASK);
            /* Same cast as above */
            byte_len = ((*(const uint32_t*)(&p_top[offset])) & SB_PRV_TLV_TL_LEN_MASK) * SB_PRV_BYTES_OF_WORD;

            /* Search type table */
            search_i = 0UL;
            while (search_i < num_of_search_type)
            {
                if ((type & p_search_types[search_i].mask) ==
                    (p_search_types[search_i].type & p_search_types[search_i].mask))
                {
                    if (NULL == p_tlvs[search_i].p_val)
                    {
                        p_tlvs[search_i].type = type;
                        p_tlvs[search_i].byte_len = byte_len;
                        /* Casting from pointer to pointer is no problem */
                        p_tlvs[search_i].p_val  = (const uint32_t*)(&p_top[offset + SB_PRV_TLV_TL_SIZE]);
                        hit_cnt++;
                    }
                    else
                    {
                        /* Target type already found. Do nothing */
                    }
                }
                else
                {
                    /* Do nothing */
                }
                search_i++;
            }

            /* Next TLV */
            offset += (SB_PRV_TLV_TL_SIZE + byte_len);
        }

        /* Check TLV total length over */
        if (offset > tlv_len)
        {
            ret = SB_RET_ERR_MANI_TLV_INVALID_LEN;
        }
        else
        {
            /* Set ret to the success code */
            ret = SB_RET_SUCCESS;
        }
    }
    else
    {
        /* If there are null arguments, return SB_RET_ERR_INTERNAL_FAIL */
    }

    return ret;
}
/**********************************************************************************************************************
* End of function r_sb_mani_parse_tlvs()
**********************************************************************************************************************/

/*=====================================================================================================================
 Private function definitions
=====================================================================================================================*/

/*=====================================================================================================================
 End of file
=====================================================================================================================*/
