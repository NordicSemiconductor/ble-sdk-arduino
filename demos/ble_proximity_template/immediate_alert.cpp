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

#include <stdint.h>
#include "lib_aci.h"
#include "services.h"
#include "alert_level_characteristic.h"
#include "immediate_alert.h"


void immediate_alert_pipes_updated_evt_rcvd(uint8_t pipe_num, uint8_t *buffer)
{
  switch (pipe_num)
  {
    case PIPE_IMMEDIATE_ALERT_ALERT_LEVEL_RX :
      immediate_alert_hook((alert_level_t)buffer[0]);
      break;
  }
}

/*  This function returns true if the immediate alert service is available at the master.
	The user of this function may decide take appropriate action (if needed) based of the
	return value of this function. */

bool is_immediate_alert_service_available_at_master(aci_state_t * aci_stat)
{
	return lib_aci_is_pipe_available(aci_stat, PIPE_IMMEDIATE_ALERT_ALERT_LEVEL_TX_1);

}
