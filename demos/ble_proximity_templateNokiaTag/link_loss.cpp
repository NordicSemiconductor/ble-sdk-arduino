/* Copyright (c) 2010 Nordic Semiconductor. All Rights Reserved.
*
* The information contained herein is property of Nordic Semiconductor ASA.
* Terms and conditions of usage are described in detail in NORDIC
* SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
*
* Licensees are granted free, non-transferable use of the information. NO
* WARRANTY of ANY KIND is provided. This heading must NOT be removed from
* the file.
*
* $LastChangedRevision$
*/

/* Attention! 
*  To maintain compliance with Nordic Semiconductor ASA's Bluetooth profile 
*  qualification listings, this section of source code must not be modified.
*/


#include <hal_platform.h>
#include "alert_level_characteristic.h"
#include "services.h"
#include "lib_aci.h"
#include "link_loss.h"

/*link loss Service */
volatile alert_level_t alert_handle_on_link_loss;

void link_loss_init(void)
{
  alert_handle_on_link_loss = ALERT_LEVEL_NO_ALERT;
}

void proximity_disconect_evt_rcvd(uint8_t disconnect_reason)
{
  if ((DISCONNECT_REASON_CX_CLOSED_BY_PEER_DEVICE != disconnect_reason)&&(DISCONNECT_REASON_CX_CLOSED_BY_LOCAL_DEVICE != disconnect_reason))
  {
    link_loss_alert_hook(alert_handle_on_link_loss);
  }
}

void link_loss_pipes_updated_evt_rcvd(uint8_t pipe_num, uint8_t *buffer)
{
  switch (pipe_num)
  {
    case PIPE_LINK_LOSS_ALERT_ALERT_LEVEL_RX_ACK_AUTO :
      alert_handle_on_link_loss = (alert_level_t)buffer[0];
      break;
  }
}
