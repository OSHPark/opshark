
#include <Servo.h>
#include <Adafruit_NeoPixel.h>


Servo bite;
Servo tail;
Servo lfin;
Servo rfin;
Servo ldrive;
Servo rdrive;

#define PIN            2
#define NUMPIXELS      16
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


int pos = 0;    // variable to store the servo position

void setup()
{
  bite.attach(5);  // attaches the servo on pin 9 to the servo object
  tail.attach(4);  // attaches the servo on pin 9 to the servo object
  lfin.attach(13);  // attaches the servo on pin 9 to the servo object
  rfin.attach(12);  // attaches the servo on pin 9 to the servo object
  ldrive.attach(14);  // attaches the servo on pin 9 to the servo object
  rdrive.attach(16);  // attaches the servo on pin 9 to the servo object


  pixels.begin(); // This initializes the NeoPixel library.

}

void loop()
{

  Serial.print("I did a thing!  ");
  Serial.println(millis());


  for (pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees
  { // in steps of 1 degree
    bite.write(pos);              // tell servo to go to position in variable 'pos'
    tail.write(pos);              // tell servo to go to position in variable 'pos'
    lfin.write(pos);              // tell servo to go to position in variable 'pos'
    rfin.write(pos);              // tell servo to go to position in variable 'pos'
    ldrive.write(pos);              // tell servo to go to position in variable 'pos'
    rdrive.write(pos);              // tell servo to go to position in variable 'pos'

    pixels.setPixelColor(0, pixels.Color(pos/4, 0, 45-pos/4)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(25);                       // waits 15ms for the servo to reach the position



  }
  for (pos = 180; pos >= 0; pos -= 1) // goes from 180 degrees to 0 degrees
  {
    bite.write(pos);              // tell servo to go to position in variable 'pos'
    tail.write(pos);              // tell servo to go to position in variable 'pos'
    lfin.write(pos);              // tell servo to go to position in variable 'pos'
    rfin.write(pos);              // tell servo to go to position in variable 'pos'
    ldrive.write(pos);              // tell servo to go to position in variable 'pos'
    rdrive.write(pos);              // tell servo to go to position in variable 'pos'
    
    pixels.setPixelColor(0, pixels.Color(pos/4, 0, 45-pos/4)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    
    delay(25);                       // waits 15ms for the servo to reach the position
  }

}

