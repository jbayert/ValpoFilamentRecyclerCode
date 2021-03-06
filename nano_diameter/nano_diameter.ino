#include "data_process.h"
#include "Wire.h"

#define  DIAL_CLK_PIN    13 //yellow
#define  DIAL_DATA_PIN   12 //blue
#define VERBOSE

short CaliperValueMain;
short test;
byte sendData[2];

void setup()
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  CaliperSetup(DIAL_CLK_PIN,DIAL_DATA_PIN);
  Wire.begin(8);
  Wire.onRequest(requestEvent);
  test = 0;
}//====================================================

void loop()
{
  short temp = CaliperLoop();
 
  if (temp != -1){
    //Serial.print(temp);
    //Serial.println(" um");
    test = temp;
    byte sendbyte = 21;
    sendData[0] = (test >> 8) & 0x00FF;
    sendData[1] = test & 0x00FF;
    //Serial.write(sendbyte);
    Serial.write(0xCC); //Write the serial data
    Serial.write(sendData,2);
    Serial.write(0xCC); //Write the serial data
    delay(100);
  }
  
}//====================================================


void requestEvent(){
  //Serial.println(CaliperValueMain);
  
  Wire.write(sendData, 2);
  unsigned short test = sendData[1];
  test = (test << 8) | sendData[0];
  #ifdef VERBOSE
  //Serial.println(test);
 #endif
}
