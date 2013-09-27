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
 
/**
 * test project to put the nRF8001 in Test mode and allow DTM commands over the nRF8001 UART
 */

/** @defgroup ble_set_in_test_mode ble_set_in_test_mode
@{
@ingroup projects
@brief Put the nRF8001 in test mode.

@details
This project is to put the nRF8001 in test mode and enable the nRF8001 to accept DTM commands over UART . 
You can send the DTM commands from the nRFgo studio or from a Nordic Semiconductor supplied python script on a Windows PC.
 */
#include <SPI.h>
#include <avr/pgmspace.h>
#include <ble_system.h>
#include <lib_aci.h>

// aci_struct that will contain 
// total initial credits
// current credit
// current state of the aci (setup/test/standby/active/sleep)
// open remote pipe pending
// close remote pipe pending
// Current pipe available bitmap
// Current pipe closed bitmap
// Current connection interval, slave latency and link supervision timeout
// Current State of the the GATT client (Service Discovery)
// Status of the bond (R) Peer address
static struct aci_state_t aci_state;

static hal_aci_evt_t aci_data;
static hal_aci_data_t aci_cmd;

void setup(void)
{ 
  Serial.begin(115200);
  
  //Tell the ACI library, the MCU to nRF8001 pin connections
  aci_state.aci_pins.board_name = BOARD_DEFAULT; //See board.h for details REDBEARLAB_SHIELD_V1_1 or BOARD_DEFAULT
  aci_state.aci_pins.reqn_pin   = 9; //SS for Nordic board, 9 for REDBEARLABS
  aci_state.aci_pins.rdyn_pin   = 8; //3 for Nordic board, 8 for REDBEARLABS
  aci_state.aci_pins.mosi_pin   = MOSI;
  aci_state.aci_pins.miso_pin   = MISO;
  aci_state.aci_pins.sck_pin    = SCK;
	
  aci_state.aci_pins.spi_clock_divider     = SPI_CLOCK_DIV8;
	  
  aci_state.aci_pins.reset_pin             = 7; //4 for Nordic board, UNUSED for REDBEARLABS
  aci_state.aci_pins.active_pin            = UNUSED;
  aci_state.aci_pins.optional_chip_sel_pin = UNUSED;
  
  aci_state.aci_pins.interface_is_interrupt	  = false;
  aci_state.aci_pins.interrupt_number	          = 1;
  
  lib_aci_init(&aci_state);
  Serial.println(F("nRF8001 Reset done"));
}

void loop()
{
  // We enter the if statement only when there is a ACI event available to be processed
  if (lib_aci_event_get(&aci_state, &aci_data))
  {
    aci_evt_t * aci_evt;
    
    aci_evt = &aci_data.evt;
    switch(aci_evt->evt_opcode)
    {
        /**
        As soon as you reset the nRF8001 you will get an ACI Device Started Event
        */
        case ACI_EVT_DEVICE_STARTED:
        {          
          aci_state.data_credit_available = aci_evt->params.device_started.credit_available;
          switch(aci_evt->params.device_started.device_mode)
          {
            case ACI_DEVICE_SETUP:
              Serial.println(F("Evt Device Started: Setup"));              
              //Put the nRF8001 in Test mode. 
              //See ACI Test Command in Section 24 (System Commands) of the nRF8001 datasheet.
              //Use ACI_TEST_MODE_DTM_ACI to send DTM commands over ACI
              lib_aci_test(ACI_TEST_MODE_DTM_UART);
              break;
                            
            case ACI_DEVICE_TEST:
            {
              uint8_t i = 0;
              Serial.println(F("Evt Device Started: Test"));
              Serial.println(F("Ready for testing with DTM commands over the nRF8001 UART"));
            }
              break;
          }
        }
        break; //ACI Device Started Event
      case ACI_EVT_CMD_RSP:
        //If an ACI command response event comes with an error -> stop
        if (ACI_STATUS_SUCCESS != aci_evt->params.cmd_rsp.cmd_status)
        {
          //ACI ReadDynamicData and ACI WriteDynamicData will have status codes of
          //TRANSACTION_CONTINUE and TRANSACTION_COMPLETE
          //all other ACI commands will have status code of ACI_STATUS_SCUCCESS for a successful command
          Serial.print(F("ACI Command 0x"));
          Serial.println(aci_evt->params.cmd_rsp.cmd_opcode, HEX);
          Serial.println(F("Evt Cmd respone: Error. Arduino is in an while(1); loop"));
          while (1);
        }
        break;
   }
  }
  else
  {
    // No event in the ACI Event queue
  }
}

