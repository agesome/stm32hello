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

/*
 * Default implementation of the tfm_ns_interface that does not take any lock.
 * This reference implementation can be used on any context where a single
 * thread on the system is using the library.
 * 
 * In cases where multiple threads are allowed to make calls to this library,
 * a different implementation which takes the required locks is required.
 */

#include <stdint.h>
#include <stddef.h>

/* Include NS specific mutex declarations */
#include "tfm_ns_interface.h"

/* To include __weak */
#include "psa/client_extension.h"


__weak int32_t tfm_ns_interface_dispatch(veneer_fn fn,
                                         uint32_t arg0, uint32_t arg1,
                                         uint32_t arg2, uint32_t arg3)
{
    int32_t result;

    result = fn(arg0, arg1, arg2, arg3);
    
    return result;
}

__weak void ns_ipc_seq_begin(const ns_ipc_seq_info_t* info)
{
    (void) info;
    // do nothing
    return;
}

__weak void ns_ipc_seq_end(const ns_ipc_seq_info_t* info)
{
    (void) info;
    // do nothing
    return;
}
