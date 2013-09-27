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
#include "alert_level_characteristic.h"

/** @defgroup immediate_alert immediate_alert
* @{
* @ingroup services
*  
* @brief immediate_alert service implementation.
* 
* 
*/

#ifndef IMMEDIATE_ALERT_H__
#define IMMEDIATE_ALERT_H__

/** @brief Callback on immediate alert.
 *  @details This function is called when an immediate alert characteristic value is updated. 
 *  Implement this function to have your application behave according to the alert level of the immediate alert.
 *  @param level : Level of the immediate alert (see @ref alert_level_characteristic to view possible values).
 */
extern void immediate_alert_hook(alert_level_t level);

/** @brief Function to handle reception of data for immediate_alert.
 *  @details Call this function on the ACI_EVT_DATA_RECEIVED event. This function checks if the data received is for immediate_alert.
 *  If so it triggers the immediate alert with the received level.
 *  @param pipe_num Pipe which has received data.
 *  @param buffer Pointer to the received data.
 */
void immediate_alert_pipes_updated_evt_rcvd(uint8_t pipe_num, uint8_t *buffer);

/** @brief Function to check if the immediate alert service is available at master side.
 *  @details Returns the return value of lib_aci_is_pipe_available(PIPE_IMMEDIATE_ALERT_ALERT_LEVEL_TX_1).
 */
bool is_immediate_alert_service_available_at_master(aci_state_t * aci_stat);
#endif//IMMEDIATE_ALERT_H__
/** @} */

