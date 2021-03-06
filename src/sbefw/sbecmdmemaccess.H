/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/sbefw/sbecmdmemaccess.H $                                 */
/*                                                                        */
/* OpenPOWER sbe Project                                                  */
/*                                                                        */
/* Contributors Listed Below - COPYRIGHT 2016,2017                        */
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
/*
 * @file: ppe/sbe/sbefw/sbecmdmemaccess.H
 *
 * @brief This file contains the Interfaces for the Memory Access chip-ops
 *
 */

#ifndef __SBEFW_SBECMDMEMACCESS_H
#define __SBEFW_SBECMDMEMACCESS_H

#include <stdint.h>

typedef struct
{
    uint64_t reserved:32;
    uint64_t size:32;
    uint64_t startAddress:64;
} sbeMemRegionReq_t;

/**
 * @brief sbeUpdateMemAccessRegion - manage the unsecure memory regions
 *
 * @param[in] i_pArg Buffer to be passed to the function (not used as of now)
 *
 * @return    Rc from the FIFO access utility
 */
uint32_t sbeUpdateMemAccessRegion (uint8_t *i_pArg);

/**
  * @brief sbeGetMem : Implements SBE Get Memory ChipOp
  *
  * @param[in] i_pArg Buffer to be passed to the function (not used as of now)
  *
  * @return    Rc from the FIFO access utility
  */
uint32_t sbeGetMem (uint8_t *i_pArg);

/**
  * @brief sbePutMem : Implements SBE Put Memory ChipOp
  *
  * @param[in] i_pArg Buffer to be passed to the function (not used as of now)
  *
  * @return    Rc from the FIFO access utility
  */
uint32_t sbePutMem  (uint8_t *i_pArg);

#endif /* __SBEFW_SBECMDMEMACCESS_H */
