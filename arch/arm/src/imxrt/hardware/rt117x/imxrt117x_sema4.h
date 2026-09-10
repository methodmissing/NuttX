/****************************************************************************
 * arch/arm/src/imxrt/hardware/rt117x/imxrt117x_sema4.h
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

#ifndef __ARCH_ARM_SRC_IMXRT_HARDWARE_RT117X_IMXRT117X_SEMA4_H
#define __ARCH_ARM_SRC_IMXRT_HARDWARE_RT117X_IMXRT117X_SEMA4_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include "hardware/imxrt_memorymap.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Sixteen byte-wide gates. A gate reads 0 when free, otherwise the
 * processor number + 1 of the core holding it; only that core's write of
 * its own number + 1 takes effect, any core may write 0 to release.
 */

#define IMXRT_SEMA4_NGATES            16
#define IMXRT_SEMA4_GATE(n)           (IMXRT_SEMA4_BASE + (n))
#define IMXRT_SEMA4_RSTGT             (IMXRT_SEMA4_BASE + 0x0042)

#define SEMA4_GATE_FREE               0
#define SEMA4_GATE_LOCKED(proc)       ((proc) + 1)

#endif /* __ARCH_ARM_SRC_IMXRT_HARDWARE_RT117X_IMXRT117X_SEMA4_H */
