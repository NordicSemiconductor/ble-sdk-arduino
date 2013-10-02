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

/* Attention! 
*  To maintain compliance with Nordic Semiconductor ASA's Bluetooth profile 
*  qualification listings, this section of source code must not be modified.
*/


#include <hal_platform.h>
#include "alert_level_characteristic.h"
#include "services.h"
#include "lib_aci.h"
#include "link_loss.h"

/*link loss Service */
volatile alert_level_t alert_handle_on_link_loss;

void link_loss_init(void)
{
  alert_handle_on_link_loss = ALERT_LEVEL_NO_ALERT;
}

void proximity_disconect_evt_rcvd(uint8_t disconnect_reason)
{
  if ((DISCONNECT_REASON_CX_CLOSED_BY_PEER_DEVICE != disconnect_reason)&&(DISCONNECT_REASON_CX_CLOSED_BY_LOCAL_DEVICE != disconnect_reason))
  {
    link_loss_alert_hook(alert_handle_on_link_loss);
  }
}

void link_loss_pipes_updated_evt_rcvd(uint8_t pipe_num, uint8_t *buffer)
{
  switch (pipe_num)
  {
    case PIPE_LINK_LOSS_ALERT_ALERT_LEVEL_RX_ACK_AUTO :
      alert_handle_on_link_loss = (alert_level_t)buffer[0];
      break;
  }
}
