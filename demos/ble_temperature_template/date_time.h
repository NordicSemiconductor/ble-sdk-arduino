/* Copyright (c) 2011 Nordic Semiconductor. All Rights Reserved.
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

#ifndef datetime_H
#define datetime_H
#include <stdint.h>
/** @file date_time.h
 * @brief Contains the structure definition of time_stamp structure
 */

/* Date and Time Structure */
typedef struct time_stamp
{
    uint16_t year;
    uint8_t  month;
    uint8_t  day;
    uint8_t  hour;
    uint8_t  minute;
    uint8_t  seconds;
}time_stamp_t;
#endif 
