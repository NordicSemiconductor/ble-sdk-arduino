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

/**
 * @file
 *
 * @ingroup aci
 *
 * @brief Definitions for the ACI (Application Control Interface) events
 */

#ifndef ACI_EVTS_H__
#define ACI_EVTS_H__

/**
 * @enum aci_evt_opcode_t
 * @brief ACI event opcodes
 */
typedef enum __attribute__ ((__packed__))
{
 /**
  * Invalid event code
  */
  ACI_EVT_INVALID                     = 0x00,
 /**
  * Sent every time the device starts
  */
  ACI_EVT_DEVICE_STARTED              = 0x81,
 /**
  * Mirrors the ACI_CMD_ECHO
  */
  ACI_EVT_ECHO                        = 0x82,
 /**
  * Asynchronous hardware error event
  */
  ACI_EVT_HW_ERROR                  = 0x83,
 /**
  * Event opcode used as a event response for all commands
  */
  ACI_EVT_CMD_RSP                     = 0x84,
 /**
  * Link connected
  */
  ACI_EVT_CONNECTED                   = 0x85,
 /**
  * Link disconnected
  */
  ACI_EVT_DISCONNECTED                = 0x86,
 /**
  * Bond completion result
  */
  ACI_EVT_BOND_STATUS                 = 0x87,
  /**
  * Pipe bitmap for available pipes
  */
  ACI_EVT_PIPE_STATUS             = 0x88,
 /**
  * Sent to the application when the radio enters a connected state
  * or when the timing of the radio connection changes
  */
  ACI_EVT_TIMING                      = 0x89,
 /**
  * Notification to the application that transmit credits are
  * available
  */
  ACI_EVT_DATA_CREDIT                 = 0x8A,
 /**
  * Data acknowledgement event
  */
  ACI_EVT_DATA_ACK                    = 0x8B,
 /**
  * Data received notification event
  */
  ACI_EVT_DATA_RECEIVED               = 0x8C,
 /**
  * Error notification event
  */
  ACI_EVT_PIPE_ERROR                  = 0x8D,
 /**
  * Display Passkey Event
  */
  ACI_EVT_DISPLAY_PASSKEY             = 0x8E,
 /**
  * Security Key request
  */
  ACI_EVT_KEY_REQUEST                 = 0x8F

} aci_evt_opcode_t;

/**
 * @struct aci_evt_params_device_started_t
 * @brief Structure for the ACI_EVT_DEVICE_STARTED event return parameters
 */
typedef struct __attribute__ ((__packed__))
{
  uint8_t device_mode; /**< enum aci_device_operation_mode_t -> Mode in which the device is being started */
  uint8_t hw_error;  /**< enum aci_hw_error_t -> Hardware Error if available for the start */
  uint8_t credit_available; /**< Flow control credit available for this specific FW build */
} aci_evt_params_device_started_t;

/**
 * @struct aci_evt_params_hw_error_t
 * @brief Structure for the ACI_EVT_HW_ERROR event return parameters
 */
typedef struct __attribute__ ((__packed__))
{
  uint16_t line_num;
  uint8_t file_name[20];
} aci_evt_params_hw_error_t;

/**
 * @struct aci_evt_cmd_rsp_params_dtm_cmd_t
 * @brief Structure for the ACI_EVT_CMD_RSP event with opcode=ACI_CMD_DTM_CMD event return parameters
 */
typedef struct __attribute__ ((__packed__))
{
  uint8_t  evt_msb;
  uint8_t  evt_lsb;
} aci_evt_cmd_rsp_params_dtm_cmd_t;

/**
 * @struct aci_evt_cmd_rsp_read_dynamic_data_t
 * @brief Structure for the ACI_EVT_CMD_RSP event with opcode=ACI_CMD_READ_DYNAMIC_DATA event return parameters
 * @note Dynamic data chunk size in this event is defined to go up to ACI_PACKET_MAX_LEN - 5
 */
typedef struct __attribute__ ((__packed__))
{
  uint8_t seq_no;
  uint8_t dynamic_data[1];
} aci_evt_cmd_rsp_read_dynamic_data_t;

/**
 * @struct aci_evt_cmd_rsp_params_get_device_version_t
 * @brief Structure for the ACI_EVT_CMD_RSP event with opcode=ACI_CMD_GET_DEVICE_VERSION event return parameters
 */
typedef struct __attribute__ ((__packed__))
{
  uint16_t  configuration_id;
  uint8_t   aci_version;
  uint8_t   setup_format;
  uint32_t  setup_id;
  uint8_t   setup_status;
} aci_evt_cmd_rsp_params_get_device_version_t;

/**
 * @struct aci_evt_cmd_rsp_params_get_device_address_t
 * @brief Structure for the ACI_EVT_CMD_RSP event with opcode=ACI_CMD_GET_DEVICE_ADDRESS event return parameters
 */
typedef struct __attribute__ ((__packed__))
{
  uint8_t bd_addr_own[BTLE_DEVICE_ADDRESS_SIZE];
  uint8_t bd_addr_type; /**< enum aci_bd_addr_type_t */
} aci_evt_cmd_rsp_params_get_device_address_t;

/**
 * @struct aci_evt_cmd_rsp_params_get_battery_level_t
 * @brief Structure for the ACI_EVT_CMD_RSP event with opcode=ACI_CMD_GET_BATTERY_LEVEL event return parameters
 */
typedef struct __attribute__ ((__packed__))
{
  uint16_t battery_level;
} aci_evt_cmd_rsp_params_get_battery_level_t;

/**
 * @struct aci_evt_cmd_rsp_params_get_temperature_t
 * @brief Structure for the ACI_EVT_CMD_RSP event with opcode=ACI_CMD_GET_TEMPERATURE event return parameters
 */
typedef struct __attribute__ ((__packed__))
{
  int16_t temperature_value;
} aci_evt_cmd_rsp_params_get_temperature_t;

/**
 * @struct aci_evt_params_cmd_rsp_t
 * @brief Structure for the ACI_EVT_CMD_RSP event return parameters
 */
typedef struct __attribute__ ((__packed__))
{
  uint8_t cmd_opcode; /**< enum aci_cmd_opcode_t -> Command opcode for which the event response is being sent */
  uint8_t cmd_status; /**< enum aci_status_code_t -> Status of the command that was sent. Used in the context of the command. */
  union
  {
    aci_evt_cmd_rsp_params_dtm_cmd_t dtm_cmd;
    aci_evt_cmd_rsp_read_dynamic_data_t read_dynamic_data;
    aci_evt_cmd_rsp_params_get_device_version_t get_device_version;
    aci_evt_cmd_rsp_params_get_device_address_t get_device_address;
    aci_evt_cmd_rsp_params_get_battery_level_t  get_battery_level;
    aci_evt_cmd_rsp_params_get_temperature_t    get_temperature;
    uint8_t                                     padding[29];  
  } params;
} aci_evt_params_cmd_rsp_t;

/**
 * @struct aci_evt_params_connected_t
 * @brief Structure for the ACI_EVT_CONNECTED event return parameters
 */
typedef struct __attribute__ ((__packed__))
{
  aci_bd_addr_type_t dev_addr_type;
  uint8_t  dev_addr[BTLE_DEVICE_ADDRESS_SIZE];
  uint16_t conn_rf_interval;  /**< rf_interval = conn_rf_interval * 1.25 ms Range:0x0006 to 0x0C80 */
  uint16_t conn_slave_rf_latency; /**< Number of RF events the slave can skip */
  uint16_t conn_rf_timeout; /**< Timeout as a multiple of 10ms i.e timeout = conn_rf_timeout * 10ms Range: 0x000A to 0x0C80 */
  uint8_t master_clock_accuracy; /**< enum aci_clock_accuracy_t -> Clock accuracy of Bluetooth master: Enumerated list of values from 500 ppm to 20 ppm */
} aci_evt_params_connected_t;

/**
 * @struct aci_evt_params_disconnected_t
 * @brief Structure for the ACI_EVT_DISCONNECTED event return parameters
 */
typedef struct __attribute__ ((__packed__))
{
  uint8_t aci_status; /**< enum aci_status_code_t */
  uint8_t btle_status;
} aci_evt_params_disconnected_t;

/**
 * @struct aci_evt_params_bond_status_t
 * @brief Structure for the ACI_EVT_BOND_STATUS event return parameters
 */
typedef struct __attribute__ ((__packed__))
{
  uint8_t status_code;
  uint8_t status_source; /**< enum aci_bond_status_source_t */
  uint8_t secmode1_bitmap;
  uint8_t secmode2_bitmap;
  uint8_t keys_exchanged_slave;
  uint8_t keys_exchanged_master;
} aci_evt_params_bond_status_t;

/**
 * @struct aci_evt_params_pipe_status_t
 * @brief Structure for the ACI_EVT_PIPE_STATUS event return parameters
 */
typedef struct __attribute__ ((__packed__))
{
  uint8_t  pipes_open_bitmap[8];
  uint8_t  pipes_closed_bitmap[8];
} aci_evt_params_pipe_status_t;

/**
 * @struct aci_evt_params_timing_t
 * @brief Structure for the ACI_EVT_TIMING event return parameters
 */
typedef struct __attribute__ ((__packed__))
{
  uint16_t conn_rf_interval;  /**< rf_interval = conn_rf_interval * 1.25 ms Range:0x0006 to 0x0C80 */
  uint16_t conn_slave_rf_latency; /**< Number of RF events the slave can skip */
  uint16_t conn_rf_timeout; /**< Timeout as a multiple of 10ms i.e timeout = conn_rf_timeout * 10ms Range: 0x000A to 0x0C80 */
} aci_evt_params_timing_t;

/**
 * @struct aci_evt_params_data_credit_t
 * @brief Structure for the ACI_EVT_DATA_CREDIT event return parameters
 */
typedef struct __attribute__ ((__packed__))
{
  uint8_t credit;
} aci_evt_params_data_credit_t;

/**
 * @struct aci_evt_params_data_ack_t
 * @brief Structure for the ACI_EVT_DATA_ACK event return parameters
 */
typedef struct __attribute__ ((__packed__))
{
  uint8_t pipe_number;
} aci_evt_params_data_ack_t;

/**
 * @struct aci_evt_params_data_received_t
 * @brief Structure for the ACI_EVT_DATA_RECEIVED event return parameters
 */
typedef struct __attribute__ ((__packed__))
{
  aci_rx_data_t rx_data;
} aci_evt_params_data_received_t;

typedef struct __attribute__ ((__packed__))
{
  uint8_t content[1];
} error_data_t;

/**
 * @struct aci_evt_params_pipe_error_t
 * @brief Structure for the ACI_EVT_PIPE_ERROR event return parameters
 */
typedef struct __attribute__ ((__packed__))
{
  uint8_t pipe_number;
  uint8_t error_code;
  union 
  {
    error_data_t  error_data;
  } params;
} aci_evt_params_pipe_error_t;

/**
 * @struct aci_evt_params_display_passkey_t
 * @brief Structure for the ACI_EVT_DISPLAY_PASSKEY event return parameters
 */
typedef struct __attribute__ ((__packed__))
{
  uint8_t passkey[6];
} aci_evt_params_display_passkey_t;

/**
 * @struct aci_evt_params_key_request_t
 * @brief Structure for the ACI_EVT_KEY_REQUEST event return parameters
 */
typedef struct __attribute__ ((__packed__))
{
  uint8_t key_type; /**< enum aci_key_type_t */
} aci_evt_params_key_request_t;

/**
 * @struct aci_event_params_echo_t
 * @brief  Structure for the ACI_EVT_ECHO ACI event parameters
 */
typedef struct __attribute__ ((__packed__))
{
  uint8_t echo_data[ACI_ECHO_DATA_MAX_LEN];
} aci_evt_params_echo_t;

/**
 * @struct aci_evt_t
 * @brief  Encapsulates a generic ACI event
 */
typedef struct __attribute__ ((__packed__))
{
  uint8_t len;
  uint8_t evt_opcode; /** enum aci_evt_opcode_t */
  union
  {
    aci_evt_params_device_started_t                     device_started;
    aci_evt_params_echo_t                               echo;
    aci_evt_params_hw_error_t                           hw_error;
    aci_evt_params_cmd_rsp_t                            cmd_rsp;
    aci_evt_params_connected_t                          connected;
    aci_evt_params_disconnected_t                       disconnected;
    aci_evt_params_bond_status_t                        bond_status;
    aci_evt_params_pipe_status_t                        pipe_status;
    aci_evt_params_timing_t                             timing;
    aci_evt_params_data_credit_t                        data_credit;
    aci_evt_params_data_ack_t                           data_ack;
    aci_evt_params_data_received_t                      data_received;
    aci_evt_params_pipe_error_t                         pipe_error;
    aci_evt_params_display_passkey_t                    display_passkey;
    aci_evt_params_key_request_t                        key_request;
  } params;
} aci_evt_t;

#endif // ACI_EVTS_H__
