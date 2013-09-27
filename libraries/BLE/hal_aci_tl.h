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

/** @file
 * @brief Interface for hal_aci_tl.
 */
 
/** @defgroup hal_aci_tl hal_aci_tl
@{
@ingroup hal
 
@brief Module for the ACI Transport Layer interface
@details This module is responsible for sending and receiving messages over the ACI interface of the nRF8001 chip.
 The hal_aci_tl_send_cmd() can be called directly to send ACI commands.


The RDYN line is hooked to an interrupt on the MCU when the level is low.
The SPI master clocks in the interrupt context.
The ACI Command is taken from the head of the command queue is sent over the SPI
and the received ACI event is placed in the tail of the event queue.

*/
 
#ifndef HAL_ACI_TL_H__
#define HAL_ACI_TL_H__

#include "hal_platform.h"
#include "boards.h"

#ifndef HAL_ACI_MAX_LENGTH
#define HAL_ACI_MAX_LENGTH 31
#endif

/***********************************************************************    */
/* The ACI_QUEUE_SIZE determines the memory usage of the system.            */
/* Successfully tested to a ACI_QUEUE_SIZE of 4 (interrupt) and 4 (polling) */
/***********************************************************************    */
#define ACI_QUEUE_SIZE  2

/************************************************************************/
/* Unused nRF8001 pin                                                    */
/************************************************************************/
#define UNUSED		    255 

/** Data type for ACI commands and events */
typedef struct __attribute__ ((__packed__)) hal_aci_data_t{
  uint8_t status_byte;
  uint8_t buffer[HAL_ACI_MAX_LENGTH+1];
} hal_aci_data_t;

typedef struct {
	hal_aci_data_t           aci_data[ACI_QUEUE_SIZE];
	uint8_t                  head;
	uint8_t                  tail;
} aci_queue_t;


/** Datatype for ACI pins and interface (polling/interrupt)*/
typedef struct aci_pins_t
{
	uint8_t board_name;             //Optional : Use BOARD_DEFAULT if you do not know. See boards.h
	uint8_t	reqn_pin;				//Required
	uint8_t	rdyn_pin;				//Required
	uint8_t	mosi_pin;				//Required
	uint8_t	miso_pin;				//Required
	uint8_t	sck_pin;				//Required
	
	uint8_t spi_clock_divider;      //Required : Clock divider on the SPI clock : nRF8001 supports a maximum clock of 3MHz
	
	
	uint8_t	reset_pin;				//Recommended but optional - Set it to UNUSED when not connected
	uint8_t active_pin;				//Optional - Set it to UNUSED when not connected
	uint8_t optional_chip_sel_pin;  //Optional - Used only when the reqn line is required to be separate from the SPI chip select. Eg. Arduino DUE
	
	bool	interface_is_interrupt;	//Required - true = Uses interrupt on RDYN pin. false - Uses polling on RDYN pin
	
	uint8_t	interrupt_number;		//Required when using interrupts, otherwise ignored
} aci_pins_t;

/** @brief Message received hook function.
 *  @details A hook function that must be implemented by the client of this module. 
 * The function will be called by this module when a new message has been received from the nRF8001.
 *  @param received_msg Pointer to a structure containing a pointer to the received data.
 */
extern void hal_aci_tl_msg_rcv_hook(hal_aci_data_t *received_msg);

/** ACI Transport Layer configures inputs/outputs.
 */
void hal_aci_tl_io_config(void);


/** ACI Transport Layer initialization.
 */
void hal_aci_tl_init(aci_pins_t *a_pins);

/**@brief Sends an ACI command to the radio.
 *  @details
 *  This function sends an ACI command to the radio. This will memorize the pointer of the message to send and 
 *  lower the request line. When the device lowers the ready line, @ref hal_aci_tl_poll_rdy_line() will send the data.
 *  @param aci_buffer Pointer to the message to send.
 *  @return True if the send is started successfully, false if a transaction is already running.
 */
bool hal_aci_tl_send(hal_aci_data_t *aci_buffer);


/** @brief Check for pending transaction.
 *  @details 
 *  Call this function from the main context at regular intervals to check if the nRF8001 RDYN line indicates a pending transaction.
 *  If a transaction is pending, this function will treat it and call the receive hook.
 */
void hal_aci_tl_poll_rdy_line(void);

hal_aci_data_t * hal_aci_tl_poll_get(void);

/** @brief Get an ACI event from the event queue
 *  @details 
 *  Call this function from the main context to get an event from the ACI event queue
 *  This is called by lib_aci_event_get
 */
bool hal_aci_tl_event_get(hal_aci_data_t *p_aci_data);

/** @brief Flush the ACI command Queue and the ACI Event Queue
 *  @details
 *  Call this function in the main thread
*/
void m_aci_q_flush(void);

/** @brief Enable debug printing of all ACI commands sent and ACI events received
 *  @details
 *  when the enable parameter is true. The debug printing is enabled on the Serial.
 *  When the enable parameter is false. The debug printing is disabled on the Serial.
 *  By default the debug printing is disabled.
*/
void hal_aci_debug_print(bool enable);

/** @brief 
 *  @details
 *
*/
void m_rdy_line_handle(void);

/** @brief Is the queue empty
 *  @details
 *
*/
bool m_aci_q_is_empty(aci_queue_t *aci_q);

/** @brief Is the queue full
 *  @details
 *

*/

bool m_aci_q_is_full(aci_queue_t *aci_q);


/** @brief Enqueue an ACI event. Used to workaround boards that do not have access to the Reset pin
 *  @details
 *

*/
bool m_aci_q_enqueue(aci_queue_t *aci_q, hal_aci_data_t *p_data);

/** @brief Point the low level library at the ACI pins specified					  */
/*  @details																		  */
/*  The ACI pins are specified in the application and a pointer is made available for */
/*  the low level library to use                                                                    */
/************************************************************************/
void m_aci_pins_set(aci_pins_t *a_pins_ptr);

#endif // HAL_ACI_TL_H__
/** @} */




