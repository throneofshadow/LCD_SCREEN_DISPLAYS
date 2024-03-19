/*********************************************************
UART Communication Protocol Spoof
Written by: Brett Nelson, @ throneofshadow
Code intended to spoof UART communication from a local control unit to a arduino Nano. Communication
streams include relevant and irrelevant data structures. Data may be parsed on the receiver (Nano) side.
**************************************************************/

// Global structure for data
#include <SoftwareSerial.h>
struct data_table{char Voltage[5], Amps[4], ControlState[1], CurrentSolar[4], CurrentLoad[5], CurrentProduction[5], estop_on[1],
 model[1], lcu_version[4], serial[10];};
int baud_rate = 9600;
const byte rxPin = 2;
const byte txPin = 3;
SoftwareSerial Serial1 (rxPin, txPin);

void setup() {
/********************
Initialize UART serial output from TX/RX
**********************/
//int baud_rate = 9600;
//const byte rxPin = 2;
//const byte txPin = 3;
//SoftwareSerial Serial1 (rxPin, txPin);
//Serial1.begin(baud_rate); // Initialize tx/rx UART transmitter
pinMode(rxPin, INPUT);
pinMode(txPin, OUTPUT);
Serial1.begin(baud_rate); // Initialize tx/rx UART transmitter

}

void loop() {
// Compile data for writing
char write_string[200] ;
struct data_table write_data = { "378.9", "10.1", "0", "02.3", "01342", "01640", "0", "0", "1.57", "10000001"};
int size_table = sizeof(struct data_table);
Serial.write("/s", 2);
delay(20);
Serial1.write(write_data.serial, strlen(write_data.serial)); //Write to TX/RX pins in char
//delay(50);
Serial1.write("/v", 2);
//delay(50);
Serial1.write(write_data.Voltage, 4); //Write to TX/RX pins in char
//delay(50);
Serial1.write("/a", 2);
//delay(50);
Serial1.write(write_data.Amps, 4); //Write to TX/RX pins in char
//delay(50);
Serial1.write("/c", 2);
//delay(50);
Serial1.write(write_data.ControlState, 1); //Write to TX/RX pins in char
//delay(50);
Serial1.write("/cs", 3);
Serial1.write(write_data.CurrentSolar, 4); //Write to TX/RX pins in char
Serial1.write("/cp", 3);
Serial1.write(write_data.CurrentProduction, 5); //Write to TX/RX pins in char
Serial1.write("/cl", 3);
Serial1.write(write_data.CurrentLoad, 5); //Write to TX/RX pins in char
Serial1.write("/es", 3);
Serial1.write(write_data.estop_on, 1); //Write to TX/RX pins in char
Serial1.write("/n", 2);
// Finished writing data, wait for read
delay(150);  // For read
char gotchar = Serial1.read();
Serial.print(gotchar, 2);
}
