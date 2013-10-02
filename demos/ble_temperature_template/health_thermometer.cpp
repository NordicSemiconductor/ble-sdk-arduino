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

#include "services.h"
#include "health_thermometer.h"
#include "lib_aci.h"

#include <stdbool.h>

static h_thermo_temp_measure_t h_temperature;
static h_temp_type_t current_type;

void health_thermometer_init()
{
  h_temperature.flags = 0;
  h_temperature.measurement[H_THERMOMETER_POS_TEMP_LSB0] = 0;
  h_temperature.measurement[H_THERMOMETER_POS_TEMP_LSB1] = 0;
  h_temperature.measurement[H_THERMOMETER_POS_TEMP_MSB0] = 0;
  h_temperature.measurement[H_THERMOMETER_POS_TEMP_MSB1] = 0;
  h_temperature.time_type[H_THERMOMETER_POS_YEAR_LSB] = (uint8_t)((1582)&0x00FF);
  h_temperature.time_type[H_THERMOMETER_POS_YEAR_MSB] = (uint8_t)((1582>>8)&0x00FF);
  h_temperature.time_type[H_THERMOMETER_POS_MOUNTH  ] = 0;
  h_temperature.time_type[H_THERMOMETER_POS_DAY     ] = 1;
  h_temperature.time_type[H_THERMOMETER_POS_HOUR    ] = 0;
  h_temperature.time_type[H_THERMOMETER_POS_MINUTE  ] = 0;
  h_temperature.time_type[H_THERMOMETER_POS_SECOND  ] = 0;
  h_temperature.time_type[H_THERMOMETER_POS_TYPE_WITH_TSTAMP] = 0;
  current_type = H_TYPE_NOT_INCLUDED;
}

void health_thermometer_set_unit_c()
{
  h_temperature.flags  &= ~H_THERMOMETER_FLAGS_UNIT_BIT; 
}

void health_thermometer_set_unit_f()
{
  h_temperature.flags  |= H_THERMOMETER_FLAGS_UNIT_BIT; 
}

bool health_thermometer_send_measure(uint32_t meas_temp)
{
  
  uint8_t measurement_size = 5;
  uint8_t *p_in_val = (uint8_t *)&meas_temp;
  
  if (0 != (h_temperature.flags&H_THERMOMETER_FLAGS_TYPE_BIT))
  {
    measurement_size++;
    h_temperature.time_type[H_THERMOMETER_POS_TYPE_NO_TSTAMP] = current_type;
  }
  h_temperature.flags  &= ~H_THERMOMETER_FLAGS_T_STAMP_BIT; 
  h_temperature.measurement[H_THERMOMETER_POS_TEMP_LSB0] = p_in_val[0];//p_in_val[3];
  h_temperature.measurement[H_THERMOMETER_POS_TEMP_LSB1] = p_in_val[1];//p_in_val[2];
  h_temperature.measurement[H_THERMOMETER_POS_TEMP_MSB0] = p_in_val[2];//p_in_val[1];
  h_temperature.measurement[H_THERMOMETER_POS_TEMP_MSB1] = p_in_val[3];//p_in_val[0];
  return lib_aci_send_data(PIPE_HEALTH_THERMOMETER_TEMPERATURE_MEASUREMENT_TX_ACK, (uint8_t *)&h_temperature, measurement_size);
}

bool health_thermometer_send_measure_with_t_stamp(uint32_t meas_temp, time_stamp_t *t_stamp, bool is_freshest_sample)
{
  uint8_t measurement_size = 12;
  uint8_t *p_in_val = (uint8_t *)&meas_temp;
  if (0 != (h_temperature.flags&H_THERMOMETER_FLAGS_TYPE_BIT))
  {
    measurement_size++;
    h_temperature.time_type[H_THERMOMETER_POS_TYPE_WITH_TSTAMP] = current_type;
  }
  h_temperature.measurement[H_THERMOMETER_POS_TEMP_LSB0] = p_in_val[3];
  h_temperature.measurement[H_THERMOMETER_POS_TEMP_LSB1] = p_in_val[2];
  h_temperature.measurement[H_THERMOMETER_POS_TEMP_MSB0] = p_in_val[1];
  h_temperature.measurement[H_THERMOMETER_POS_TEMP_MSB1] = p_in_val[0];
  h_temperature.time_type[H_THERMOMETER_POS_YEAR_LSB] = (uint8_t)(t_stamp->year);
  h_temperature.time_type[H_THERMOMETER_POS_YEAR_MSB] = (uint8_t)((t_stamp->year)>>8);
  h_temperature.time_type[H_THERMOMETER_POS_MOUNTH  ] = t_stamp->month  ;
  h_temperature.time_type[H_THERMOMETER_POS_DAY     ] = t_stamp->day    ;
  h_temperature.time_type[H_THERMOMETER_POS_HOUR    ] = t_stamp->hour   ;
  h_temperature.time_type[H_THERMOMETER_POS_MINUTE  ] = t_stamp->minute ;
  h_temperature.time_type[H_THERMOMETER_POS_SECOND  ] = t_stamp->seconds;
  h_temperature.flags  |= H_THERMOMETER_FLAGS_T_STAMP_BIT; 
  return lib_aci_send_data(PIPE_HEALTH_THERMOMETER_TEMPERATURE_MEASUREMENT_TX_ACK, (uint8_t *)&h_temperature, 
                           measurement_size);
}

void health_thermometer_set_dynamic_type(h_temp_type_t in_type)
{
  if (H_TYPE_NOT_INCLUDED == in_type)
  {
    h_temperature.flags  &= ~H_THERMOMETER_FLAGS_TYPE_BIT; 
  }
  else
  {
    h_temperature.flags |= H_THERMOMETER_FLAGS_TYPE_BIT; 
    current_type = in_type;
  }
}


