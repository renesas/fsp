/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rsip_primitive.h"
#include "r_rsip_util.h"

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

uint32_t         S_RAM[RSIP_PRV_WORD_SIZE_S_RAM];
uint32_t const * S_INST2;
uint32_t         INST_DATA_SIZE;

uint32_t const DomainParam_NIST_P256[] =
{
    BSWAP_32BIG_C(0x646d9b3cU), BSWAP_32BIG_C(0xa740e0d8U), BSWAP_32BIG_C(0x14953f12U), BSWAP_32BIG_C(0xca1d90faU),
    BSWAP_32BIG_C(0x6f8993baU), BSWAP_32BIG_C(0x150c91caU), BSWAP_32BIG_C(0xf075f037U), BSWAP_32BIG_C(0xe1be2d57U),
    BSWAP_32BIG_C(0x5e63ad9fU), BSWAP_32BIG_C(0x15426e2eU), BSWAP_32BIG_C(0x97b77340U), BSWAP_32BIG_C(0xb2c3da0aU),
    BSWAP_32BIG_C(0x437815a0U), BSWAP_32BIG_C(0xfc91cdb5U), BSWAP_32BIG_C(0x47da485dU), BSWAP_32BIG_C(0x765ff0acU),
    BSWAP_32BIG_C(0x167f5522U), BSWAP_32BIG_C(0xd5fa6619U), BSWAP_32BIG_C(0x23469968U), BSWAP_32BIG_C(0xe46a9817U),
    BSWAP_32BIG_C(0xa32bbb8aU), BSWAP_32BIG_C(0xdaee68bbU), BSWAP_32BIG_C(0x537a3bb6U), BSWAP_32BIG_C(0x0897fe04U),
    BSWAP_32BIG_C(0x545d0562U), BSWAP_32BIG_C(0xc30d1b7eU), BSWAP_32BIG_C(0xab4770c2U), BSWAP_32BIG_C(0xacfe2f1eU),
    BSWAP_32BIG_C(0xf62f2ef1U), BSWAP_32BIG_C(0x705ce539U), BSWAP_32BIG_C(0x6c29d9d5U), BSWAP_32BIG_C(0x6d0e7f05U),
    BSWAP_32BIG_C(0xeda353e0U), BSWAP_32BIG_C(0x02e966d2U), BSWAP_32BIG_C(0x9c1e5923U), BSWAP_32BIG_C(0x20d4b26aU),
    BSWAP_32BIG_C(0x3acce832U), BSWAP_32BIG_C(0xce7be734U), BSWAP_32BIG_C(0xa1d287e8U), BSWAP_32BIG_C(0xb6c1bc37U),
    BSWAP_32BIG_C(0xd98571d4U), BSWAP_32BIG_C(0xade3fd3aU), BSWAP_32BIG_C(0xb10af158U), BSWAP_32BIG_C(0x0b5a0177U),
    BSWAP_32BIG_C(0xc6203d55U), BSWAP_32BIG_C(0x905c6266U), BSWAP_32BIG_C(0xdf0c9ac3U), BSWAP_32BIG_C(0x0198a9e5U),
    BSWAP_32BIG_C(0x7f75f86cU), BSWAP_32BIG_C(0xca00c7d0U), BSWAP_32BIG_C(0x51ac028eU), BSWAP_32BIG_C(0xcbf43f06U),
    BSWAP_32BIG_C(0xb029a4e0U), BSWAP_32BIG_C(0xb8bed4ebU), BSWAP_32BIG_C(0xa53c40c3U), BSWAP_32BIG_C(0x83abc923U),
    BSWAP_32BIG_C(0x01fd7d1cU), BSWAP_32BIG_C(0xc01a0e90U), BSWAP_32BIG_C(0x2350c769U), BSWAP_32BIG_C(0x9d9ea28dU),
    BSWAP_32BIG_C(0xe9d3a38fU), BSWAP_32BIG_C(0xe2f06bd2U), BSWAP_32BIG_C(0x87d1e891U), BSWAP_32BIG_C(0xac087462U),
    BSWAP_32BIG_C(0x0dd38e41U), BSWAP_32BIG_C(0xb6ee6c1aU), BSWAP_32BIG_C(0x97ab7790U), BSWAP_32BIG_C(0x01190e35U),
    BSWAP_32BIG_C(0x0c1d5cc7U), BSWAP_32BIG_C(0xb8750a2bU), BSWAP_32BIG_C(0x8ea6a7a6U), BSWAP_32BIG_C(0x3b7deb84U),
};
