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
// @ throneofshadow
#include "DEV_Config.h"

void GPIO_Init()
{
  pinMode(DEV_CS_PIN, OUTPUT);
  pinMode(DEV_RST_PIN, OUTPUT);
  pinMode(DEV_DC_PIN, OUTPUT);
  pinMode(DEV_BL_PIN, OUTPUT);
  analogWrite(DEV_BL_PIN,140);
 }
 void Config_Init()
 {

  GPIO_Init();
  
  //Serial
  Serial.begin(115200);
  
  //spi
  SPI.setDataMode(SPI_MODE3);
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.begin();
  }
