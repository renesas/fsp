/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "bsp_api.h"

/* UNCRUSTIFY-OFF */

/* boot loaded applications cannot set ofs registers (only do so in the boot loader) */
#ifndef BSP_BOOTLOADED_APPLICATION
/** configuration register output to sections */
#if defined BSP_CFG_OPTION_SETTING_OFS0 && !BSP_TZ_NONSECURE_BUILD
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_ofs0") g_bsp_cfg_option_setting_ofs0[] = {BSP_CFG_OPTION_SETTING_OFS0};
#endif
#if defined BSP_CFG_OPTION_SETTING_OFS2 && !BSP_TZ_NONSECURE_BUILD
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_ofs2") g_bsp_cfg_option_setting_ofs2[] = {BSP_CFG_OPTION_SETTING_OFS2};
#endif
#if defined BSP_CFG_OPTION_SETTING_DUALSEL && !BSP_TZ_NONSECURE_BUILD
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_dualsel") g_bsp_cfg_option_setting_dualsel[] = {BSP_CFG_OPTION_SETTING_DUALSEL};
#endif
#if defined BSP_CFG_OPTION_SETTING_OFS1
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_ofs1") g_bsp_cfg_option_setting_ofs1[] = {BSP_CFG_OPTION_SETTING_OFS1};
#endif
#if defined BSP_CFG_OPTION_SETTING_BANKSEL
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_banksel") g_bsp_cfg_option_setting_banksel[] = {BSP_CFG_OPTION_SETTING_BANKSEL};
#endif
#if defined BSP_CFG_OPTION_SETTING_BPS
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_bps") g_bsp_cfg_option_setting_bps[] = {BSP_CFG_OPTION_SETTING_BPS};
#endif
#if defined BSP_CFG_OPTION_SETTING_PBPS
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_pbps") g_bsp_cfg_option_setting_pbps[] = {BSP_CFG_OPTION_SETTING_PBPS};
#endif
#if defined BSP_CFG_OPTION_SETTING_OFS1_SEC && !BSP_TZ_NONSECURE_BUILD
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_ofs1_sec") g_bsp_cfg_option_setting_ofs1_sec[] = {BSP_CFG_OPTION_SETTING_OFS1_SEC};
#endif
#if defined BSP_CFG_OPTION_SETTING_BANKSEL_SEC && !BSP_TZ_NONSECURE_BUILD
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_banksel_sec") g_bsp_cfg_option_setting_banksel_sec[] = {BSP_CFG_OPTION_SETTING_BANKSEL_SEC};
#endif
#if defined BSP_CFG_OPTION_SETTING_BPS_SEC && !BSP_TZ_NONSECURE_BUILD
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_bps_sec") g_bsp_cfg_option_setting_bps_sec[] = {BSP_CFG_OPTION_SETTING_BPS_SEC};
#endif
#if defined BSP_CFG_OPTION_SETTING_PBPS_SEC && !BSP_TZ_NONSECURE_BUILD
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_pbps_sec") g_bsp_cfg_option_setting_pbps_sec[] = {BSP_CFG_OPTION_SETTING_PBPS_SEC};
#endif
#if defined BSP_CFG_OPTION_SETTING_OFS1_SEL && !BSP_TZ_NONSECURE_BUILD
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_ofs1_sel") g_bsp_cfg_option_setting_ofs1_sel[] = {BSP_CFG_OPTION_SETTING_OFS1_SEL};
#endif
#if defined BSP_CFG_OPTION_SETTING_BANKSEL_SEL && !BSP_TZ_NONSECURE_BUILD
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_banksel_sel") g_bsp_cfg_option_setting_banksel_sel[] = {BSP_CFG_OPTION_SETTING_BANKSEL_SEL};
#endif
#if defined BSP_CFG_OPTION_SETTING_BPS_SEL && !BSP_TZ_NONSECURE_BUILD
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_bps_sel") g_bsp_cfg_option_setting_bps_sel[] = {BSP_CFG_OPTION_SETTING_BPS_SEL};
#endif
#endif // BSP_BOOTLOADED_APPLICATION

/******************************/
/* the init tables are located in bsp_linker_info.h */
#define BSP_LINKER_C
#include "bsp_linker_info.h"

/* UNCRUSTIFY-ON */
