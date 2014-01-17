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
*  To maintain compliance with Nordic Semiconductor ASA�s Bluetooth profile 
*  qualification listings, this section of source code must not be modified.
*/

/** @defgroup battery battery
* @{
* @ingroup services
*
* @brief battery service implementation.
* @details
* This module implements the battery service with characteristics : battery_level, battery_state and the aggregate of level and state.
*
* The level, in percent, is computed using @ref lib_battery_level by the function @ref update_battery.
*
*/
#include <stdint.h>

#ifndef BATTERY_H__
#define BATTERY_H__

#define BATTERY_LVL_CHANGE_THRESHOLD 2

/** @brief Function to check the battery.
 *  @details This function checks the battery's current level. Call this function on a regular basis to monitor the battery.
 *  @param percent_level Measured battery level in percent.
 */
void update_battery(aci_state_t *aci_stat, uint8_t percent_level);


/** @brief Battery's pipe_status event handler.
 *  @details Call this function on @c PipeStatusEvent.
 */
void battery_on_pipe_status(aci_state_t *aci_stat);

/** @brief Battery's connect event handler.
 *  @details Call this function on @c ConnectedEvent.
 *  @param percent_level Measured battery level in percent.
 */
void battery_on_connect(uint8_t percent_level);

/** @brief Battery's disconnect event handler.
 *  @details Call this function on @c DisconnectedEvent.
 *  @param percent_level Measured battery level in percent.
 */
void battery_on_disconnect(uint8_t percent_level);


#endif //BATTERY_DEMO_H__

//@}
