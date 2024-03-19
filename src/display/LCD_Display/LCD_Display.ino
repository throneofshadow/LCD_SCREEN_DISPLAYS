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
********************************************************************************/
#include <SPI.h>
#include "LCD_Driver.h"
#include "GUI_Paint.h"
#include "source_image.h"
#include "SafeString.h"



/*********************
  Global Variables
*********************/

//Global variables used in LCU, sensor loops
int mode_pin, memory_mode;
int top_node = 3;
int baud_transmission = 9600;
char receivedMessage;
char receivedChar;
struct LCU_struct { float Voltage, Amperage, Data1, Data2, Data3, Data4;};

/*********************
      Setup 
***********************/


void setup()
{
  // This is the initial loading screen on boot for each device. 
  // As main progresses through the logic loop, each mode template is called
  // Additionally, data is continously read through arduino pins dedicated to the data stream.
  // This data is used to inform each mode template of the appropriate value to display for each parameter.
  // This data is continually refreshed during a cycle. If unavailable, 
  Config_Init();
  Serial.begin(baud_transmission); // Initialize UART serial connection
  LCD_Init();
  LCD_Clear(0xffff);
  int control_loops = 0;

  /********************
  Fetch Initial Data
  ********************/

  while (Serial.available() > 0){
    char receivedChar = Serial.read();
    if (receivedChar == '\n') {
       if (control_loops > 4)
       {break;
       }
      else {
      receivedMessage = "";  // Reset the received message
      control_loops += 1;}
        }
    else { receivedMessage += receivedChar; }
  }
Serial.println(receivedMessage);
delay(1000);
  // Decipher string message for unit information (unit type, serial, LCU info..)
char *message = receivedMessage;
cSFP(rdata, message);
rdata.trim();
//if (rdata.startsWith("t")){
  //cSF(sfToken, 10);
  //cSF(sfSub, 3);
  //char delimeters[] = "/v";
  //rdata.nextToken(sfToken, delimeters);  // step over +QGPSLOC:
  //sfToken.toFloat(float serial);
  //rdata.nextToken(sfToken, delimeters);
  //sfToken.toFloat(float Voltage);
  //rdata.nextToken(sfToken, delimeters);
  //sfToken.toFloat(float Amps);
  //rdata.nextToken(sfToken,delimeters);
  //sfToken.toFloat(float ControlState);
  //rdata.nextToken(sfToken, delimeters);
  //sfToken.toFloat(float CurrentSolar);
  //rdata.nextToken(sfToken, delimeters);
  //sfToken.toFloat(float CurrentProduction);
  //rdata.nextToken(sfToken, delimeters);
  //sfToken.toFloat(float CurrentLoad);
  //rdata.nextToken(sfToken, delimeters);
  //sfToken.toFloat(float estop_on);
  // End DB
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
  Paint_Clear(RED);
  Paint_DrawString_EN(100, 100, "YouSolar", &Font24, RED, BLACK);
  //Paint_DrawString_EN(30, 34, "ABC", &Font24, BLUE, CYAN);
  //Paint_DrawRectangle(125, 10, 225, 58, BLACK,  DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
  //Paint_DrawLine(125, 10, 225, 58, MAGENTA,   DOT_PIXEL_2X2,LINE_STYLE_SOLID);
  //Paint_DrawCircle(180,100, 25, BLACK,  DOT_PIXEL_2X2,   DRAW_FILL_EMPTY);
  //Paint_DrawImage(gImage_70X70, 20, 80, 70, 70); 
  //Paint_DrawFloatNum (5, 150 ,987.654321,4,  &Font20,    WHITE,   LIGHTGREEN);
delay(5000);  // delay before moving to mode 1
loop();
}


/*****************************
     LCD SCREEN TEMPLATES
******************************/

void template_mode_main(int switch_value, float Voltage){
  LCD_Clear(0xffff);
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
  Paint_Clear(RED);
  Paint_DrawString_EN(120, 120, char(switch_value), &Font24, RED, BLACK);
  Paint_DrawRectangle(5, 5, 315, 235, BLACK,  DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
  Paint_DrawCircle(180,100, 25, GREEN,  DOT_PIXEL_2X2,   DRAW_FILL_EMPTY);
  Paint_DrawCircle(180,125, 25, BLUE,  DOT_PIXEL_2X2,   DRAW_FILL_EMPTY);

}

void template_mode_1(int switch_value, float Voltage)
{
  LCD_Clear(0xffff);
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
  Paint_Clear(GREEN);
  Paint_DrawString_EN(80, 60, "386.4 V", &Font24, GREEN, RED);
  Paint_DrawRectangle(15, 15, 205, 205, BLACK,  DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
  Paint_DrawCircle(180,100, 25, GREEN,  DOT_PIXEL_2X2,   DRAW_FILL_EMPTY);
  Paint_DrawCircle(180,125, 25, BLUE,  DOT_PIXEL_2X2,   DRAW_FILL_EMPTY);
}

void template_mode_2(int switch_value, float Voltage)
{
  LCD_Clear(0xffff);
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
  Paint_Clear(BLACK);
  Paint_DrawString_EN(140, 120, char(switch_value), &Font24, GREEN, CYAN);
  Paint_DrawRectangle(125, 10, 225, 58, BLACK,  DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
  Paint_DrawCircle(180,100, 25, GREEN,  DOT_PIXEL_2X2,   DRAW_FILL_EMPTY);
  Paint_DrawCircle(180,125, 25, BLUE,  DOT_PIXEL_2X2,   DRAW_FILL_EMPTY);
}


/**************************
    Main Control Loop
***************************/

void loop()

{
// This is the main loop function, meant to loop continously while obtaining reference data from
// module LCUs and pin input for mode switching.

//UART Communication from LCU

//READ UART COMMUNICATION FROM LCU SERIAL
int i = 0;
int dlen = 0;
int BUFFER_SIZE = 200 ; 
char buf[200];
while (Serial.available() > 0) {
  if (i > 2){ break;} else{
  dlen = Serial.readBytes( buf, BUFFER_SIZE);
  }
}
// Format message string into database
// Read string, split by named delimeters

Serial.println(dlen);
Serial.println(buf);
//Serial.write("tx", 2);
// Add database values to structure
struct LCU_struct lcu_data = { 
  398.8, 10.1, 100.0, 100.0, 100.0, 100.0
};
// A global variable, mode_value, is used to hold current screen mode in reference.
int switch_value = digitalRead(DEV_MODE_PIN);  //READ SENSOR
int mode_pin_v = mode_pin;  // point at main mode_pin
// if pins match previous value, no change in screen
//Serial.print("My step 1");
//Serial.print(char(mode_pin));
switch_value = switch_value + mode_pin;

// else, change mode_pin to new value, refresh screen
mode_pin_v = switch_value;
if (mode_pin_v > top_node)
{ mode_pin_v = 0;
}
// Swap address contents for next loop
memory_mode = mode_pin;
mode_pin = mode_pin_v;
switch (mode_pin_v){
  case 0: // No change in mode switching
    template_mode_main(mode_pin_v, lcu_data.Voltage);
    Serial.println("Mode 0");
    //delay(1000);
    break;
  case 1:
  if (memory_mode == mode_pin){break;}
  else{
    template_mode_1(mode_pin_v, lcu_data.Voltage);
    Serial.println("Mode 1");
    //delay(1000);
    break;}
  case 2:
    template_mode_2(mode_pin_v, lcu_data.Voltage);
    Serial.println("Mode 2");
    //delay(1000);
    break;
  default:
    template_mode_main(mode_pin_v, lcu_data.Voltage);
    Serial.println("In the wrong land..");
    //delay(10000);
    break;
}


}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
