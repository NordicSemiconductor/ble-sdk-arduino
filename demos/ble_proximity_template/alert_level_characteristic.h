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

#ifndef ALERT_LEVEL_CHARACTERISTIC_H
#define ALERT_LEVEL_CHARACTERISTIC_H

/** @file
 * @brief 
 */
 
/** @defgroup alert_level_characteristic alert_level_characteristic
* @{
* @ingroup services
*  
* @brief alert_level_characteristic : defines possibles alert levels.
* 
*/

/** Possible Alert Levels*/
typedef enum alert_level_t
{
  /** No alert*/                           
  ALERT_LEVEL_NO_ALERT   = 0,
  /** Mild/moderate alert*/                           
  ALERT_LEVEL_MILD_ALERT = 1,
  /** high alert*/                           
  ALERT_LEVEL_HIGH_ALERT = 2,
}alert_level_t;

/** @} */

#endif // ALERT_LEVEL_CHARACTERISTIC_H
