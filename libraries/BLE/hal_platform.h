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

#ifndef PLATFORM_H__
#define PLATFORM_H__

/** @file
* @brief 
*/
#include "Arduino.h"

#ifdef PROGMEM
#undef PROGMEM
#define PROGMEM __attribute__(( section(".progmem.data") ))
#endif

//#define hal_pltf_clear_spi_master_config() do { SPCR = 0; } while(0)

//SPI2X=1 SPS0=1 SPR0=1 -> 250KHz
//DORD=1 LSBit first
//SPE=1  Enable the SPI
//MSTR=1 Enable master mode
//CPOL=0 See Section 7 in the nRF8001 PS (Clock Polarity)
//CPHA=0 See Section 7 in the nRF8001 PS (Clock Phase)
/*
Atmega328
Table 18-5. Relationship Between SCK and the Oscillator Frequency
SPI2X   SPR1 SPR0 SCK Frequency
0 0 0 fosc/4
0 0 1 fosc/16
0 1 0 fosc/64
0 1 1 fosc/128
1 0 0 fosc/2
1 0 1 fosc/8
1 1 0 fosc/32
1 1 1 fosc/64
*/
/*
#define hal_pltf_spi_master_config() do { \
  pinMode(SCK, OUTPUT);\
  pinMode(MOSI, OUTPUT);\
  pinMode(SS, OUTPUT);\
  pinMode(MISO, INPUT);\
  digitalWrite(SCK, LOW);\
  digitalWrite(MOSI, LOW);\
  digitalWrite(SS, HIGH);\
  SPCR = 0; \
  SPSR = 0; \
  SPSR = (1<<SPI2X);\
  SPCR = ((1<<SPE)|(1<<MSTR)|(0<<SPR1) | (1<<SPR0) | (1<<DORD) | (0<<CPOL) | (0<<CPHA));}\
while(0)
*/

/*
#define hal_pltf_enable_spi()  do { SPCR |= _BV(SPE); } while(0)
#define hal_pltf_disable_spi() do { SPCR &= ~_BV(SPE); } while(0)
  


#define hal_pltf_configure_spi_for_aci() do{\
  hal_pltf_spi_master_config();\
}while(0)
*/

#endif /* PLATFORM_H__ */
