/* Copyright (c) 2009 Nordic Semiconductor. All Rights Reserved.
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

/** @file

@defgroup lib_battery_level lib_battery_level
@{
@ingroup lib

@brief Battery model that gives the battery level based on supply voltage
@details The model is based on the CR2032 coin cell battery. The nominal
voltage is 3.0 Volts. The voltage will drop as the battery drains.

 */

#ifndef LIB_BATTERY_LEVEL_H__
#define LIB_BATTERY_LEVEL_H__

#include "hal_platform.h"

/** @brief Calculates the battery level in percent based on supply voltage

@details The calculation is based on a linearized version of typical alcaline battery
discharge curve. 9.0V returns 100% battery level while the limit for power failure is
6.0V and is considered to be the lower boundary.

@param mvolts The supply voltage in mV (9000-6000).
@return Battery level in percent.

*/
uint8_t lib_battery_level_percent_alkaline_9_volt(float mvolts);

/** @brief Calculates the battery level in percent based on supply voltage

@details The calculation is based on a linearized version of the battery's discharge
curve. 3.0V returns 100% battery level while the limit for power failure is 2.1V and 
is considered to be the lower boundary.

@param mvolts The supply voltage in mV (9000-6000).
@return Battery level in percent.

*/
uint8_t lib_battery_level_percent(uint16_t mvolts);

#endif // LIB_BATTERY_LEVEL_H__

/** @} */
