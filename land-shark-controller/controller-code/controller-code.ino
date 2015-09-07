/** 
Controller-code: This code is uploaded to the Teensy 3.1 which reads capacative buttons, and then allows 
a base-station or other device to read them via SPI.

This code uses the T3SPI class which enables the Teensy 3 to act as an SPI Slave. This code can be found here:
https://github.com/soerup/Teensy-3.0-SPI-Master---Slave
*/


#include "controller.h"
SPIController self=SPIController();

#include <t3spi.h>

//Initialize T3SPI class as SPI_SLAVE
T3SPI SPI_SLAVE;

//The number of integers per data packet
//MUST be the same as defined on the MASTER device
#define dataLength  1

//Initialize the arrays for incoming data
volatile uint16_t data[dataLength] = {};

//Initialize the arrays for outgoing data
//Not actually utilized currently
volatile uint16_t returnData[dataLength] = {};


void print_values() {
  Serial.print("Up: ");
  Serial.println(self.readUp());
  Serial.print("Down: ");
  Serial.println(self.readDown());
  Serial.print("Left: ");
  Serial.println(self.readLeft());
  Serial.print("Right: ");
  Serial.println(self.readRight());
  Serial.print("Bite: ");
  Serial.println(self.readBite());
  Serial.print("Dance: ");
  Serial.println(self.readDance());
  Serial.println("  ");
}

void setup() {
   Serial.begin(115200);
  
  
  //Begin SPI in SLAVE (SCK pin, MOSI pin, MISO pin, CS pin)
  SPI_SLAVE.begin_SLAVE(SCK, MOSI, MISO, CS0);
  
  //Set the CTAR0_SLAVE0 (Frame Size, SPI Mode)
  SPI_SLAVE.setCTAR_SLAVE(16, SPI_MODE0);
  
  //Enable the SPI0 Interrupt
  NVIC_ENABLE_IRQ(IRQ_SPI0);
  
  //Poputlate the array of outgoing data
  for (int i=0; i<dataLength; i++){
    returnData[i]=i;}
  returnData[0]='h'<<8|'i';
  returnData[1]='n'<<8|'o';

}

void loop() {
  
  /**
  * Examine all the buttons, and determine if they're currently being pressed. 
  */
  self.update();
  print_values();
  
  /**
  * The incoming data will be one byte of nothing, and 1 byte of address information. 
  * Outgoing data will be the address (previously sent), and the current controller data. 
  */
  returnData[0]= (data[0]<<8) | self.read();
  
  
  //Hold off a small amount between buttons, to avoid crazy hysterics on buttons. 
  delay(100);
}


//Interrupt Service Routine to handle incoming data
//This function is responsible for replying to any SPI requests with the data we've stashed away in memory. 
void spi0_isr(void){
  
  SPI_SLAVE.rxtx16(data, returnData, dataLength);
}
