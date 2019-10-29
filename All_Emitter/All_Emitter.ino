//Transmitter program

#include <SPI.h>
#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"

Nrf24l Mirf = Nrf24l(10, 9);
int value1,value2;

byte go [4] = {0x00, 0x00, 0x00, 0xFF}; 
byte standby [4] = {0x00, 0x00, 0xFF, 0xFF};
byte ans [4] = {0};

int msgSend = 0;

int inPin = 2;

void setup()
{
    Serial.begin(9600);
    Mirf.spi = &MirfHardwareSpi;
    Mirf.init();
    //Set your own address (sender address) using 5 characters
    Mirf.setRADDR((byte *)"ABCDE");

    // set input pin

    pinMode(inPin, INPUT);

   
}

void loop()
{
    Mirf.payload = sizeof(standby);
    Mirf.channel = 10;              //Set the channel used
    Mirf.config();
    if(Mirf.channel == 10)
    {
    Mirf.setTADDR((byte *)"FGHIJ");           //Set the receiver address

    
    if (digitalRead(inPin)){
      msgSend = 2;
      Mirf.send((byte*) &go);               //Send GO
    }
    else{
      msgSend = 1;
      Mirf.send((byte *)&standby);          //Send Stand by
    }
    
    Serial.print("Wait for sending.....");
    while (Mirf.isSending()) delay(1);        //Until you send successfully, exit the loop
    
    Serial.print("Send success: ");
    if (msgSend == 1){
      Serial.println("msg1");
    }
    else if (msgSend == 2) {
      Serial.println("msg2");
    }

    delay(500);
    ////////////////////////////////////////////////////////////////////////////////////////
    //                                    wait for answer                                 //
    ////////////////////////////////////////////////////////////////////////////////////////

    
    }

    /*
    Mirf.payload = sizeof(value2);
    Mirf.channel = 20;              //Set the channel used
    Mirf.config();
    if(Mirf.channel == 20)
    { 
    Mirf.setTADDR((byte *)"KLMNO");           //Set the receiver address
    value2 = 200;
    Mirf.send((byte *)&value2);                //Send instructions, send random number value
    Serial.print("Wait for sending.....");
    while (Mirf.isSending()) delay(1);        //Until you send successfully, exit the loop
    Serial.print("value2 Send success:");
    Serial.println(value2);
    delay(500);
    }*/
}
