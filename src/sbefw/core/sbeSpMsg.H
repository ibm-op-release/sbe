/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/sbefw/core/sbeSpMsg.H $                                   */
/*                                                                        */
/* OpenPOWER sbe Project                                                  */
/*                                                                        */
/* Contributors Listed Below - COPYRIGHT 2015,2018                        */
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
 * @file: ppe/sbe/sbefw/sbeSpMsg.H
 *
 * @brief This file contains the message structures for FIFO
 *        communication.
 *
 */

#ifndef __SBEFW_SBESP_MSG_H
#define __SBEFW_SBESP_MSG_H

#include "sbe_sp_intf.H"

#include "p9_adu_coherent_utils.H"

// @NOTE Make sure all FIFO structures are 32 bit alligned ( the largest
// member should be atleast 4 byte). It is required as in sbe fifo
// operation we are casting these structures to uint32_t pointer. It can
// cause alignment issue if largest member of structure is not atleast
// 32 bit. We can use bit fields to optimize  memory requirements.
// These are two coding guidleines we will follow for this file
// 1. All data members less than 32 bits will be bit fields
// 2. All data members more than 32 buts will be divided into small
//    members of 32 bit each. This is required as compiler pads structure
//    to largest data member and we do not want extra padding for data
//    members gretater than 32 bits ( e.g. uint64_t )
/**
  * @brief Command Request Header
  */
typedef struct
{
    uint32_t len;
    uint32_t reserved:12;
    uint32_t clientId:4;
    uint32_t cmdClass:8;
    uint32_t command:8;
}sbeFifoCmdReqBuf_t;

/**
  * @brief structure for generic header for fifo response.
  *
  */
typedef struct
{
    private:
    uint32_t _magicCode:16;
    uint32_t _cmdClass:8;
    uint32_t _command:8;
    uint32_t _primaryStatus:16;
    uint32_t _secondaryStatus:16;

    public:
    const uint8_t  cmdClass() const        { return _cmdClass; }
    const uint8_t  command() const         { return _command; }
    const uint16_t primaryStatus() const   { return _primaryStatus; }
    const uint16_t secondaryStatus() const { return _secondaryStatus; }
    /**
      * @brief set the primary and secondary status
      *
      * @param[in] i_prim  Primary status
      * @param[in] i_sec   Secondary status
      *
      * @return
      */
    void setStatus( const uint16_t i_prim, const uint16_t i_sec);

    /**
      * @brief set initial values for response header
      *
      * @note  We did not set this in constructor as based on use case
      *        it is possible that SBE_GLOBAL->sbeFifoCmdHdr does not have proper
      *        values at time of object creation.
      *
      */
    void init();
}sbeRespGenHdr_t;

/**
  * @brief structure for ffdc header for fifo response.
  *
  */
typedef struct sbeResponseFfdc
{
    uint32_t magicBytes:16;
    uint32_t lenInWords:16;  // length in word( 4 byte )
    uint32_t seqId:16;
    uint32_t cmdClass:8;
    uint32_t cmd:8;
    uint32_t fapiRc;

    /**
      * @brief set failed command information
      *
      * @param[in] i_seqId      sequence Id of command
      * @param[in] i_cmdClass   command class
      * @param[in] i_cmd        command
      *
      * @return
      */
    void inline setCmdInfo(const uint16_t i_seqId,
                           const uint8_t i_cmdClass,
                           const uint8_t i_cmd)
    {
        seqId = i_seqId;
        cmdClass = i_cmdClass;
        cmd = i_cmd;
    }

    /**
      * @brief set rc
      *
      * @param[in] i_rc  FAPI RC
      *
      * @return
      */
    void setRc(const uint32_t i_rc)
    {
        fapiRc = i_rc;
    }

    /**
      * @brief return fapiRc
      *
      * @return fapiRc
      */
    uint32_t getRc() const
    {
        return fapiRc;
    }

    /**
      * @brief constructor
      *
      * @param[in] i_rc  FAPI RC
      *
      * @return
      */
    sbeResponseFfdc()
    {
        magicBytes = 0xFFDC;
        seqId = 0;
        cmdClass = SBE_CMD_CLASS_UNKNOWN;
        cmd = SBE_CMD_UNKNOWN;
        lenInWords  = ( sizeof(uint32_t )    // For magicBytes + lenInWords
                        + sizeof(uint32_t)   // For SeqId + CmdClass + Cmd
                        + sizeof(fapiRc))
                           / sizeof(uint32_t);
        fapiRc = 0;
    }
}sbeResponseFfdc_t;

/**
  * @brief structure for execute istep chipop (0xA101) contents.
  *
  */
typedef struct
{
    uint32_t reserved1:8;
    uint32_t major:8;
    uint32_t reserved2:8;
    uint32_t minor:8;
}sbeIstepReqMsg_t;


/**
  * @brief structure for GetScom Chipop (0xA201) contents.
  *
  */
typedef struct
{
    uint32_t hiAddr;
    uint32_t lowAddr;
}sbeGetScomReqMsg_t;

/**
  * @brief structure for PutScom Chipop (0xA202) contents.
  *
  */
typedef struct
{
    uint32_t hiAddr;
    uint32_t lowAddr;
    uint32_t hiInputData;
    uint32_t lowInputData;

    /**
      * @brief return 64-bit Scom data
      *
      * @return 64-bit Scom data
      */
    uint64_t getScomData()
    {
        uint64_t data = ((uint64_t)hiInputData << 32) | lowInputData;
        return data;
    }
}sbePutScomReqMsg_t;

/**
  * @brief structure for Modify_Scom Chipop (0xA203) contents.
  *
  */
typedef struct
{
    uint32_t reserved:24;
    uint32_t opMode:8;
    uint32_t hiAddr;
    uint32_t lowAddr;
    uint32_t hiInputData;
    uint32_t lowInputData;

    /**
      * @brief return 64-bit modifying data
      *
      * @return 64-bit modifying data
      */
    uint64_t getModifyingData()
    {
        uint64_t data = ((uint64_t)hiInputData << 32) | lowInputData;
        return data;
    }
}sbeModifyScomReqMsg_t;

/**
  * @brief structure for PutScom_UnderMask Chipop (0xA204) contents.
  *
  */
typedef struct
{
    uint32_t hiAddr;
    uint32_t lowAddr;
    uint32_t hiInputData;
    uint32_t lowInputData;
    uint32_t hiMaskData;
    uint32_t lowMaskData;

    /**
      * @brief return 64-bit input data
      *
      * @return 64-bit input data
      */
    uint64_t getInputData()
    {
        uint64_t data = ((uint64_t)hiInputData << 32) | lowInputData;
        return data;
    }

    /**
      * @brief return 64-bit input mask
      *
      * @return 64-bit input mask
      */
    uint64_t getInputMask()
    {
        uint64_t data = ((uint64_t)hiMaskData << 32) | lowMaskData;
        return data;
    }

    /**
      * @brief Determines 64-bit Scom data
      *
      * @param[in/out] io_scomData 64-bit scom data
      */
    void getScomData(uint64_t &io_scomData)
    {
        uint64_t l_inputMask = getInputMask();
        uint64_t l_inputData = getInputData();
        io_scomData = (io_scomData & (~l_inputMask))
                    | (l_inputData & l_inputMask);
    }
}sbePutScomUnderMaskReqMsg_t;

/**
 * @brief Structure for SBE Memory Access ChipOps (0xA401/A402)
 *
 */
typedef struct
{
    uint32_t coreChipletId:8; //Pervasive Core Chiplet Id for PBA
    uint32_t eccByte:8;       //Ecc Override Byte from user
    uint32_t flags:16;        //Operational Flags -refer enum sbeMemoryAccessFlags
    uint32_t addrHi;          //Higher 32-Bit Memory Address
    uint32_t addrLo;          //Lower  32-Bit Memory Address
    uint32_t len;             //Length of Data in Bytes

    /**
      * @brief Calculates 64-bit PBA ADU Address
      *
      * @return Return 64-bit PBA ADU address
      */
    uint64_t getAddr() const
    {
        return (((uint64_t)addrHi << 32) | addrLo);
    }

    /**
      * @brief Determines if ECC Override bit is set
      *
      * @return Returns True if ECC Override bit is set
      *                 False if ECC Override bit is not set
      */
    bool isEccOverrideFlagSet() const
    {
        return ((flags & SBE_MEM_ACCESS_FLAGS_ECC_OVERRIDE) ? true : false);
    }

    /**
      * @brief Determines if ECC required bit is set
      *
      * @return Returns True if ECC required flag is set
      *                 False if ECC required flag is not set
      */
    bool isEccFlagSet() const
    {
        return ((flags & SBE_MEM_ACCESS_FLAGS_ECC_REQUIRED) ? true : false);
    }

    /**
      * @brief Determines if Itag required bit is set
      *
      * @return Returns True if Itag required flag is set
      *                 False if Itag required flag is not set
      */
    bool isItagFlagSet() const
    {
        return ((flags & SBE_MEM_ACCESS_FLAGS_ITAG) ? true : false);
    }

    /**
      * @brief Determines if PBA flag is set
      *
      * @return Returns True if PBA Flag is set
      *                 False if PBA flag is not set
      */
    bool isPbaFlagSet()
    {
        return ((flags & SBE_MEM_ACCESS_FLAGS_TARGET_PBA) ? true : false);
    }

    /**
      * @brief Determines if Auto Increment Mode is set
      *
      * @return Returns True if Auto Increment mode is set
      *                 False if Auto Increment is not set
      */
    bool isAutoIncrModeSet() const
    {
        return ((flags & SBE_MEM_ACCESS_FLAGS_AUTO_INCR_ON) ? true : false);
    }

    /**
      * @brief Determines if Fast Mode is set
      *
      * @return Returns True if Fast mode is set
      *                 False if Fast mode is not set
      */
    uint32_t isFastModeSet() const
    {
        return ((flags & SBE_MEM_ACCESS_FLAGS_FAST_MODE_ON) ? true : false);
    }

    /**
      * @brief Determines if LCO Mode is set
      *
      * @return Returns True if LCO mode is set
      *                 False if LCO mode is not set
      */
    uint32_t isPbaLcoModeSet() const
    {
        return ((flags & SBE_MEM_ACCESS_FLAGS_LCO_ENABLED) ? true : false);
    }

    /**
      * @brief Determines if inject Mode is set
      *
      * @return Returns True if inject mode is set
      *                 False if inject mode is not set
      */
    uint32_t isPbaInjectModeSet() const
    {
        return ((flags & SBE_MEM_ACCESS_FLAGS_INJECT_ON) ? true : false);
    }

    /**
      * @brief Calculates Data length in alignment with PBA/ADU Cacheline
      * (128B/8B respectively)
      *
      * @return Returns Data length in alignment with PBA/ADU Cacheline
      */
    uint64_t getDataLenCacheAlign() const
    {
        // Expected length in bytes is 1, 2, 4, or multiples of 8,
        // won't work for any other values
        uint64_t l_len = (len < 8) ? (1) : (len / 8);
        if(flags & SBE_MEM_ACCESS_FLAGS_TARGET_PBA)
        {
            l_len = (l_len / 16);
        }
        return l_len;
    }

    /**
      * @brief Determines if it is Host Pass-through Command
      *
      * @return Returns True if Host Pass-through mode is set
      *                 False if Host Pass-through mode is not set
      */
    uint32_t isPbaHostPassThroughModeSet() const
    {
        return ((flags & SBE_MEM_ACCESS_FLAGS_HOST_PASS_THROUGH) ? true : false);
    }

    /**
      * @brief Map SBE mem access flags to ADU operation type flag
      *
      */
    void setADUOperationType(p9_ADU_oper_flag &o_aduFlag) const
    {
        if(flags & SBE_MEM_ACCESS_FLAGS_CACHE_INHIBIT)
        {
            o_aduFlag.setOperationType(p9_ADU_oper_flag::CACHE_INHIBIT);
        }
        else if(flags & SBE_MEM_ACCESS_FLAGS_PB_DIS)
        {
            o_aduFlag.setOperationType(p9_ADU_oper_flag::PB_DIS_OPER);
        }
        else if(flags & SBE_MEM_ACCESS_FLAGS_SWITCH)
        {
            o_aduFlag.setOperationType(p9_ADU_oper_flag::PMISC_OPER);
        }
        else if(flags & SBE_MEM_ACCESS_FLAGS_PB_INIT)
        {
            o_aduFlag.setOperationType(p9_ADU_oper_flag::PB_INIT_OPER);
        }
        else if(flags & SBE_MEM_ACCESS_FLAGS_PRESWITCH_AB)
        {
            o_aduFlag.setOperationType(p9_ADU_oper_flag::PRE_SWITCH_AB);
        }
        else if(flags & SBE_MEM_ACCESS_FLAGS_PRESWITCH_CD)
        {
            o_aduFlag.setOperationType(p9_ADU_oper_flag::PRE_SWITCH_CD);
        }
        else if(flags & SBE_MEM_ACCESS_FLAGS_POSTSWITCH)
        {
            o_aduFlag.setOperationType(p9_ADU_oper_flag::POST_SWITCH);
        }
    }

    /**
      * @brief check if the given flags are trusted operations,
      *        which doesn't work with address and data passed
      *
      */
    bool isTrustedOp() const
    {
        bool trusted = false;
        if(flags &
                (SBE_MEM_ACCESS_FLAGS_PB_DIS |
                 SBE_MEM_ACCESS_FLAGS_SWITCH |
                 SBE_MEM_ACCESS_FLAGS_PB_INIT |
                 SBE_MEM_ACCESS_FLAGS_PRESWITCH_AB |
                 SBE_MEM_ACCESS_FLAGS_PRESWITCH_CD |
                 SBE_MEM_ACCESS_FLAGS_POSTSWITCH))
        {
            trusted = true;
        }
        return trusted;
    }

}sbeMemAccessReqMsgHdr_t;

/**
 * @brief Structure for SBE OCC Get/Put Sram Access ChipOps (0xA403/A404)
 */
typedef struct
{
    uint32_t reserved:24;           // Not used
    sbeSramAccessMode mode:8;       // Channel select 0-3
    uint32_t addr;                  // 32-Bit Memory Address
    uint32_t len;                   // Length of Data in Bytes
}sbeOccSramAccessReqMsgHdr_t;

// Maximum number of capabilities - max of FIFO and PSU capabilities
static const uint32_t SBE_MAX_CAPABILITIES      = 20;

/**
  * @brief structure for SBE Get Capabilities chipop (0xA802) contents.
  *
  */
typedef struct sbeCapabilityRespMsg
{
    uint32_t verMajor:16;
    uint32_t verMinor:16;
    uint32_t fwCommitId;
    char     buildTag[20];
    uint32_t capability[SBE_MAX_CAPABILITIES];
    // ctor. constructor will initialise all values.
    sbeCapabilityRespMsg();
}sbeCapabilityRespMsg_t;

//  TODO via RTC 128658
//  We may be able to replace this structure by sbeRespGenHdr_t

/**
  * @brief Command response structure to hold the primary and secondary
  *        status values. This will be utilized when a command class
  *        validation or state machine check fails.
  *
  */
typedef struct
{
    uint32_t          prim_status:16 ;    // Primary Response Status
    uint32_t          sec_status:16  ;    // Secondary Response Status

    /**
     * @brief initialize the response status
     **/
    void init()
    {
        prim_status   = SBE_PRI_OPERATION_SUCCESSFUL;
        sec_status    = SBE_SEC_OPERATION_SUCCESSFUL;
    }

    /**
     * @brief set the primary and secondary status
     *
     * @param[in] i_prim      Primary status
     * @param[in] i_sec       Secondary status
     *
     **/
    void setStatus(const uint16_t i_prim,
                   const uint16_t i_sec);
} sbeCmdRespHdr_t;

/**
  * @brief structure for Stop Clocks Chipop (0xA901) contents.
  *
  */
typedef struct
{
    uint32_t       targetType:16;
    uint32_t       reserved:8;
    uint32_t       chipletId:8;
}sbeStopClocksReqMsgHdr_t;

/**
  * @brief structure for Control Instruction Chipop (0xA701) contents.
  *
  */
typedef struct
{
    uint32_t           reserved:12;
    sbeErrorMode       mode:4;
    sbeCoreChipletId   coreChipletId:8;
    sbeThreadNum       threadNum:4;
    sbeThreadOps       threadOps:4;

    /**
      * @brief Validate input arguments
      *
      * @return bool, true if the validation is success, else false for
      * validation failure
      */
    bool validateInputArgs()
    {
        bool l_validatePassFlag = true;
        // Validate Thread Command / Thread Num / Error Mode
        if((threadOps > THREAD_SRESET_INS) ||
           !((threadNum <= SMT4_THREAD3) || (threadNum == SMT4_THREAD_ALL)))
        {
            SBE_ERROR(SBE_FUNC "Invalid Parameter by User, ThreadOps[%d] "
                "mode[%d] ThreadNum[%d]", (uint32_t)threadOps, (uint32_t)mode, (uint32_t)threadNum);
            l_validatePassFlag = false;
        }
        return l_validatePassFlag;
    }

    /**
      * @brief Process the input to find out core/thread ids to iterate
      *        over HWP for the internal business logic
      *
      * @param[out] o_core, Core Id to start with in the iteration
      * @param[out] o_coreCntMax, Core Max count to iterate, start from o_core
      * @param[out] o_threadCnt, Thread Num to start with in the iteration
      * @param[out] o_threadCntMax, Thread Max Num to iterate, start from
      *             o_threadCnt
      *
      * @return void
      */
    void processInputDataToIterate(uint8_t & o_core, uint8_t & o_coreCntMax,
                               uint8_t & o_threadCnt, uint8_t & o_threadCntMax)
    {
        //Default Init
        o_threadCnt = SMT4_THREAD0;
        o_threadCntMax = SMT4_THREAD_MAX;

        o_core = SMT4_CORE0_ID;
        o_coreCntMax = SMT4_CORE_ID_LAST+1;

        if( SMT4_ALL_CORES != coreChipletId )
        {
            o_core = coreChipletId;
            o_coreCntMax = coreChipletId;
        }
        if( SMT4_THREAD_ALL != threadNum )
        {
            o_threadCnt = threadNum;
            o_threadCntMax = threadNum;
        }
    }

    /**
     * @brief Special wakeup required for this request
     *
     * @return true if required, else false
     */
    bool isSpecialWakeUpRequired()
    {
        return (mode & SPECIAL_WAKEUP);
    }
}sbeCntlInstRegMsgHdr_t;

/**
 * @brief Get Ring access message header
 */
typedef struct
{
    uint32_t ringAddr;
    uint32_t ringLenInBits;
    uint32_t reserved:16;
    uint32_t ringMode:16;
}sbeGetRingAccessMsgHdr_t;

/**
 * @brief maximum double words for putring RS4 payload for chipop operation
 */
static const uint32_t SBE_PUT_RING_RS4_MAX_DOUBLE_WORDS =
                        SBE_PUT_RING_RS4_MAX_PAYLOAD_BYTES/sizeof(uint64_t);

/**
 * @brief Put Ring message header
 */
typedef struct
{
    uint32_t reserved:16;
    uint32_t ringMode:16;
}sbePutRingMsgHdr_t;

/**
 * @brief Put Ring message
 * @note This structure should have uint64_t as type as underlying
 *       platrform cast it to uint64 pointer. If we declare this as
 *       uint32, we can get allignment errors.
 */
typedef struct
{
    uint64_t rs4Payload[SBE_PUT_RING_RS4_MAX_DOUBLE_WORDS];
}sbePutRingMsg_t;

/**
  * @brief Reg access message header
  */
typedef struct
{
    uint32_t reserved:8;
    uint32_t coreChiplet:8;
    uint32_t threadNr:4;
    uint32_t regType:4;
    uint32_t numRegs:8;

    /**
      * @brief checks if it is valid request.
      *
      * @return true if valid request, false otherwise
      */
    bool isValidRequest() const
    {
        return (( SBE_REG_ACCESS_FPR >= regType )
                &&( SBE_MAX_REG_ACCESS_REGS >= numRegs )
                &&( SMT4_THREAD3 >= threadNr )
                &&( SMT4_CORE0_ID <= coreChiplet )
                &&( SMT4_CORE_ID_LAST >= coreChiplet )) ? true:false;
    }
}sbeRegAccessMsgHdr_t;

/**
  * @brief reg scom package
  */
typedef struct
{
    uint32_t regNr;
    uint32_t hiData;
    uint32_t lowData;

    /**
      * @brief data for a register.
      *
      * @return data.
      */
    uint64_t getData() const
    {
        return (((uint64_t)hiData << 32 ) | lowData );
    }
}sbeRegAccessPackage_t;

#endif // __SBEFW_SBESP_MSG_H
