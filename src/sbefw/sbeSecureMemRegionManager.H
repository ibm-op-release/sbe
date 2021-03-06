/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/sbefw/sbeSecureMemRegionManager.H $                       */
/*                                                                        */
/* OpenPOWER sbe Project                                                  */
/*                                                                        */
/* Contributors Listed Below - COPYRIGHT 2017                             */
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
#pragma once

#include <stdint.h>
#include <stddef.h>
#include "sbe_sp_intf.H"

enum class memRegionMode:uint8_t
{
    READ = 0x01,
    WRITE = 0x02,
};

// Structure to define a mem region
typedef struct
{
    uint64_t startAddress;
    uint32_t size;
    uint32_t mode;
} secureMemRegion_t;

constexpr size_t MAX_NONSECURE_MEM_REGIONS = 8;

class SBESecureMemRegionManager
{
    secureMemRegion_t iv_memRegions[MAX_NONSECURE_MEM_REGIONS];
    size_t iv_regionsOpenCnt;

    SBESecureMemRegionManager():iv_memRegions{0}
    {
    }

    /*
     * @brief getPartialRegionSize - get the overlapping region
     *                               if it exists.
     *                               Also if the overlap is from the beginning,
     *                               first region is returned
     *
     *
     * @param[in] i_region           region to check for overlap
     *
     * @return overlapping region
     */
    secureMemRegion_t getPartialRegionSize(const secureMemRegion_t i_region);

    public:
    // Disable copy constructors
    SBESecureMemRegionManager(const SBESecureMemRegionManager&) = delete;
    SBESecureMemRegionManager& operator=(const SBESecureMemRegionManager&) = delete;

    static SBESecureMemRegionManager& getInstance();

    /*
     * @brief add - Open a new memory region
     *
     * @param[in] i_startAddr  Start address of the memory region
     * @param[in] i_size       Size of the memory region
     * @param[in] i_mode       Bit mapped access mode of the memory region
     *
     * @return SBE secondary RC
     */
    sbeSecondaryResponse add(const uint64_t i_startAddr,
                             const uint32_t i_size,
                             const uint8_t i_mode);
    /*
     * @brief remove - Close a memory region
     *
     * @param[in] i_startAddr  Start address of the memory region
     *
     * @return SBE secondary RC
     */
    sbeSecondaryResponse remove(const uint64_t i_startAddr);
    /*
     * @brief isAccessAllowed - Check if the access is allowed
     *
     * @param[in] i_region     region to check the access for
     *
     * @return SBE secondary RC
     */
    sbeSecondaryResponse isAccessAllowed(secureMemRegion_t i_region);

    /*
     * @brief closeAllRegions - close all non-secure regions
     */
    void closeAllRegions()
    {
        iv_regionsOpenCnt = 0;
    }
};

extern SBESecureMemRegionManager* SBESecMemRegionManager;
