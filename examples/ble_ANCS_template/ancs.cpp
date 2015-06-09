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
 
#include <hal_platform.h>
#include "services.h"
#include "lib_aci.h"
#include "ancs.h"


void ancs_notification_evt_rcvd(uint8_t pipe_num, uint8_t *buffer)
{
    Serial.print(F("PIPE_ANCS_NOTIFICATION_SOURCE_RX: "));
      for(uint8_t counter = 0; counter <= 20; counter++)
      {
        Serial.write(buffer[counter]); //uint8_t file_name[20];
      }
      Serial.println();
}
    
void ancs_data_evt_rcvd(uint8_t pipe_num, uint8_t *buffer)
{
      Serial.print(F("PIPE_ANCS_DATA_SOURCE_RX: "));
      for(uint8_t counter = 0; counter <= ACI_PIPE_RX_DATA_MAX_LEN; counter++)
      {
        Serial.write(buffer[counter]); //uint8_t file_name[20];
      }
      Serial.println();

}

