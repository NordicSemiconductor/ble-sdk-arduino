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

/** @file
@brief Implementation of the ACI transport layer module
*/

#include <SPI.h>
#include "hal_platform.h"
#include "hal_aci_tl.h"
#include <avr/sleep.h>

static void           m_print_aci_data(hal_aci_data_t *p_data);
static uint8_t        spi_readwrite(uint8_t aci_byte);

static hal_aci_data_t received_data;
static bool           aci_debug_print;




aci_queue_t    aci_tx_q;
aci_queue_t    aci_rx_q;

static aci_pins_t	 *a_pins_local_ptr;

static void m_aci_q_init(aci_queue_t *aci_q)
{
  uint8_t loop;
  
  aci_debug_print = false;
  aci_q->head = 0;
  aci_q->tail = 0;
  for(loop=0; loop<ACI_QUEUE_SIZE; loop++)
  {
    aci_q->aci_data[loop].buffer[0] = 0x00;
    aci_q->aci_data[loop].buffer[1] = 0x00;
  }
}

void hal_aci_debug_print(bool enable)
{
	aci_debug_print = enable;
}

bool m_aci_q_enqueue(aci_queue_t *aci_q, hal_aci_data_t *p_data)
{
  const uint8_t next = (aci_q->tail + 1) % ACI_QUEUE_SIZE;
  const uint8_t length = p_data->buffer[0];
  
  if (next == aci_q->head)
  {
    /* full queue */
    return false;
  }
  aci_q->aci_data[aci_q->tail].status_byte = 0;
  
  memcpy((uint8_t *)&(aci_q->aci_data[aci_q->tail].buffer[0]), (uint8_t *)&p_data->buffer[0], length + 1);
  aci_q->tail = next;
  
  return true;
}

//@comment after a port to a new mcu have test for the queue states, esp. the full and the empty states
static bool m_aci_q_dequeue(aci_queue_t *aci_q, hal_aci_data_t *p_data)
{
  if (aci_q->head == aci_q->tail)
  {
    /* empty queue */
    return false;
  }
  
  memcpy((uint8_t *)p_data, (uint8_t *)&(aci_q->aci_data[aci_q->head]), sizeof(hal_aci_data_t));
  aci_q->head = (aci_q->head + 1) % ACI_QUEUE_SIZE;
  
  return true;
}

bool m_aci_q_is_empty(aci_queue_t *aci_q)
{
  return (aci_q->head == aci_q->tail);
}

bool m_aci_q_is_full(aci_queue_t *aci_q)
{
  uint8_t next;
  bool state;
  
  //This should be done in a critical section
  noInterrupts();
  next = (aci_q->tail + 1) % ACI_QUEUE_SIZE;  
  
  if (next == aci_q->head)
  {
    state = true;
  }
  else
  {
    state = false;
  }
  
  interrupts();
  //end
  
  return state;
}



void m_print_aci_data(hal_aci_data_t *p_data)
{
  const uint8_t length = p_data->buffer[0];
  uint8_t i;
  Serial.print(length, DEC);
  Serial.print(" :");
  for (i=0; i<=length; i++)
  {
    Serial.print(p_data->buffer[i], HEX);
    Serial.print(F(", "));
  }
  Serial.println(F(""));
}


void m_rdy_line_handle(void)
{
  hal_aci_data_t *p_aci_data;
  
  sleep_disable();
  detachInterrupt(1);
  
  // Receive or transmit data
  p_aci_data = hal_aci_tl_poll_get();
  
  // Check if we received data
  if (p_aci_data->buffer[0] > 0)
  {
    if (!m_aci_q_enqueue(&aci_rx_q, p_aci_data))
    {
      /* Receive Buffer full.
         Should never happen.
         Spin in a while loop.
         */	  
       while(1);
    }
    if (m_aci_q_is_full(&aci_rx_q))
    {
      /* Disable RDY line interrupt.
         Will latch any pending RDY lines, so when enabled it again this
         routine should be taken again */
	  if (true == a_pins_local_ptr->interface_is_interrupt)
	  {
		EIMSK &= ~(0x2);
	  }
    }    
  }
}

bool hal_aci_tl_event_get(hal_aci_data_t *p_aci_data)
{
  bool was_full = m_aci_q_is_full(&aci_rx_q);
  
  if (m_aci_q_dequeue(&aci_rx_q, p_aci_data))
  {
    if (true == aci_debug_print)
    {
      Serial.print(" E");
      m_print_aci_data(p_aci_data);
    }
    
    if (was_full)
    {
	  if (true == a_pins_local_ptr->interface_is_interrupt)
	  {
		/* Enable RDY line interrupt again */
		EIMSK |= (0x2);
	  }
    }
    return true;
  }
  else
  {
    return false;
  }
}

void hal_aci_tl_init(aci_pins_t *a_pins)
{
  received_data.buffer[0] = 0;
  
  m_aci_pins_set(a_pins);
  
  /*
  The SPI lines used are mapped directly to the hardware SPI
  MISO MOSI and SCK
  Change here if the pins are mapped differently
  
  The SPI library assumes that the hardware pins are used
  */
  SPI.begin();
  SPI.setBitOrder(LSBFIRST);
  SPI.setClockDivider(a_pins->spi_clock_divider);
  SPI.setDataMode(SPI_MODE0);


  
  /* initialize aci cmd queue */
  m_aci_q_init(&aci_tx_q);  
  m_aci_q_init(&aci_rx_q);

  //Configure the IO lines
  pinMode(a_pins->rdyn_pin,		INPUT_PULLUP);
  pinMode(a_pins->reqn_pin,		OUTPUT);

  if (UNUSED != a_pins->active_pin)
  {
	pinMode(a_pins->active_pin,	INPUT);  
  }
  

  if (UNUSED != a_pins->reset_pin)
  {
	pinMode(a_pins->reset_pin,	OUTPUT);
	
	if (REDBEARLAB_SHIELD_V1_1 == a_pins->board_name)
	{
		//The reset for this board is inverted and has a Power On Reset
		//circuit that takes about 100ms to trigger the reset
		digitalWrite(a_pins->reset_pin, 1);
		delay(100);
		digitalWrite(a_pins->reset_pin, 0);		
	}
	else
	{
		digitalWrite(a_pins->reset_pin, 1);
		digitalWrite(a_pins->reset_pin, 0);		
		digitalWrite(a_pins->reset_pin, 1);
	}
	
  }
  
  
  digitalWrite(a_pins->miso_pin, 0);
  digitalWrite(a_pins->mosi_pin, 0);
  digitalWrite(a_pins->reqn_pin, 1);
  digitalWrite(a_pins->sck_pin,  0);  
  
  delay(30); //Wait for the nRF8001 to get hold of its lines - the lines float for a few ms after the reset
  
  //Attach the interrupt to the RDYN line as requested by the caller
  if (a_pins->interface_is_interrupt)
  {
	attachInterrupt(a_pins->interrupt_number, m_rdy_line_handle, LOW); // We use the LOW level of the RDYN line as the atmega328 can wakeup from sleep only on LOW  
  }
}

bool hal_aci_tl_send(hal_aci_data_t *p_aci_cmd)
{
  const uint8_t length = p_aci_cmd->buffer[0];
  bool ret_val = false;

  if (length > HAL_ACI_MAX_LENGTH)
  {
    return false;
  }
  else
  {
    if (m_aci_q_enqueue(&aci_tx_q, p_aci_cmd))
    {
      ret_val = true;
    }
  }

  if (true == aci_debug_print)
  {
    Serial.print("C");
    m_print_aci_data(p_aci_cmd);
  }
  
  digitalWrite(a_pins_local_ptr->reqn_pin, 0);
  return ret_val;
}



hal_aci_data_t * hal_aci_tl_poll_get(void)
{
  uint8_t byte_cnt;
  uint8_t byte_sent_cnt;
  uint8_t max_bytes;
  hal_aci_data_t data_to_send;


 
    

  digitalWrite(a_pins_local_ptr->reqn_pin, 0);
  
  // Receive from queue
  if (m_aci_q_dequeue(&aci_tx_q, &data_to_send) == false)
  {
    /* queue was empty, nothing to send */
    data_to_send.status_byte = 0;
    data_to_send.buffer[0] = 0;
  }
  
  //Change this if your mcu has DMA for the master SPI
  
  // Send length, receive header
  byte_sent_cnt = 0;
  received_data.status_byte = spi_readwrite(data_to_send.buffer[byte_sent_cnt++]);
  // Send first byte, receive length from slave
  received_data.buffer[0] = spi_readwrite(data_to_send.buffer[byte_sent_cnt++]);
  if (0 == data_to_send.buffer[0])
  {
    max_bytes = received_data.buffer[0];
  }
  else
  {
    // Set the maximum to the biggest size. One command byte is already sent
    max_bytes = (received_data.buffer[0] > (data_to_send.buffer[0] - 1)) 
      ? received_data.buffer[0] : (data_to_send.buffer[0] - 1);
  }

  if (max_bytes > HAL_ACI_MAX_LENGTH)
  {
    max_bytes = HAL_ACI_MAX_LENGTH;
  }

  // Transmit/receive the rest of the packet 
  for (byte_cnt = 0; byte_cnt < max_bytes; byte_cnt++)
  {
    received_data.buffer[byte_cnt+1] =  spi_readwrite(data_to_send.buffer[byte_sent_cnt++]);
  }

  digitalWrite(a_pins_local_ptr->reqn_pin, 1);

  //RDYN should follow the REQN line in approx 100ns
  
  sleep_enable();
  if (a_pins_local_ptr->interface_is_interrupt)
  {
	attachInterrupt(a_pins_local_ptr->interrupt_number, m_rdy_line_handle, LOW);	  
  }


  
  if (false == m_aci_q_is_empty(&aci_tx_q))
  {
    //Lower the REQN line to start a new ACI transaction         
    digitalWrite(a_pins_local_ptr->reqn_pin, 0); 
  }
  
  /* valid Rx available or transmit finished*/
  return (&received_data);
}

static uint8_t spi_readwrite(const uint8_t aci_byte)
{
	return SPI.transfer(aci_byte);
}

void m_aci_q_flush(void)
{
  noInterrupts();
  /* re-initialize aci cmd queue and aci event queue to flush them*/
  m_aci_q_init(&aci_tx_q);
  m_aci_q_init(&aci_rx_q);
  interrupts();
}

void m_aci_pins_set(aci_pins_t *a_pins_ptr)
{
  a_pins_local_ptr = a_pins_ptr;	
}