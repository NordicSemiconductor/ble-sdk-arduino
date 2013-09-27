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
 * @ingroup group_acilib
 *
 * @brief Internal prototype for acilib module.
 */

#ifndef DTM_H__
#define DTM_H__

/** @brief DTM command codes (upper two bits in the DTM command), use a bitwise OR with the frequency N = 0x00 – 0x27: N = (F-2402)/2 Frequency Range 2402 MHz
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
