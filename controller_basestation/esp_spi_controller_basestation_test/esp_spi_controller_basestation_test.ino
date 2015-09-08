
#include <SPI.h>
#define SS_CTRL1 16

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.write("Starting up...");

  //Should operate in mode 0 by default, which is the One True Sane Mode.
  digitalWrite (SS_CTRL1, HIGH);
  pinMode (SS_CTRL1, OUTPUT);
  SPI.begin(); 

  //pinMode(pMISO,OUTPUT);
  //pinMode(pSCK,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);  

  //begin the transaction by writing the SS pin low  
  SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
    digitalWrite(SS_CTRL1,LOW);
    // Works for triggering clock on Teensy, but doesn't capture or send data
    byte a=SPI.transfer('y');
    byte b=SPI.transfer('o');
    
    /*
    byte a=shiftIn(pMISO,pSCK,MSBFIRST);
    delayMicroseconds(5);
    byte b=shiftIn(pMISO,pSCK,MSBFIRST);
    //*/
    
    //End by returning SS high
    digitalWrite(SS_CTRL1,HIGH);
  SPI.endTransaction();
  
  //poll controllers once per second
  Serial.println("=Transfer=");
  Serial.println(a);
  Serial.println(b);
  

  digitalWrite(13,!digitalRead(13));
}
