/*Copyright (c) 2014, Nordic Semiconductor ASA
 *
 *Permission is hereby granted, free of charge, to any person obtaining a copy
 *of this software and associated documentation files (the "Software"), to deal
 *in the Software without restriction, including without limitation the rights
 *to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *copies of the Software, and to permit persons to whom the Software is
 *furnished to do so, subject to the following conditions:
 *
 *The above copyright notice and this permission notice shall be included in all
 *copies or substantial portions of the Software.
 *
 *THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *SOFTWARE.
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
