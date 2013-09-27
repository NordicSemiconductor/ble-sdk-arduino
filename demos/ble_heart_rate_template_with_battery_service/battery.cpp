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


#include "lib_aci.h"
#include "services.h"
#include "battery.h"
#include "lib_battery_level.h"

#define INVALID_BATTERY_LEVEL 0xFF
#define BATTERY_DATA_BUFF_SIZE 1

const int battery_pin = 0;

static uint8_t previous_battery_level      = INVALID_BATTERY_LEVEL;
static uint8_t battery_level_on_disconnect = INVALID_BATTERY_LEVEL;
static uint8_t percent_level_on_connect    = INVALID_BATTERY_LEVEL;
static uint8_t battery_data_buffer[BATTERY_DATA_BUFF_SIZE];
 
 
bool get_battery_evolution(uint8_t *diff, uint8_t curr_batt_level)
{
  bool is_discharging = false;
  
  if (curr_batt_level != previous_battery_level)
  {
    if (curr_batt_level < previous_battery_level)
    {
      *diff = previous_battery_level - curr_batt_level;
      is_discharging = true;
    }
    else
    {
      *diff = curr_batt_level - previous_battery_level;
      is_discharging = false;
    }
  }
  return (is_discharging);
}

uint8_t measure_battery(aci_state_t *aci_state)
{
  uint16_t value;
  float calculated_mvolts;
  uint16_t mvolts;
  uint8_t battery_percent_level;
  
  analogReference(INTERNAL);
  value = analogRead(battery_pin);                    //sample 10 bit battery measurement
  calculated_mvolts = ((float)value)/1023*9000;       //transform sample value into millivolts
  mvolts = (uint16_t) calculated_mvolts;
  battery_percent_level = lib_battery_level_percent_alkaline_9_volt(calculated_mvolts);   //transform millivolt measurement into percent value
  
  return battery_percent_level;
}

void send_battery_update(aci_state_t *aci_state, uint8_t percent_level)
{
  if (lib_aci_send_data(PIPE_BATTERY_BATTERY_LEVEL_TX, &percent_level, sizeof(percent_level)))        //Sending battery level over the air
  {
    aci_state->data_credit_available--;
  }
}

void update_battery_from_data_buffer(aci_state_t *aci_state)
{
  //Todo:
  //Call send_battery_update with the buffer data if the buffer data is valid, otherwise do nothing.
}

void update_battery(aci_state_t *aci_state, uint8_t percent_level)
{
  uint8_t level_difference = 0;
  get_battery_evolution(&level_difference, percent_level);
  
  if (level_difference >= BATTERY_LVL_CHANGE_THRESHOLD)
  {
    lib_aci_set_local_data(aci_state, PIPE_BATTERY_BATTERY_LEVEL_SET, &percent_level, sizeof(percent_level));   //Set battery level
    previous_battery_level = percent_level;
    
    if(lib_aci_is_pipe_available(aci_state, PIPE_BATTERY_BATTERY_LEVEL_TX))
    {
      if(aci_state->data_credit_available > 0)
      {
        send_battery_update(aci_state, percent_level);
      }
      else
      {
        //Currently no data credit is available.
        //Insert battery data into data buffer.
        battery_data_buffer[0] = percent_level;
      }
    }    
  }  
}

void battery_on_pipe_status(aci_state_t *aci_stat)
{
  if (percent_level_on_connect != battery_level_on_disconnect)
  {
    if(lib_aci_is_pipe_available(aci_stat, PIPE_BATTERY_BATTERY_LEVEL_TX))
    {
      lib_aci_send_data(PIPE_BATTERY_BATTERY_LEVEL_TX, &percent_level_on_connect, sizeof(percent_level_on_connect));
    }
  }
}

void battery_on_connect(aci_state_t *aci_stat, uint8_t percent_level)
{
  percent_level_on_connect = percent_level;
  lib_aci_set_local_data(aci_stat, PIPE_BATTERY_BATTERY_LEVEL_SET, &percent_level, sizeof(percent_level));
}

void battery_on_disconnect(uint8_t percent_level)
{
  battery_level_on_disconnect = percent_level;
}
