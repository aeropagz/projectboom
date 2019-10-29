//Transmitter program

#include <SPI.h>
#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"

Nrf24l Mirf = Nrf24l(10, 9);

char standby [16] = "standby"; 
char go [16] = "GO";
char ans [16] = "";

int msgSend = 0;

int inPin = 2;

void setup()
{
    Serial.begin(9600);
    Mirf.spi = &MirfHardwareSpi;
    Mirf.init();
    Mirf.setRADDR((byte *)"ABCDE");         //Set your own address (sender address) using 5 characters
    
    
    
    
    
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
      Serial.println("standby");
    }
    else if (msgSend == 2) {
      Serial.println("GO");
    }

    //delay(500);
    ////////////////////////////////////////////////////////////////////////////////////////
    //                                    wait for answer                                 //
    ////////////////////////////////////////////////////////////////////////////////////////

    if (Mirf.dataReady()) {
          Mirf.getData((byte*)&ans);

          Serial.print("Answer is: ");
          Serial.print(ans);
          Serial.println();
    } 

    delay(1000);
    
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
