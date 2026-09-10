/****************************************************************************
 * arch/arm/src/imxrt/imxrt_sema4.c
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

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <errno.h>
#include <stdint.h>

#include <nuttx/arch.h>

#include "arm_internal.h"
#include "imxrt_periphclks.h"
#include "imxrt_sema4.h"
#include "hardware/rt117x/imxrt117x_sema4.h"

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* Value this core must write to take a gate: processor number + 1.
 * 0 until imxrt_sema4_init() has run.
 */

static uint8_t g_sema4_self;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

static inline bool sema4_try(unsigned int gate, uint8_t value)
{
  putreg8(value, IMXRT_SEMA4_GATE(gate));
  return getreg8(IMXRT_SEMA4_GATE(gate)) == value;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

int imxrt_sema4_init(void)
{
  uint8_t proc;

  if (g_sema4_self != 0)
    {
      return OK;
    }

  imxrt_periphclk_configure(CCM_CCGR_SEMA, CCM_CG_ALL);

  /* The hardware ignores a write of another core's number: whichever
   * value sticks is ours. Probe on the last gate and release it.
   */

  for (proc = 0; proc < 2; proc++)
    {
      if (sema4_try(IMXRT_SEMA4_NGATES - 1, SEMA4_GATE_LOCKED(proc)))
        {
          putreg8(SEMA4_GATE_FREE, IMXRT_SEMA4_GATE(IMXRT_SEMA4_NGATES - 1));
          g_sema4_self = SEMA4_GATE_LOCKED(proc);
          return OK;
        }
    }

  return -ENODEV;
}

int imxrt_sema4_lock(unsigned int gate, uint32_t timeout_us)
{
  uint32_t waited = 0;

  DEBUGASSERT(gate < IMXRT_SEMA4_NGATES && g_sema4_self != 0);

  while (!sema4_try(gate, g_sema4_self))
    {
      if (waited >= timeout_us)
        {
          return -ETIMEDOUT;
        }

      up_udelay(1);
      waited++;
    }

  return OK;
}

void imxrt_sema4_unlock(unsigned int gate)
{
  DEBUGASSERT(gate < IMXRT_SEMA4_NGATES);
  putreg8(SEMA4_GATE_FREE, IMXRT_SEMA4_GATE(gate));
}
