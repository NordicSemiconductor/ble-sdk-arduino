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

