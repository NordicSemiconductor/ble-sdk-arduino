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
  
#include <avr/pgmspace.h>
#include <lib_aci.h>
#include "aci_setup.h"


// aci_struct that will contain 
// total initial credits
// current credit
// current state of the aci (setup/standby/active/sleep)
// open remote pipe pending
// close remote pipe pending
// Current pipe available bitmap
// Current pipe closed bitmap
// Current connection interval, slave latency and link supervision timeout
// Current State of the the GATT client (Service Discovery status)


extern hal_aci_data_t msg_to_send;



/**************************************************************************                */
/* Utility function to fill the the ACI command queue                                      */
/* aci_stat               Pointer to the ACI state                                         */
/* num_cmd_offset(in/out) Offset in the Setup message array to start from                  */
/*                        offset is updated to the new index after the queue is filled     */
/*                        or the last message us placed in the queue                       */
/* Returns                void                                                             */
/***************************************************************************/
void aci_setup_fill(aci_state_t *aci_stat, uint8_t *num_cmd_offset)
{
    
  while (*num_cmd_offset < aci_stat->aci_setup_info.num_setup_msgs)
  {
    //Copy the setup ACI message from Flash to RAM
    //Add 2 bytes to the length byte for status byte, length for the total number of bytes
    memcpy_P(&msg_to_send, &(aci_stat->aci_setup_info.setup_msgs[*num_cmd_offset]), 
              pgm_read_byte_near(&(aci_stat->aci_setup_info.setup_msgs[*num_cmd_offset].buffer[0]))+2); 
    
    //Put the Setup ACI message in the command queue
    if (!hal_aci_tl_send(&msg_to_send))
    {
		//ACI Command Queue is full
		// *num_cmd_offset is now pointing to the index of the Setup command that did not get sent
		return;
    }
    
    (*num_cmd_offset)++;
  }
 
}

  

aci_status_code_t do_aci_setup(aci_state_t *aci_stat)
{
  uint8_t setup_offset     = 0;
  uint16_t i               = 0x0000;
  aci_evt_t * aci_evt      = NULL;
  
  /*
  We are using the same buffer since we are copying the contents of the buffer when queuing and immediately processing the
  buffer when receiving
  */
  hal_aci_evt_t  *aci_data = (hal_aci_evt_t *)&msg_to_send;
  
  
  aci_evt->params.cmd_rsp.cmd_status = ACI_STATUS_ERROR_CRC_MISMATCH;
 
  while (aci_evt->params.cmd_rsp.cmd_status != ACI_STATUS_TRANSACTION_COMPLETE)
  {	  
	if (setup_offset < aci_stat->aci_setup_info.num_setup_msgs)
	{
		aci_setup_fill(aci_stat,  &setup_offset);
	}

	i++; //i is used as a guard counter, if this counter overflows, there is an error	
	if (i > 0xFFFE)
	{
		return ACI_STATUS_ERROR_INTERNAL;	
	}
	
    if (true == lib_aci_event_get(aci_stat, aci_data))
    {
		  aci_evt = &(aci_data->evt);
		  
		  if (ACI_EVT_CMD_RSP != aci_evt->evt_opcode )
		  {
			  //Got something other than a command response evt -> Error
			  return ACI_STATUS_ERROR_INTERNAL;
		  }      
      
		  switch (aci_evt->params.cmd_rsp.cmd_status)
		  {
			  case ACI_STATUS_TRANSACTION_CONTINUE:
			  //Go back to the the top of the loop so the queue can be filled up again
			  break;
			  
			  case ACI_STATUS_TRANSACTION_COMPLETE:
			  //Break out of the while loop when this status code appears
			  break;
			  
			  default:
			  //Any other status code is an error
			  return (aci_status_code_t )aci_evt->params.cmd_rsp.cmd_status;
			  break;			  
		  } 
	}
  }
  
  return (aci_status_code_t)aci_evt->params.cmd_rsp.cmd_status;
}
  
  

