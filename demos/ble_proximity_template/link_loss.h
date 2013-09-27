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

#ifndef LINK_LOSS_H
#define LINK_LOSS_H

 
/** @defgroup link_loss link_loss
* @{
* @ingroup services
*  
* @brief Link Loss Service (for proximity profile) implementation.
* 
* 
*/


#include <stdint.h>
#include "alert_level_characteristic.h"

/** @brief Callback on link_loss alert.
 *  @details This function is called when a link loss alert characteristic value is updated. 
 *  Implement this function to have your application behave according to the alert level of the link loss alert.
 *  @param level Level of the link_loss alert (see @ref alert_level_characteristic to view possible values).
 */
extern void link_loss_alert_hook(alert_level_t level);


/** Function to be initialize the link_loss service (set the alert on link_loss to NO_ALERT).*/
void link_loss_init(void);


/** @brief Function to handle disconnect event.
 *  @details Call this function on the ACI_EVT_DISCONNECTED event. This function checks the reason for disconnect 
 *  and if it matches a link loss situation, triggers a link_loss event.
 *  @param disconnect_reason Reason for disconnect event (given with the disconnect event).
 */
void proximity_disconect_evt_rcvd(uint8_t disconnect_reason);

/** @brief Function to handle reception of data for link_loss.
 *  @details Call this function on the ACI_EVT_DATA_RECEIVED event. This function checks if the data received is for link_loss.
 *  If so, it memorizes the alert level received to use it for the next link_loss event.
 *  @param pipe_num Pipe which has received data.
 *  @param buffer Pointer to the received data.
 */
void link_loss_pipes_updated_evt_rcvd(uint8_t pipe_num, uint8_t *buffer);


/** @} */

#endif //LINK_LOSS_H
