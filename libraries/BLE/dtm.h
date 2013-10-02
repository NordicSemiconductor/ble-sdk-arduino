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
 * @ingroup group_acilib
 *
 * @brief Internal prototype for acilib module.
 */

#ifndef DTM_H__
#define DTM_H__

/** @brief DTM command codes (upper two bits in the DTM command), use a bitwise OR with the frequency N = 0x00 � 0x27: N = (F-2402)/2 Frequency Range 2402 MHz
to 2480 MHz*/
#define DTM_LE_CMD_RESET            0x00
#define DTM_LE_CMD_RECEIVER_TEST    0x40
#define DTM_LE_CMD_TRANSMITTER_TEST 0x80
#define DTM_LE_CMD_TEST_END         0xC0


/** @brief Defined packet types for DTM */
#define DTM_LE_PKT_PRBS9      0x00       /**< Bit pattern PRBS9.    */
#define DTM_LE_PKT_0X0F       0x01       /**< Bit pattern 11110000 (LSB is the leftmost bit). */
#define DTM_LE_PKT_0X55       0x02       /**< Bit pattern 10101010 (LSB is the leftmost bit). */
#define DTM_LE_PKT_VENDOR     0x03       /**< Vendor specific. Nordic: continous carrier test */

/** @brief Defined bit fields for DTM responses. */
#define LE_PACKET_REPORTING_EVENT_MSB_BIT   0x80
#define LE_TEST_STATUS_EVENT_LSB_BIT        0x01

/** @brief DTM response types. */
#define LE_TEST_STATUS_EVENT                0x00
#define LE_TEST_PACKET_REPORT_EVENT         0x80

/** @brief DTM return values. */
#define LE_TEST_STATUS_SUCCESS              0x00
#define LE_TEST_STATUS_FAILURE              0x01



#endif //DTM_H__

/** @} */
