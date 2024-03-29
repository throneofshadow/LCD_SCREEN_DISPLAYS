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
//cSFP(rdata, message);
//rdata.trim();
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
  /************************************
  * Basic Grid Template for LCD Display
  *************************************/

Paint_DrawLine(160, 0, 160, 240, WHITE, DOT_PIXEL_1X1,LINE_STYLE_SOLID);// Horizontal grid line
Paint_DrawLine(0, 120, 320, 120, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID); //Vertical grid line
Paint_DrawRectangle(0, 0, 160, 120, WHITE,  DOT_PIXEL_1X1, DRAW_FILL_FULL); // error example box
Paint_DrawRectangle(160, 120, 320, 240, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL); // error example box
Paint_DrawString_EN(40, 70, "VOLTAGE", &Font16, WHITE, RED); // data label
Paint_DrawString_EN(200, 190, "CURRENT", &Font16, WHITE, RED); // data label
Paint_DrawFloatNum (40, 50 , 987.654321, 1,  &Font24,    RED,   WHITE);
Paint_DrawFloatNum (200, 170 , 9.654321, 2,  &Font24,    RED,   WHITE);
delay(5000);  // delay before moving to mode 1
loop();
}
/*************************
    LCD SCREEN FUNCTIONS
*****************************/


/*****************************
     LCD SCREEN TEMPLATES
******************************/

void template_mode_estop(float dis1, float dis2){
  LCD_Clear(0xffff);
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE); // Fill whole quadrant with white.
  Paint_Clear(WHITE);
  Paint_DrawString_EN(0, 0, "Demo : Emergency Mode", &Font16, WHITE, BLACK);
  Paint_DrawString_EN(110, 60, "E STOP", &Font24, WHITE, RED); // Draw E-STOP char in top quadrant.
  Paint_DrawRectangle(0, 120, 320, 240, RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);  // Draw Red Rectangle on Bottom
  Paint_DrawLine(160, 0, 160, 240, WHITE, DOT_PIXEL_1X1,LINE_STYLE_SOLID); // Seperate into two sides with line
  Paint_DrawString_EN(40, 190, "VOLTAGE", &Font16, RED, WHITE);  // Label for data 1
  Paint_DrawString_EN(205, 190, "CURRENT", &Font16, RED, WHITE); // label for data 2
  Paint_DrawFloatNum (40, 160 , 987.654321, 1,  &Font24,    WHITE,   RED); // data 1
  Paint_DrawFloatNum (200, 160 , 11.334321, 1,  &Font24,    WHITE,   RED); // data 2
  delay(5000); // 1s time for screen to refresh.
}

void template_mode_main(int switch_value, float Voltage){
  LCD_Clear(0xffff);
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
  Paint_Clear(RED);

  Paint_DrawLine(160, 0, 160, 240, WHITE, DOT_PIXEL_1X1,LINE_STYLE_SOLID);// Horizontal grid line
  Paint_DrawLine(0, 120, 320, 120, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID); //Vertical grid line
  Paint_DrawString_EN(0, 0, "Main Mode", &Font16, RED, BLACK);
  //Paint_DrawStringEN();
  //Paint_DrawRectangle(0, 0, 160, 120, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL); // error example box top right
  //Paint_DrawRectangle(160, 120, 320, 240, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL); // error example box bottom left
  Paint_DrawRectangle(160, 120, 320, 240, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawRectangle(0, 120, 160, 240, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  //Paint_DrawCircle(180,100, 25, GREEN,  DOT_PIXEL_2X2,   DRAW_FILL_FULL);
  //Paint_DrawCircle(180,125, 25, BLUE,  DOT_PIXEL_2X2,   DRAW_FILL_FULL);
  delay(5000);
}

void template_mode_1(int switch_value, float Voltage)
{
  LCD_Clear(0xffff);
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
  Paint_Clear(RED);
  Paint_DrawString_EN(0, 0, "Demo: Mode 1", &Font16, RED, BLACK);
  Paint_DrawLine(160, 0, 160, 240, WHITE, DOT_PIXEL_1X1,LINE_STYLE_SOLID);// Horizontal grid line
  Paint_DrawLine(0, 120, 320, 120, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID); //Vertical grid line
  //Paint_DrawString_EN(80, 60, "386.4 V", &Font24, GREEN, RED);
  delay(5000);
}

void template_mode_2(int switch_value, float Voltage)
{
  LCD_Clear(0xffff);
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
  Paint_Clear(RED);
  Paint_DrawString_EN(0, 0, "Demo: Mode 2", &Font16, RED, BLACK);
  Paint_DrawLine(160, 0, 160, 240, WHITE, DOT_PIXEL_1X1,LINE_STYLE_SOLID);// Horizontal grid line
  Paint_DrawLine(0, 120, 320, 120, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID); //Vertical grid line
  delay(5000);
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
int switch_value = 1;  //READ SENSOR
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
    template_mode_estop(mode_pin_v, lcu_data.Voltage);
    Serial.println("Mode 0");
    delay(1000);
    break;
  case 1:
  if (memory_mode == mode_pin){break;}
  else{
    template_mode_1(mode_pin_v, lcu_data.Voltage);
    Serial.println("Mode 1");
    delay(1000);
    break;}
  case 2:
    template_mode_2(mode_pin_v, lcu_data.Voltage);
    Serial.println("Mode 2");
    delay(1000);
    break;
  default:
    template_mode_main(mode_pin_v, lcu_data.Voltage);
    Serial.println("In the wrong land..");
    delay(1000);
    break;
}


}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
