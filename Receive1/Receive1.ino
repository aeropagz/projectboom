//Receiver program
#include <SPI.h>
#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"

Nrf24l Mirf = Nrf24l(10, 9);

char standby [16] = "standby"; 
char go [16] = "GO";
char error [16] = "error";
char msg [16] = "";

String by = "standby";
String stand = "standby"; 


void setup()
{
  Serial.begin(9600);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"FGHIJ");                                 //Set your own address (receiver address) using 5 characters
  Mirf.payload = sizeof(standby);
  Mirf.channel = 10;                                              //Set the used channel
  Mirf.config();
  Serial.println("Listening...");                                 //Start listening to received data
}

void loop()
{
    
    Mirf.ceLow();
    Mirf.configRegister(RF_CH, 10);                                //switch channel 10
    Mirf.ceHi();   
    
    if (Mirf.dataReady()) {                                        //When the program is received, the received data is output from the serial port
        
        Mirf.getData((byte *) &msg);
        
        Serial.print("Receive1 got data is: ");
        Serial.print(msg);       
        Serial.println();
        
    }
     delay(800);
    ////////////////////////////////////////////////////////////////////////////////////////
    //                                    send answer                                     //
    ////////////////////////////////////////////////////////////////////////////////////////

   Mirf.setTADDR ((byte*) "ABCDE");

   if (stand == by){
       Mirf.send((byte*)&standby);
       while (Mirf.isSending()) delay(1);
       Serial.println ("Send success: ");
       Serial.println("standby send");
   }
   else{
       Mirf.send((byte*)&error);
          while (Mirf.isSending()) delay(1);
          Serial.println ("Send success: ");
          Serial.println("error send");
   }


   
   delay(500);  
   

   
      
}
