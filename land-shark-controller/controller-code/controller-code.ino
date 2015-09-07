
#include "controller.h"
SPIController self=SPIController();


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
  
}

void loop() {
  
/**
* Examine all the buttons, and determine if they're currently being pressed. 
*/
  self.update();
  print_values();
  
  //Hold off a small amount between buttons, to avoid crazy hysterics. 
  delay(200);
}






