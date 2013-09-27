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
*  To maintain compliance with Nordic Semiconductor ASA’s Bluetooth profile 
*  qualification listings, this section of source code must not be modified.
*/

#include "hal_platform.h"
#include "lib_battery_level.h"


/*
The discharge curve for CR2032 is non-linear. In this model it is split into
4 linear sections:
- Section 1: 3.0V - 2.9V = 100% - 42% (58% drop on 100 mV)
- Section 2: 2.9V - 2.74V = 42% - 18% (24% drop on 160 mV)
- Section 3: 2.74V - 2.44V = 18% - 6% (12% drop on 300 mV)
- Section 4: 2.44V - 2.1V = 6% - 0% (6% drop on 340 mV)

These numbers are by no means accurate. Temperature and
load in the actual application is not accounted for!
*/
uint8_t lib_battery_level_percent(uint16_t mvolts)
{
  uint16_t battery_level;

  if (mvolts >= 3000)
  {
    battery_level = 100;
  }
  else if (mvolts > 2900)
  {
    battery_level = 100 - ((3000 - mvolts) * 58) / 100;  
  }
  else if (mvolts > 2740)
  {
    battery_level = 42 - ((2900 - mvolts) * 24) / 160;  
  }
  else if (mvolts > 2440)
  {
    battery_level = 18 - ((2740 - mvolts) * 12) / 300;  
  }
  else if (mvolts > 2100)
  {
    battery_level = 6 - ((2440 - mvolts) * 6) / 340;
  }
  else
  {
    battery_level = 0; 
  }

  return (uint8_t)battery_level; 
}
