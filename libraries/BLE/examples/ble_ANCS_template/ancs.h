/* Copyright (c) 2014, Nordic Semiconductor ASA
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
 
 #include <stdint.h>

#define ANCS_ATTRIBUTE_DATA_MAX                     32                                   /*<< Maximium notification attribute data length. */

/**@brief Category IDs for iOS notifications. */
typedef enum
{
    BLE_ANCS_CATEGORY_ID_OTHER,
    BLE_ANCS_CATEGORY_ID_INCOMING_CALL,
    BLE_ANCS_CATEGORY_ID_MISSED_CALL,
    BLE_ANCS_CATEGORY_ID_VOICE_MAIL,
    BLE_ANCS_CATEGORY_ID_SOCIAL,
    BLE_ANCS_CATEGORY_ID_SCHEDULE,
    BLE_ANCS_CATEGORY_ID_EMAIL,
    BLE_ANCS_CATEGORY_ID_NEWS,
    BLE_ANCS_CATEGORY_ID_HEALTH_AND_FITNESS,
    BLE_ANCS_CATEGORY_ID_BUSINESS_AND_FINANCE,
    BLE_ANCS_CATEGORY_ID_LOCATION,
    BLE_ANCS_CATEGORY_ID_ENTERTAINMENT
} ble_ancs_category_id_values_t;

/**@brief Event IDs for iOS notifications. */
typedef enum
{
    BLE_ANCS_EVENT_ID_NOTIFICATION_ADDED,
    BLE_ANCS_EVENT_ID_NOTIFICATION_MODIFIED,
    BLE_ANCS_EVENT_ID_NOTIFICATION_REMOVED
} ble_ancs_event_id_values_t;

/**@brief Control point command IDs. */
typedef enum
{
    BLE_ANCS_COMMAND_ID_GET_NOTIFICATION_ATTRIBUTES,
    BLE_ANCS_COMMAND_ID_GET_APP_ATTRIBUTES
} ble_ancs_command_id_values_t;

/**@brief Event flags for iOS notifications. */
#define BLE_ANCS_EVENT_FLAG_SILENT                (1 << 0)
#define BLE_ANCS_EVENT_FLAG_IMPORTANT             (1 << 1)

/**@brief Notification attribute IDs. */
typedef enum
{
    BLE_ANCS_NOTIFICATION_ATTRIBUTE_ID_APP_IDENTIFIER,
    BLE_ANCS_NOTIFICATION_ATTRIBUTE_ID_TITLE,
    BLE_ANCS_NOTIFICATION_ATTRIBUTE_ID_SUBTITLE,
    BLE_ANCS_NOTIFICATION_ATTRIBUTE_ID_MESSAGE,
    BLE_ANCS_NOTIFICATION_ATTRIBUTE_ID_MESSAGE_SIZE,
    BLE_ANCS_NOTIFICATION_ATTRIBUTE_ID_DATE,
} ble_ancs_notification_attribute_id_values_t;

typedef struct {
    uint8_t                            event_id;
    uint8_t                            event_flags;
    uint8_t                            category_id;
    uint8_t                            category_count;
    uint8_t                            notification_uid[4];
} ble_ancs_c_evt_ios_notification_t;

typedef struct {
    uint8_t                            command_id;
    uint8_t                            notification_uid[4];
    uint8_t                            attribute_id;
    uint16_t                           attribute_len;
    uint8_t                            data[ANCS_ATTRIBUTE_DATA_MAX];
} ble_ancs_c_evt_notif_attribute_t;

typedef struct {
    uint8_t                            attribute_id;
    uint16_t                           attribute_len;
} ble_ancs_attr_list_t;

 /** @brief Function to handle reception of data for ANCS.
 *  @details Call this function on the ACI_EVT_DATA_RECEIVED event. This function checks if the data received is for ANCS.
 *  If so it prints the received data to the Serial interface.
 *  @param pipe_num Pipe which has received data.
 *  @param buffer Pointer to the received data.
 */
 void ancs_notification_evt_rcvd(uint8_t pipe_num, uint8_t *buffer);
 
void ancs_data_evt_rcvd(uint8_t pipe_num, uint8_t *buffer);
