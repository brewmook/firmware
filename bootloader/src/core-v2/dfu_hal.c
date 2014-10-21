/**
 ******************************************************************************
 * @file    dfu_hal.c
 * @authors  Satish Nair
 * @version V1.0.0
 * @date    20-Oct-2014
 * @brief   USB DFU Hardware Abstraction Layer
 ******************************************************************************
  Copyright (c) 2013-14 Spark Labs, Inc.  All rights reserved.

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, either
  version 3 of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this program; if not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "usbd_dfu_core.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usb_conf.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
USB_OTG_CORE_HANDLE USB_OTG_dev;

/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
 * Function Name  : HAL_DFU_USB_Init.
 * Description    : Initialize USB for DFU class.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void HAL_DFU_USB_Init(void)
{
    USBD_Init(&USB_OTG_dev,
#ifdef USE_USB_OTG_HS
            USB_OTG_HS_CORE_ID,
#else
            USB_OTG_FS_CORE_ID,
#endif
            &USR_desc,
            &DFU_cb,
            &USR_cb);
}
