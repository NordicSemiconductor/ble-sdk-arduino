/*Copyright (c) 2013, Nordic Semiconductor ASA
 *All rights reserved.
 *
 *Redistribution and use in source and binary forms, with or without modification,
 *are permitted provided that the following conditions are met:
 *
 *  Redistributions of source code must retain the above copyright notice, this
 *  list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright notice, this
 *  list of conditions and the following disclaimer in the documentation and/or
 *  other materials provided with the distribution.
 *
 *  Neither the name of Nordic Semiconductor ASA nor the names of its
 *  contributors may be used to endorse or promote products derived from
 *  this software without specific prior written permission.
 *
 *THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 *ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
