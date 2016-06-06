//#include <SPI.h>
//#include <Ethernet.h>
#include <ESP8266WiFi.h>
#include "MgsModbus.h"

MgsModbus Mb;
int inByte = 0; // incoming serial byte



void setup()
{

  // serial setup
  Serial.begin(9600);
  Serial.println("Serial interface started");

  // initialize the ethernet device
  WiFi.begin("ssid","passphrase");   // start etehrnet interface
  Serial.println("WiFi interface started"); 

  // print your local IP address:
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(WiFi.localIP()[thisByte], DEC);
    Serial.print("."); 
  }
  Serial.println();


  // Fill MbData
//  Mb.SetBit(0,false);
  Mb.MbData[0] = 1;
  Mb.MbData[1] = 2;
  Mb.MbData[2] = 3;
  Mb.MbData[3] = 4;
  Mb.MbData[4] = 5;
  Mb.MbData[5] = 6;
  Mb.MbData[6] = 0;
  Mb.MbData[7] = 0;
  Mb.MbData[8] = 0;
  Mb.MbData[9] = 0;
  Mb.MbData[10] = 0;
  Mb.MbData[11] = 0;
  
  // print MbData
  for (int i=0;i<12;i++) {
    Serial.print("address: "); Serial.print(i); Serial.print("Data: "); Serial.println(Mb.MbData[i]);
  }
  // print menu
  Serial.println("0 - print the first 12 words of the MbData space");
  Serial.println("1 - FC 1 - read the first 5 coils from the slave and store them in the lower byte of MbData[1]");
  Serial.println("2 - FC 2 - read the first 5 discrete inputs from the slave and store them in the higer of the MbData[1]");
  Serial.println("3 - FC 3 - read the first 5 registers from the slave and store them in MbData[3..7");
  Serial.println("4 - FC 4 - read the first 5 input registers from the slave and store them in MbData[8..12]");
  Serial.println("5 - FC 5 - write coil 0 of the slave with the bit valeu of MbData[0.0]");
  Serial.println("6 - FC 6 - write register 0 of the slave with MbData[2]");
  Serial.println("7 - FC 15 - write 5 coils of the slave starting with coil 0 with GetBit(16..20");
  Serial.println("8 - Fc 16 - write 5 registers of the slave starting on register 0 with MbData[0..4]");

  Serial.println(Mb.remSlaveIP);
}

void loop()
{
  if (Serial.available() > 0) {
    // get incoming byte:
    inByte = Serial.read();
    if (inByte == '0') {                                          // print MbData
      for (int i=0;i<12;i++) {
        Serial.print("address: "); Serial.print(i); Serial.print("Data: "); Serial.println(Mb.MbData[i]);
      }
    }  
    if (inByte == '1') {Mb.Req(MB_FC_READ_COILS,               6,6,6);} // 1 // ref, count, pos
    if (inByte == '2') {Mb.Req(MB_FC_READ_DISCRETE_INPUT,      6,6,6);} // 2
    if (inByte == '3') {Mb.Req(MB_FC_READ_REGISTERS,           6,6,6);} // 3
    if (inByte == '4') {Mb.Req(MB_FC_READ_INPUT_REGISTER,      6,6,6);} // 4
    if (inByte == '5') {Mb.Req(MB_FC_WRITE_COIL,               0,0,0);} // 5 // count can be x
    if (inByte == '6') {Mb.Req(MB_FC_WRITE_REGISTER,           7,0,0);} // 6 // count can be x
    if (inByte == '7') {Mb.Req(MB_FC_WRITE_MULTIPLE_COILS,     0,6,0);} // 15
    if (inByte == '8') {Mb.Req(MB_FC_WRITE_MULTIPLE_REGISTERS, 0,6,0);} // 16
  }

  Mb.MbmRun();
//  Mb.MbsRun();
}

