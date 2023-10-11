 /*
 * @copyright
 * Copyright (c) 2017-2021, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 * This file was modified by ProvenRun
 * Copyright (c) 2015-2023 ProvenRun S.A.S. - All Rights Reserved
 * https://www.provenrun.com/ 
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 */

#ifndef __TFM_NS_INTERFACE_H__
#define __TFM_NS_INTERFACE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef int32_t (*veneer_fn) (uint32_t arg0, uint32_t arg1,
                              uint32_t arg2, uint32_t arg3);

typedef struct ns_ipc_seq_info
{
    uint32_t signal;
} ns_ipc_seq_info_t;



/**
 * \brief NS interface, veneer function dispatcher
 *
 * \details This function implements the dispatching mechanism for the
 *          desired veneer function, to be called with the parameters
 *          described from arg0 to arg3.
 *
 * \note    NSPE shall implement this dispatcher according to NS specific
 *          implementation and actual usage scenario.
 *
 * \param[in] fn   Function pointer to the veneer function desired
 * \param[in] arg0 Argument 0 of fn
 * \param[in] arg1 Argument 1 of fn
 * \param[in] arg2 Argument 2 of fn
 * \param[in] arg3 Argument 3 of fn
 *
 * \return Returns the same return value of the requested veneer function
 *
 * \note This API must ensure the return value is from the veneer function.
 *       Other unrecoverable errors must be considered as fatal error and should
 *       not return.
 */
int32_t tfm_ns_interface_dispatch(veneer_fn fn,
                                  uint32_t arg0, uint32_t arg1,
                                  uint32_t arg2, uint32_t arg3);

/**
 * \brief NS interface, sequence initialisation hook function
 *
 * \details This function is guaranteed to be called before any sequence of
 *          call to the the TFM. In cases where multiple threads may call this
 *          library, the NSPE must provide an implementation of this function
 *          that will guarantee that no other threads is in the process of
 *          doing a sequence of calls to the Secure World, typically by taking
 *          a lock.
 *
 * \note    NSPE shall implement this dispatcher according to NS specific
 *          implementation and actual usage scenario.
 */
void ns_ipc_seq_begin(const ns_ipc_seq_info_t* info);

/**
 * \brief NS interface, sequence termination hook function
 *
 * \details This function is guaranteed to be called after any sequence of
 *          call to the the TFM. In cases where multiple threads may call this
 *          library, the NSPE must provide an implementation of this function
 *          that will release the lock used to guarantee that sequences do not
 *          happen concurrently.
 *
 * \note    NSPE shall implement this dispatcher according to NS specific
 *          implementation and actual usage scenario.
 */
void ns_ipc_seq_end(const ns_ipc_seq_info_t* info);

#ifdef __cplusplus
}
#endif

#endif /* __TFM_NS_INTERFACE_H__ */
