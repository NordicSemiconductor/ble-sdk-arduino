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

#include <Arduino.h>

extern uint8_t timer1_f;

/*** FUNC

Name:           Timer1start

Function:       Start timer 1 to interrupt periodically. Call this from 
                the Arduino setup() function.

Description:    The pre-scaler and the timer count divide the timer-counter
                clock frequency to give a timer overflow interrupt rate:

                Interrupt rate =  16MHz / (prescaler * (255 - TCNT2))

        TCCR2B[b2:0]   Prescaler    Freq [KHz], Period [usec] after prescale
          0x0            (TC stopped)     0         0
          0x1                1        16000.        0.0625
          0x2                8         2000.        0.500
          0x3               32          500.        2.000
          0x4               64          250.        4.000
          0x5              128          125.        8.000
          0x6              256           62.5      16.000
          0x7             1024           15.625    64.000


Parameters: void

Returns:    void

FUNC ***/

void Timer1start(void) 
{

    // Setup Timer1 overflow to fire every 4000ms 
    //   period [sec] = (1 / f_clock [sec]) * prescale * (count)
    //                  (1/16000000)  * 1024 * (count) = 4000 ms


    TCCR1B  = 0x00;        // Disable Timer1 while we set it up

    TCNT1H  = 11;          // Approx 4000ms when prescaler is set to 1024
    TCNT1L  = 0; 
    TIFR1   = 0x00;        // Timer1 INT Flag Reg: Clear Timer Overflow Flag
    TIMSK1  = 0x01;        // Timer1 INT Reg: Timer1 Overflow Interrupt Enable
    TCCR1A  = 0x00;        // Timer1 Control Reg A: Wave Gen Mode normal
    TCCR1B  = 0x05;        // Timer1 Control Reg B: Timer Prescaler set to 1024
}

void Timer1stop(void)
{
    TCCR1B = 0x00;
    TIMSK1 = 0x00;
}

/*** FUNC

Name:       Timer1 ISR

Function:   Handles the Timer1-overflow interrupt

FUNC ***/

ISR(TIMER1_OVF_vect) 
{    
    if (0 == timer1_f)
    {
      timer1_f = 1;
    }

    TCNT1H = 11;    // Approx 4000 ms - Reload
    TCNT1L = 0;
    TIFR1  = 0x00;    // timer1 int flag reg: clear timer overflow flag
};
