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
