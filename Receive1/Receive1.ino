//Receiver program
#include <SPI.h>
#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"

Nrf24l Mirf = Nrf24l(10, 9);

int value;
byte standby [4] =  {0x00, 0x00, 0x00, 0x00};
void setup()
{
  Serial.begin(9600);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"FGHIJ"); //Set your own address (receiver address) using 5 characters
  Mirf.payload = sizeof(standby);
  Mirf.channel = 10;             //Set the used channel
  Mirf.config();
  Serial.println("Listening...");  //Start listening to received data
}

void loop()
{

    Mirf.ceLow();
    Mirf.configRegister(RF_CH, 10);  //switch channel 10
    Mirf.ceHi();
    if (Mirf.dataReady()) { //When the program is received, the received data is output from the serial port
        Mirf.getData((byte *) &msg);
        Serial.print("Receive1 got data is: ");
        for (int i = 0; i < sizeof(msg); i++){
        Serial.print(msg[i], HEX);
        Serial.print(" ");
        }
        Serial.println();
        
    }
     delay(800);
      
}
