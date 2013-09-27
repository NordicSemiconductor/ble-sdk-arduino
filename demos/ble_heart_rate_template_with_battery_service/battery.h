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

#define BATTERY_LVL_CHANGE_THRESHOLD 1

uint8_t measure_battery(aci_state_t *aci_state);
void update_battery_from_data_buffer(aci_state_t *aci_stat);

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
