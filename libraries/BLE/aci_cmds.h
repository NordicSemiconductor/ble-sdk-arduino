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

/**
 * @file
 *
 * @ingroup aci
 *
 * @brief Definitions for the ACI (Application Control Interface) commands
 * @remarks
 *
 */

#ifndef ACI_CMDS_H__
#define ACI_CMDS_H__

/**
 * @enum aci_cmd_opcode_t
 * @brief ACI command opcodes
 */
typedef enum __attribute__ ((__packed__))
{
 /**
  * Enter test mode
  */
  ACI_CMD_TEST                    = 0x01,
 /**
  * Echo (loopback) test command
  */
  ACI_CMD_ECHO                    = 0x02,
 /**
  * Send a BTLE DTM command to the radio
  */
  ACI_CMD_DTM_CMD                 = 0x03,
  /**
  * Put the device to sleep
  */
  ACI_CMD_SLEEP                   = 0x04,
 /**
  * Wakeup the device from deep sleep
  */
  ACI_CMD_WAKEUP                  = 0x05,
 /**
  * Replace the contents of the internal database with
  * user provided data
  */
  ACI_CMD_SETUP                   = 0x06,
 /**
  * Read the portions of memory required to be restored after a power cycle
  */
  ACI_CMD_READ_DYNAMIC_DATA       = 0x07,
 /**
  * Write back the data retrieved using ACI_CMD_READ_DYNAMIC_DATA
  */
  ACI_CMD_WRITE_DYNAMIC_DATA      = 0x08,
  /**
  * Retrieve the device's version information
  */
  ACI_CMD_GET_DEVICE_VERSION      = 0x09,
 /**
  * Request the Bluetooth address and its type
  */
  ACI_CMD_GET_DEVICE_ADDRESS      = 0x0A,
  /**
  * Request the battery level measured by nRF8001
  */
  ACI_CMD_GET_BATTERY_LEVEL       = 0x0B,
 /**
  * Request the temperature value measured by nRF8001
  */
  ACI_CMD_GET_TEMPERATURE         = 0x0C,
 /**
  * Write to the local Attribute Database
  */
  ACI_CMD_SET_LOCAL_DATA          = 0x0D,
 /**
  * Reset the baseband and radio and go back to idle
  */
  ACI_CMD_RADIO_RESET          = 0x0E,
 /**
  * Start advertising and wait for a master connection
  */
  ACI_CMD_CONNECT                 = 0x0F,
 /**
  * Start advertising and wait for a master connection
  */
  ACI_CMD_BOND                    = 0x10,
 /**
  * Start advertising and wait for a master connection
  */
  ACI_CMD_DISCONNECT              = 0x11,
 /**
  * Throttles the Radio transmit power
  */
  ACI_CMD_SET_TX_POWER            = 0x12,
 /**
  * Trigger a connection parameter update
  */
  ACI_CMD_CHANGE_TIMING           = 0x13,
 /**
  * Open a remote pipe for data reception
  */
  ACI_CMD_OPEN_REMOTE_PIPE        = 0x14,
 /**
  * Transmit data over an open pipe
  */
  ACI_CMD_SEND_DATA               = 0x15,
 /**
  * Send an acknowledgment of received data
  */
  ACI_CMD_SEND_DATA_ACK           = 0x16,
 /**
  * Request data over an open pipe
  */
  ACI_CMD_REQUEST_DATA            = 0x17,
 /**
  * NACK a data reception
  */
  ACI_CMD_SEND_DATA_NACK          = 0x18,
 /**
  * Set application latency
  */
  ACI_CMD_SET_APP_LATENCY         = 0x19,
 /**
  * Set a security key
  */
  ACI_CMD_SET_KEY                 = 0x1A,
 /**
  * Open Advertising Pipes
  */
  ACI_CMD_OPEN_ADV_PIPE           = 0x1B,
 /**
  * Start non-connectable advertising
  */
  ACI_CMD_BROADCAST               = 0x1C,
 /**
  * Start a security request in bonding mode
  */
  ACI_CMD_BOND_SECURITY_REQUEST   = 0x1D,
 /**
  * Start Directed advertising towards a Bonded Peer
  */
  ACI_CMD_CONNECT_DIRECT          = 0x1E,
 /**
  * Close a previously opened remote pipe
  */
  ACI_CMD_CLOSE_REMOTE_PIPE       = 0x1F,
 /**
  * Invalid ACI command opcode
  */
  ACI_CMD_INVALID                 = 0xFF

} aci_cmd_opcode_t;

/**
 * @struct aci_cmd_params_test_t
 * @brief  Structure for the ACI_CMD_TEST ACI command parameters
 */
typedef struct __attribute__ ((__packed__))
{
  uint8_t test_mode_change; /**< enum aci_test_mode_change_t */
} aci_cmd_params_test_t;

/**
 * @struct aci_cmd_params_echo_t
 * @brief  Structure for the ACI_CMD_ECHO ACI command parameters
 */
typedef struct __attribute__ ((__packed__))
{
  uint8_t echo_data[ACI_ECHO_DATA_MAX_LEN];
} aci_cmd_params_echo_t;

/**
 * @struct aci_cmd_params_dtm_cmd_t
 * @brief  Structure for the ACI_CMD_DTM_CMD ACI command parameters
 */
typedef struct __attribute__ ((__packed__))
{
  uint8_t                 cmd_msb;
  uint8_t                 cmd_lsb;
} aci_cmd_params_dtm_cmd_t;

/**
 * @struct aci_cmd_params_setup_t
 * @brief  Structure for the ACI_CMD_SETUP ACI command parameters
 */
typedef struct __attribute__ ((__packed__))
{
  uint8_t                 setup_data[1];
} aci_cmd_params_setup_t;

/**
 * @struct aci_cmd_params_write_dynamic_data_t
 * @brief  Structure for the ACI_CMD_WRITE_DYNAMIC_DATA ACI command parameters 
 * @note Dynamic data chunk size in this command is defined to go up to ACI_PACKET_MAX_LEN - 3
 */
typedef struct __attribute__ ((__packed__))
{
  uint8_t                 seq_no;
  uint8_t                 dynamic_data[1];
} aci_cmd_params_write_dynamic_data_t;

/**
 * @define aci_cmd_params_set_local_data_t
 * @brief  Structure for the ACI_CMD_SET_LOCAL_DATA ACI command parameters
 */
typedef struct __attribute__ ((__packed__))
{
  aci_tx_data_t tx_data;
} aci_cmd_params_set_local_data_t;

/**
 * @struct aci_cmd_params_connect_t
 * @brief  Structure for the ACI_CMD_CONNECT ACI command parameters
 */
typedef struct __attribute__ ((__packed__))
{
  uint16_t        timeout;  /**< 0x0000 (no timeout) to 0x3FFF */
  uint16_t        adv_interval;     /**< 16 bits of advertising interval for general discovery */
} aci_cmd_params_connect_t;

/**
 * @define aci_cmd_params_bond_t
 * @brief  Structure for the ACI_CMD_BOND ACI command parameters
 */
typedef struct __attribute__ ((__packed__))
{
  uint16_t        timeout;  /**< 0x0000 (no timeout) to 0x3FFF */
  uint16_t        adv_interval;     /**< 16 bits of advertising interval for general discovery */
} aci_cmd_params_bond_t;

/**
 * @struct aci_cmd_params_disconnect_t
 * @brief  Structure for the ACI_CMD_DISCONNECT ACI command parameters
 */
typedef struct __attribute__ ((__packed__))
{
  uint8_t         reason; /**< enum aci_disconnect_reason_t */
} aci_cmd_params_disconnect_t;

/**
 * @struct aci_cmd_params_set_tx_power_t
 * @brief  Structure for the ACI_CMD_SET_TX_POWER ACI command parameters
 */
typedef struct __attribute__ ((__packed__))
{
  uint8_t   device_power; /**< enum aci_device_output_power_t */
} aci_cmd_params_set_tx_power_t;

/**
 * @struct aci_cmd_params_change_timing_t
 * @brief  Structure for the ACI_CMD_CHANGE_TIMING ACI command parameters
 */
typedef struct __attribute__ ((__packed__))
{
  aci_ll_conn_params_t    conn_params;
} aci_cmd_params_change_timing_t;

/**
 * @struct aci_cmd_params_open_remote_pipe_t
 * @brief  Structure for the ACI_CMD_OPEN_REMOTE_PIPE ACI command parameters
 */
typedef struct __attribute__ ((__packed__))
{
  uint8_t pipe_number;
} aci_cmd_params_open_remote_pipe_t;

/**
 * @struct aci_cmd_params_send_data_t
 * @brief  Structure for the ACI_CMD_SEND_DATA ACI command parameters
 */
typedef struct __attribute__ ((__packed__))
{
  aci_tx_data_t tx_data;
} aci_cmd_params_send_data_t;

/**
 * @define aci_cmd_params_send_data_ack_t
 * @brief  Structure for the ACI_CMD_SEND_DATA_ACK ACI command parameters
 */
typedef struct __attribute__ ((__packed__))
{
  uint8_t pipe_number;
} aci_cmd_params_send_data_ack_t;

/**
 * @struct aci_cmd_params_send_data_t
 * @brief  Structure for the ACI_CMD_SEND_DATA ACI command parameters
 */
typedef struct __attribute__ ((__packed__))
{
  uint8_t pipe_number;
} aci_cmd_params_request_data_t;

/**
 * @define aci_cmd_params_send_data_nack_t
 * @brief  Structure for the ACI_CMD_SEND_DATA_NACK ACI command parameters
 */
typedef struct __attribute__ ((__packed__))
{
  uint8_t pipe_number;
  uint8_t error_code;
} aci_cmd_params_send_data_nack_t;

/**
 * @define aci_cmd_params_set_app_latency_t
 * @brief  Structure for the ACI_CMD_SET_APP_LATENCY ACI command parameters
 */
typedef struct __attribute__ ((__packed__))
{
  aci_app_latency_mode_t mode;
  uint16_t latency;
} aci_cmd_params_set_app_latency_t;

/**
 * @define aci_cmd_params_set_key_t
 * @brief  Structure for the ACI_CMD_SET_KEY ACI command parameters
 */
typedef struct __attribute__ ((__packed__))
{
  aci_key_type_t key_type;
  union
  {
    uint8_t passkey[6];
    uint8_t oob_key[16];
  } key;
} aci_cmd_params_set_key_t;

/**
 * @define aci_cmd_params_open_adv_pipe_t
 * @brief  Structure for the ACI_CMD_OPEN_ADV_PIPE ACI command parameters
 */
typedef struct __attribute__ ((__packed__))
{
  uint8_t pipes[8];
} aci_cmd_params_open_adv_pipe_t;

/**
 * @define aci_cmd_params_broadcast_t
 * @brief  Structure for the ACI_CMD_BROADCAST ACI command parameters
 */
typedef struct __attribute__ ((__packed__))
{
  uint16_t        timeout;  /**< 0x0000 (no timeout) to 0x3FFF */
  uint16_t        adv_interval;     /**< 16 bits of advertising interval for general discovery */
} aci_cmd_params_broadcast_t;

/**
 * @struct aci_cmd_params_close_remote_pipe_t
 * @brief  Structure for the ACI_CMD_CLOSE_REMOTE_PIPE ACI command parameters
 */
typedef struct __attribute__ ((__packed__))
{
  uint8_t pipe_number;
} aci_cmd_params_close_remote_pipe_t;

/**
 * @struct aci_cmd_t
 * @brief  Encapsulates a generic ACI command
 */
typedef struct __attribute__ ((__packed__))
{
  uint8_t len;        /**< Length of the ACI command */
  uint8_t cmd_opcode; /**< enum aci_cmd_opcode_t -> Opcode of the ACI command */
  union
  {
    aci_cmd_params_test_t                       test;
    aci_cmd_params_echo_t                       echo;
    aci_cmd_params_dtm_cmd_t                    dtm_cmd;
    aci_cmd_params_setup_t                      setup;
    aci_cmd_params_write_dynamic_data_t         write_dynamic_data;
    aci_cmd_params_set_local_data_t             set_local_data;
    aci_cmd_params_connect_t                    connect;
    aci_cmd_params_bond_t                       bond;
    aci_cmd_params_disconnect_t                 disconnect;
    aci_cmd_params_set_tx_power_t               set_tx_power;
    aci_cmd_params_change_timing_t              change_timing;
    aci_cmd_params_open_remote_pipe_t           open_remote_pipe;
    aci_cmd_params_send_data_t                  send_data;
    aci_cmd_params_send_data_ack_t              send_data_ack;
    aci_cmd_params_request_data_t               request_data;
    aci_cmd_params_send_data_nack_t             send_data_nack;
    aci_cmd_params_set_app_latency_t            set_app_latency;
    aci_cmd_params_set_key_t                    set_key;
    aci_cmd_params_open_adv_pipe_t              open_adv_pipe;
    aci_cmd_params_broadcast_t                  broadcast;
    aci_cmd_params_close_remote_pipe_t          close_remote_pipe;

  } params;
} aci_cmd_t;

#endif // ACI_CMDS_H__


