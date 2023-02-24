/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * File Name    : r_drw_memory.c
 * Description  : This file defines the D/AVE D1 low-level driver memory management functions.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <stdlib.h>
#include <string.h>
#include "r_drw_base.h"
#include "r_drw_cfg.h"

#if (BSP_CFG_RTOS == 2)                // FreeRTOS
 #include "FreeRTOS.h"
#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Extern functions
 **********************************************************************************************************************/

/* Optional user-defined memory allocation functions */
#if DRW_CFG_CUSTOM_MALLOC
extern void * d1_malloc(size_t size);
extern void   d1_free(void * ptr);

#endif

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @internal
 * @addtogroup DRW_PRV Internal DRW Documentation
 * @ingroup RENESAS_INTERNAL
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Allocates memory in the driver heap.
 *
 * @param[in] size      Size of the memory to be allocated.
 * @retval Non-NULL     The function returns a pointer to the allocation if successful.
 * @retval NULL         The function returns NULL if memory allocation failed.
 **********************************************************************************************************************/
void * d1_allocmem (d1_uint_t size)
{
#if DRW_CFG_CUSTOM_MALLOC

    /* Use user-defined malloc */
    return d1_malloc((size_t) size);
#elif (BSP_CFG_RTOS == 2)              // FreeRTOS
 #if configSUPPORT_DYNAMIC_ALLOCATION

    /* Use FreeRTOS heap */
    return pvPortMalloc((size_t) size);
 #else

    /* If RTOS dynamic allocation is disabled then allocate d1 heap data in the main heap. */
    return malloc((size_t) size);
 #endif
#else

    /* If no RTOS is present then allocate d1 heap data in the main heap. */
    return malloc((size_t) size);
#endif
}

/*******************************************************************************************************************//**
 * Frees the specified memory area in the driver heap.
 *
 * @param[in] ptr       Pointer to the memory area to be freed.
 **********************************************************************************************************************/
void d1_freemem (void * ptr)
{
#if DRW_CFG_CUSTOM_MALLOC

    /* Use user-defined free */
    d1_free(ptr);
#elif (BSP_CFG_RTOS == 2)              // FreeRTOS
 #if configSUPPORT_DYNAMIC_ALLOCATION

    /* Use FreeRTOS heap */
    vPortFree(ptr);
 #else

    /* If RTOS dynamic allocation is disabled then use free(). */
    free(ptr);
 #endif
#else

    /* If no RTOS is present then use free(). */
    free(ptr);
#endif
}

/*******************************************************************************************************************//**
 * This function intends to return the size of the given memory block but we don't return a valid value.
 * This function always returns 1.
 *
 * @param[in] ptr       Pointer to a memory block in the heap.
 * @retval    1         The function always returns 1.
 **********************************************************************************************************************/
d1_uint_t d1_memsize (void * ptr)
{
    FSP_PARAMETER_NOT_USED(ptr);

    /* Always return 1. */
    return 1U;
}

/*******************************************************************************************************************//**
 * Allocate video memory.
 * FSP does not use virtual memory so this function simply calls d1_allocmem.
 *
 * @param[in] handle    Pointer to the d1_device object (not used).
 * @param[in] memtype   Type of memory (not used).
 * @param[in] size      Number of bytes to allocate.
 * @retval    Non-NULL  The function returns a pointer to the allocation if successful.
 * @retval    NULL      The function returns Null if memory allocation failed.
 **********************************************************************************************************************/
void * d1_allocvidmem (d1_device * handle, d1_int_t memtype, d1_uint_t size)
{
    FSP_PARAMETER_NOT_USED(handle);
    FSP_PARAMETER_NOT_USED(memtype);

    return d1_allocmem(size);
}

/*******************************************************************************************************************//**
 * Free video memory.
 * FSP does not use virtual memory so this function simply calls d1_freemem.
 *
 * @param[in] handle    Pointer to the d1_device object (not used).
 * @param[in] memtype   Type of memory (not used).
 * @param[in] ptr       Address returned by d1_allocvidmem.
 **********************************************************************************************************************/
void d1_freevidmem (d1_device * handle, d1_int_t memtype, void * ptr)
{
    FSP_PARAMETER_NOT_USED(handle);
    FSP_PARAMETER_NOT_USED(memtype);

    d1_freemem(ptr);
}

/*******************************************************************************************************************//**
 * Get current memory status. This function is not used and always returns 0.
 *
 * @param[in] handle    Pointer to the d1_device object (not used).
 * @param[in] memtype   Type of memory (not used).
 * @param[in] query     Type of requested information (not used).
 * @retval    0         The function always return 0.
 **********************************************************************************************************************/
d1_int_t d1_queryvidmem (d1_device * handle, d1_int_t memtype, d1_int_t query)
{
    FSP_PARAMETER_NOT_USED(handle);
    FSP_PARAMETER_NOT_USED(memtype);
    FSP_PARAMETER_NOT_USED(query);

    return 0;
}

/*******************************************************************************************************************//**
 * Return information about system memory architecture.
 *
 * @param[in] handle    Pointer to the d1_device object (not used).
 * @retval    d1_ma_unified  The function always return d1_ma_unified (Unified memory architecture).
 **********************************************************************************************************************/
d1_int_t d1_queryarchitecture (d1_device * handle)
{
    FSP_PARAMETER_NOT_USED(handle);

    return d1_ma_unified;
}

/*******************************************************************************************************************//**
 * Map video memory for direct CPU access.
 * FSP does not use virtual memory so this function simply returns the passed pointer.
 *
 * @param[in] handle    Pointer to the d1_device object (not used).
 * @param[in] ptr       Video memory address returned by d1_allocvidmem.
 * @param[in] flags     Memory mapping flags (not used).
 * @retval    ptr       The function just returns ptr back as there is no mapping required for FSP.
 **********************************************************************************************************************/
void * d1_mapvidmem (d1_device * handle, void * ptr, d1_int_t flags)
{
    FSP_PARAMETER_NOT_USED(handle);
    FSP_PARAMETER_NOT_USED(flags);

    /* Nothing special necessary for FSP. */
    return ptr;
}

/*******************************************************************************************************************//**
 * Release memory mapping.
 * FSP does not use virtual memory so this function always returns 1.
 *
 * @param[in] handle    Pointer to the d1_device object (not used).
 * @param[in] ptr       Mapped video memory address returned by d1_mapvidmem (not used).
 * @retval    1         The function always return 1.
 **********************************************************************************************************************/
d1_int_t d1_unmapvidmem (d1_device * handle, void * ptr)
{
    FSP_PARAMETER_NOT_USED(handle);
    FSP_PARAMETER_NOT_USED(ptr);

    /* No unmapping necessary for FSP. */
    return 1;
}

/*******************************************************************************************************************//**
 * Map CPU accessible address of a video memory block back to video memory address.
 * FSP does not use virtual memory so this function simply returns the passed pointer.
 *
 * @param[in] handle    Pointer to the d1_device object (not used).
 * @param[in] ptr       CPU accessible address pointing to a video memory block originally allocated using d1_allocvidmem.
 * @retval    ptr       The function just returns ptr back as there is no mapping required for FSP.
 **********************************************************************************************************************/
void * d1_maptovidmem (d1_device * handle, void * ptr)
{
    FSP_PARAMETER_NOT_USED(handle);

    /* Nothing special necessary for FSP. */
    return ptr;
}

/*******************************************************************************************************************//**
 * Map already allocated video memory address to a CPU-accessible address.
 *
 * @param[in] handle    Pointer to the d1_device object (not used).
 * @param[in] ptr       Video memory address returned by d1_allocvidmem.
 * @retval    ptr       The function just returns ptr back as there is no mapping required for FSP.
 **********************************************************************************************************************/
void * d1_mapfromvidmem (d1_device * handle, void * ptr)
{
    FSP_PARAMETER_NOT_USED(handle);

    /* Nothing special necessary for FSP. */
    return ptr;
}

/*******************************************************************************************************************//**
 * Copy data to video memory. Destination (video) memory area has to be allocated by d1_allocvidmem.
 * As RA devices do not have separate video memory this simply calls memcpy.
 *
 * @param[in] handle    Pointer to the d1_device object (not used).
 * @param[in] dst       pointer into video memory (destination).
 * @param[in] src       Pointer into system memory (source).
 * @param[in] size      Number of bytes to copy.
 * @param[in] flags     Bitfield containing additional information on data to be copied (not used).
 * @retval    1         The function always return 1.
 **********************************************************************************************************************/
d1_int_t d1_copytovidmem (d1_device * handle, void * dst, const void * src, d1_uint_t size, d1_int_t flags)
{
    FSP_PARAMETER_NOT_USED(handle);
    FSP_PARAMETER_NOT_USED(flags);

    /* Simply use C standard memcpy. */
    memcpy(dst, src, size);

    return 1;
}

/*******************************************************************************************************************//**
 * Copy data from video memory. Source (video) memory area has to be allocated by d1_allocvidmem.
 * As RA devices do not have separate video memory this simply calls memcpy.
 *
 * @param[in] handle    Pointer to the d1_device object (not used).
 * @param[in] dst       pointer into system memory (destination).
 * @param[in] src       Pointer into video memory (source).
 * @param[in] size      Number of bytes to copy.
 * @param[in] flags     Reserved for future use.
 * @retval    1         The function always return 1.
 **********************************************************************************************************************/
d1_int_t d1_copyfromvidmem (d1_device * handle, void * dst, const void * src, d1_uint_t size, d1_int_t flags)
{
    FSP_PARAMETER_NOT_USED(handle);
    FSP_PARAMETER_NOT_USED(flags);

    /* Simply use C standard memcpy. */
    memcpy(dst, src, size);

    return 1;
}

/*******************************************************************************************************************//**
 * Flush CPU data caches. RA devices do not have cache memory so this function immediately returns 1.
 *
 * @param[in] handle    Pointer to the d1_device object (not used).
 * @param[in] memtype   Memory pools to flush (can be ORed together; not used).
 * @retval    1         The function always return 1.
 **********************************************************************************************************************/
d1_int_t d1_cacheflush (d1_device * handle, d1_int_t memtype)
{
    FSP_PARAMETER_NOT_USED(handle);
    FSP_PARAMETER_NOT_USED(memtype);

    return 1;
}

/*******************************************************************************************************************//**
 * Flush part of CPU data caches. RA devices do not have cache memory so this function immediately returns 1.
 *
 * @param[in] handle    Pointer to the d1_device object (not used).
 * @param[in] memtype   Memory pools to flush (can be ORed together; not used).
 * @param[in] ptr       Start address of memory to be flushed (not used).
 * @param[in] size      Size of memory to be flushed (not used).
 * @retval    1         The function always return 1.
 **********************************************************************************************************************/
d1_int_t d1_cacheblockflush (d1_device * handle, d1_int_t memtype, const void * ptr, d1_uint_t size)
{
    FSP_PARAMETER_NOT_USED(handle);
    FSP_PARAMETER_NOT_USED(memtype);
    FSP_PARAMETER_NOT_USED(ptr);
    FSP_PARAMETER_NOT_USED(size);

    return 1;
}

/*******************************************************************************************************************//**
 * @}
 **********************************************************************************************************************/
