# IBM_PROLOG_BEGIN_TAG
# This is an automatically generated prolog.
#
# $Source: src/build/import_hwp_mk/istep4/istep4files.mk $
#
# OpenPOWER sbe Project
#
# Contributors Listed Below - COPYRIGHT 2016,2017
# [+] International Business Machines Corp.
#
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
# implied. See the License for the specific language governing
# permissions and limitations under the License.
#
# IBM_PROLOG_END_TAG
#  @file istep4files.mk
#
#  @brief mk for including istep4 object files
#
##########################################################################
# Object Files
##########################################################################
include img_defs.mk

ISTEP4-CPP-SOURCES = p9_hcd_cache_poweron.C
ISTEP4-CPP-SOURCES +=p9_hcd_cache_chiplet_reset.C
ISTEP4-CPP-SOURCES +=p9_hcd_cache_gptr_time_initf.C
ISTEP4-CPP-SOURCES +=p9_hcd_cache_dpll_setup.C
ISTEP4-CPP-SOURCES +=p9_hcd_cache_dcc_skewadjust_setup.C
ISTEP4-CPP-SOURCES +=p9_hcd_cache_chiplet_init.C
ISTEP4-CPP-SOURCES +=p9_hcd_cache_repair_initf.C
ISTEP4-CPP-SOURCES +=p9_hcd_cache_arrayinit.C
ISTEP4-CPP-SOURCES +=p9_hcd_cache_initf.C
ISTEP4-CPP-SOURCES +=p9_hcd_cache_startclocks.C
ISTEP4-CPP-SOURCES +=p9_hcd_cache_scominit.C
ISTEP4-CPP-SOURCES +=p9_hcd_cache_scomcust.C
ISTEP4-CPP-SOURCES +=p9_hcd_cache_dpll_initf.C
ISTEP4-CPP-SOURCES +=p9_hcd_cache_chiplet_l3_dcc_setup.C
ISTEP4-CPP-SOURCES +=p9_hcd_core_poweron.C
ISTEP4-CPP-SOURCES +=p9_hcd_core_chiplet_reset.C
ISTEP4-CPP-SOURCES +=p9_hcd_core_gptr_time_initf.C
ISTEP4-CPP-SOURCES +=p9_hcd_core_chiplet_init.C
ISTEP4-CPP-SOURCES +=p9_hcd_core_repair_initf.C
ISTEP4-CPP-SOURCES +=p9_hcd_core_arrayinit.C
ISTEP4-CPP-SOURCES +=p9_hcd_core_initf.C
ISTEP4-CPP-SOURCES +=p9_hcd_core_startclocks.C
ISTEP4-CPP-SOURCES +=p9_hcd_core_scominit.C
ISTEP4-CPP-SOURCES +=p9_hcd_core_scomcust.C
ISTEP4-CPP-SOURCES +=p9_core_scom.C
ISTEP4-CPP-SOURCES +=p9_hcd_cache_dcc_skewadjust_setup.C
ISTEP4-CPP-SOURCES +=p9_ncu_scom.C
ISTEP4-CPP-SOURCES +=p9_l2_scom.C
ISTEP4-CPP-SOURCES +=p9_l3_scom.C
ISTEP4-CPP-SOURCES +=p9_common_poweronoff.C
ifeq  ($(ddlevel), DD2)
ISTEP4-CPP-SOURCES +=p9_eq_clear_atomic_lock.C
ISTEP4-CPP-SOURCES +=p9_collect_deadman_ffdc.C
ISTEP4-CPP-SOURCES +=p9_sbe_ppe_ffdc.C
ISTEP4-CPP-SOURCES +=p9_sbe_ppe_utils.C
endif
ISTEP4-CPP-SOURCES +=p9_sbe_check_master_stop15.C
ISTEP4-C-SOURCES =
ISTEP4-S-SOURCES =

ISTEP4_OBJECTS += $(ISTEP4-CPP-SOURCES:.C=.o)
ISTEP4_OBJECTS += $(ISTEP4-C-SOURCES:.c=.o)
ISTEP4_OBJECTS += $(ISTEP4-S-SOURCES:.S=.o)
