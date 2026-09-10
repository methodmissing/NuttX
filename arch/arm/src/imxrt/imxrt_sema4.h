/****************************************************************************
 * arch/arm/src/imxrt/imxrt_sema4.h
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

#ifndef __ARCH_ARM_SRC_IMXRT_IMXRT_SEMA4_H
#define __ARCH_ARM_SRC_IMXRT_IMXRT_SEMA4_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: imxrt_sema4_init
 *
 * Description:
 *   Enable the SEMA4 clock and learn this core's processor number by
 *   locking and releasing a gate. Idempotent.
 *
 * Returned Value:
 *   OK, or -ENODEV when no processor number claims a gate.
 *
 ****************************************************************************/

int imxrt_sema4_init(void);

/****************************************************************************
 * Name: imxrt_sema4_lock
 *
 * Description:
 *   Take a gate shared with the other core, spinning up to timeout_us.
 *
 * Returned Value:
 *   OK or -ETIMEDOUT.
 *
 ****************************************************************************/

int imxrt_sema4_lock(unsigned int gate, uint32_t timeout_us);

/****************************************************************************
 * Name: imxrt_sema4_unlock
 ****************************************************************************/

void imxrt_sema4_unlock(unsigned int gate);

#endif /* __ARCH_ARM_SRC_IMXRT_IMXRT_SEMA4_H */
