/* Copyright (c) 2011 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRENTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 * $LastChangedRevision$
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
