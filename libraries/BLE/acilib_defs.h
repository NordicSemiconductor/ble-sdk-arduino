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
 * @brief Definitions for the acilib interfaces
 */

#ifndef _acilib_DEFS_H_
#define _acilib_DEFS_H_

#define ACIL_DECODE_EVT_GET_LENGTH(buffer_in) (*(buffer_in + OFFSET_ACI_EVT_T_LEN))

#define ACIL_DECODE_EVT_GET_OPCODE(buffer_in) (*(buffer_in + OFFSET_ACI_EVT_T_EVT_OPCODE))

#endif /* _acilib_DEFS_H_ */
