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
#if defined BSP_CFG_OPTION_SETTING_OFS0 && !BSP_TZ_NONSECURE_BUILD && (BSP_CFG_CPU_CORE == 0)
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_ofs0") g_bsp_cfg_option_setting_ofs0[] = {BSP_CFG_OPTION_SETTING_OFS0};
#endif
#if defined BSP_CFG_OPTION_SETTING_OFS2 && !BSP_TZ_NONSECURE_BUILD && (BSP_CFG_CPU_CORE == 0)
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_ofs2") g_bsp_cfg_option_setting_ofs2[] = {BSP_CFG_OPTION_SETTING_OFS2};
#endif
#if defined BSP_CFG_OPTION_SETTING_SAS && !BSP_TZ_NONSECURE_BUILD && (BSP_CFG_CPU_CORE == 0)
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_sas") g_bsp_cfg_option_setting_sas[] = {BSP_CFG_OPTION_SETTING_SAS};
#endif
#if defined BSP_CFG_OPTION_SETTING_OFS1 && (BSP_CFG_CPU_CORE == 0)
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_ofs1") g_bsp_cfg_option_setting_ofs1[] = {BSP_CFG_OPTION_SETTING_OFS1};
#endif
#if defined BSP_CFG_OPTION_SETTING_OFS1_SEC && !BSP_TZ_NONSECURE_BUILD && (BSP_CFG_CPU_CORE == 0)
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_ofs1_sec") g_bsp_cfg_option_setting_ofs1_sec[] = {BSP_CFG_OPTION_SETTING_OFS1_SEC};
#endif
#if defined BSP_CFG_OPTION_SETTING_OFS1_SEL && !BSP_TZ_NONSECURE_BUILD && (BSP_CFG_CPU_CORE == 0)
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_ofs1_sel") g_bsp_cfg_option_setting_ofs1_sel[] = {BSP_CFG_OPTION_SETTING_OFS1_SEL};
#endif
#if defined BSP_CFG_OPTION_SETTING_OFS3 && (BSP_CFG_CPU_CORE == 0)
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_ofs3") g_bsp_cfg_option_setting_ofs3[] = {BSP_CFG_OPTION_SETTING_OFS3};
#endif
#if defined BSP_CFG_OPTION_SETTING_OFS3_SEC && !BSP_TZ_NONSECURE_BUILD && (BSP_CFG_CPU_CORE == 0)
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_ofs3_sec") g_bsp_cfg_option_setting_ofs3_sec[] = {BSP_CFG_OPTION_SETTING_OFS3_SEC};
#endif
#if defined BSP_CFG_OPTION_SETTING_OFS3_SEL && !BSP_TZ_NONSECURE_BUILD && (BSP_CFG_CPU_CORE == 0)
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_ofs3_sel") g_bsp_cfg_option_setting_ofs3_sel[] = {BSP_CFG_OPTION_SETTING_OFS3_SEL};
#endif
#if defined BSP_CFG_OPTION_SETTING_BPS && (BSP_CFG_CPU_CORE == 0)
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_bps") g_bsp_cfg_option_setting_bps[] = {BSP_CFG_OPTION_SETTING_BPS};
#endif
#if defined BSP_CFG_OPTION_SETTING_BPS_SEC && !BSP_TZ_NONSECURE_BUILD && (BSP_CFG_CPU_CORE == 0)
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_bps_sec") g_bsp_cfg_option_setting_bps_sec[] = {BSP_CFG_OPTION_SETTING_BPS_SEC};
#endif
#if defined BSP_CFG_OPTION_SETTING_OTP_PBPS_SEC && !BSP_TZ_NONSECURE_BUILD && (BSP_CFG_CPU_CORE == 0)
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_otp_pbps_sec") g_bsp_cfg_option_setting_otp_pbps_sec[] = {BSP_CFG_OPTION_SETTING_OTP_PBPS_SEC};
#endif
#if defined BSP_CFG_OPTION_SETTING_OTP_PBPS && (BSP_CFG_CPU_CORE == 0)
BSP_DONT_REMOVE static const uint32_t BSP_PLACE_IN_SECTION(".option_setting_otp_pbps") g_bsp_cfg_option_setting_otp_pbps[] = {BSP_CFG_OPTION_SETTING_OTP_PBPS};
#endif
#endif // BSP_BOOTLOADED_APPLICATION

/******************************/
/* the init tables are located in bsp_linker_info.h */
#define BSP_LINKER_C
#include "bsp_linker_info.h"

/* UNCRUSTIFY-ON */
