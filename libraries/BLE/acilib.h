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

#ifndef _acilib_H_
#define _acilib_H_

#define MSG_SET_LOCAL_DATA_BASE_LEN              2
#define MSG_CONNECT_LEN                          5
#define MSG_BOND_LEN                             5
#define MSG_DISCONNECT_LEN                       2
#define MSG_BASEBAND_RESET_LEN                   1
#define MSG_WAKEUP_LEN                           1
#define MSG_SET_RADIO_TX_POWER_LEN               2
#define MSG_GET_DEVICE_ADDR_LEN                  1
#define MSG_SEND_DATA_BASE_LEN                   2
#define MSG_DATA_REQUEST_LEN                     2
#define MSG_OPEN_REMOTE_PIPE_LEN                 2
#define MSG_CLOSE_REMOTE_PIPE_LEN                2
#define MSG_DTM_CMD                              3
#define MSG_WRITE_DYNAMIC_DATA_BASE_LEN          2
#define MSG_SETUP_CMD_BASE_LEN                   1
#define MSG_ECHO_MSG_CMD_BASE_LEN                1
#define MSG_CHANGE_TIMING_LEN                    9
#define MSG_SET_APP_LATENCY_LEN                  4
#define MSG_CHANGE_TIMING_LEN_GAP_PPCP           1
#define MSG_DIRECT_CONNECT_LEN                   1
#define MSG_SET_KEY_REJECT_LEN                   2
#define MSG_SET_KEY_PASSKEY_LEN                  8
#define MSG_SET_KEY_OOB_LEN                      18
#define MSG_ACK_LEN                              2
#define MSG_NACK_LEN                             3
#define MSG_BROADCAST_LEN                        5
#define MSG_OPEN_ADV_PIPES_LEN                   9

#endif /* _acilib_H_ */
