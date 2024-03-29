/*****************************************************************************
* | File        :   LCD_Display.ino
* | Author      :   Brett Nelson, @throneofshadow
* | Function    :   Demo script to run basic functionality of LCD screen using an Arduino Uno/Nano
* | Info        :
*                Used to provide master control, drawing, and mode switching.
*----------------
* | This version:   V0.1
* | Date        :   2024-7-March
* | Info        : Written for YouSolar Inc research and engineering team for device-level displays used in Gen 3 PowerBlock.
* 
******************************************************************************/
// Modified by Brett Nelson, Yousolar
// @throneofshadow
#ifndef _DEV_CONFIG_H_
#define _DEV_CONFIG_H_

#include <stdint.h>
#include <stdio.h>
#include <SPI.h>
#include <avr/pgmspace.h>



#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

/**
 * GPIO config
**/
#define DEV_CS_PIN  10
#define DEV_DC_PIN  7
#define DEV_RST_PIN 8
#define DEV_BL_PIN  9
#define DEV_MODE_PIN 6

/**
 * GPIO read and write
**/
#define DEV_Digital_Write(_pin, _value) digitalWrite(_pin, _value == 0? LOW:HIGH)
#define DEV_Digital_Read(_pin) digitalRead(_pin)


/**
 * SPI
**/
#define DEV_SPI_WRITE(_dat)   SPI.transfer(_dat)

/**
 * delay x ms
**/
#define DEV_Delay_ms(__xms)    delay(__xms)

/**
 * PWM_BL
**/
 #define  DEV_Set_PWM(_Value)  analogWrite(DEV_BL_PIN, _Value)

/*-----------------------------------------------------------------------------*/
 void Config_Init();
#endif
