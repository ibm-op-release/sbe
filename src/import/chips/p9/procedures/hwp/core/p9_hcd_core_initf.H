/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/import/chips/p9/procedures/hwp/core/p9_hcd_core_initf.H $ */
/*                                                                        */
/* OpenPOWER sbe Project                                                  */
/*                                                                        */
/* Contributors Listed Below - COPYRIGHT 2015,2017                        */
/* [+] International Business Machines Corp.                              */
/*                                                                        */
/*                                                                        */
/* Licensed under the Apache License, Version 2.0 (the "License");        */
/* you may not use this file except in compliance with the License.       */
/* You may obtain a copy of the License at                                */
/*                                                                        */
/*     http://www.apache.org/licenses/LICENSE-2.0                         */
/*                                                                        */
/* Unless required by applicable law or agreed to in writing, software    */
/* distributed under the License is distributed on an "AS IS" BASIS,      */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or        */
/* implied. See the License for the specific language governing           */
/* permissions and limitations under the License.                         */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
///
/// @file  p9_hcd_core_initf.H
/// @brief Core scan init
///

// *HWP HWP Owner          : David Du         <daviddu@us.ibm.com>
// *HWP Backup HWP Owner   : Greg Still       <stillgs@us.ibm.com>
// *HWP FW Owner           : Prem Shanker Jha <premjha2@in.ibm.com>
// *HWP Team               : PM
// *HWP Consumed by        : SBE:CME
// *HWP Level              : 3

#ifndef __P9_HCD_CORE_INITF_H__
#define __P9_HCD_CORE_INITF_H__

#include <fapi2.H>

/// @typedef p9_hcd_core_initf_FP_t
/// function pointer typedef definition for HWP call support
typedef fapi2::ReturnCode (*p9_hcd_core_initf_FP_t) (
    const fapi2::Target<fapi2::TARGET_TYPE_CORE>&);

extern "C"
{

/// @brief Core scan init
///
/// @param [in] i_target TARGET_TYPE_CORE target
/// @attr
/// @attritem ATTR_CORE_FUNC_RING - EC target, uint32
///               pointer to RS4 content<br>
///
/// @retval FAPI_RC_SUCCESS
    fapi2::ReturnCode
    p9_hcd_core_initf(
        const fapi2::Target<fapi2::TARGET_TYPE_CORE>& i_target);

}

#endif  // __P9_HCD_CORE_INITF_H__
