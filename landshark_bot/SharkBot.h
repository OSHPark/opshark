#ifndef SHARKBOT
#define SHARKBOT

//#include <Adafruit_NeoPixel.h>
#include <Servo.h>
#include "ServoPlus.h" //This is a wrapper around Servo that allows native constraints and mirroring
#include <Streaming.h>

#include "Animation.h"
//Needed for breaking up Controller object
#include "RemoteController.h"

ServoPlus leftfin;
ServoPlus rightfin;
ServoPlus bite;
ServoPlus tailfin;

ServoPlus driveleft;
ServoPlus driveright;

AnimationStep idleFinsAnimation[10] = {
  {000, LINE, {80, 80}},
  {1000, LINE, {90, 90}},
  {2000, LINE, {80, 80}},

  {2001, RESET, {85, 85}},
};
void idleFinsFunction(AnimationStep shark) {
  leftfin.write(shark.param[0]);
  rightfin.write(shark.param[1]);
}
Animation idleFin(idleFinsAnimation, idleFinsFunction);

AnimationStep idleTailAnimation[10] = {
  {0, LINE, {90}},
  {500, LINE, {75}},
  {2000, LINE, {105}},
  {2500, LINE, {90}},
  {2501, RESET, {75}},
};

void idleTailFunction(AnimationStep shark) {
  tailfin.write(shark.param[0]);
}
Animation idleTail(idleTailAnimation, idleTailFunction);



class Sharkbot {
  private:
    typedef enum {IDLE, MANUAL, DANCE, TEST } State;
    State state;
    int _address;

  public:


    //Do random cool things
    void dance() {
    }


    //Stuff to do if no one's providing input
    void disable() {
       leftfin.detach();
      rightfin.detach();
      //bite.attach(5);
      //tailfin.attach(4);
      //For some reason they're backwards from the schematic?
      bite.detach();
      driveleft.detach();
      driveright.detach();
    }
    
    void idle() {
      if (! idleFin.isEnabled()) {
        Serial.println("Starting Idle animations");
        idleFin.reset();
        idleFin.start();
      }
      if (! idleTail.isEnabled()) {
        idleTail.reset();
        idleTail.start();
      }
    }

    void notidle() {
      idleFin.stop();
      idleFin.stop();
    }

    void balance() {
    }

    Sharkbot(int address) {
      //Step 1: Write out some safe limits so our servos don't destroy anything
      leftfin.mirror();
      leftfin.restrictMapped(80, 110);
      
      rightfin.restrictMapped(80, 110);
      
      bite.restrict(90, 90); //currently not allowed to move
      
      tailfin.restrict(60,120);

      driveleft.restrict(85, 95);
      driveright.restrict(85, 95);

      //add some shark specific tuning parameters
      if(address=1){
        tailfin.offset(5);
      }
      else if(address==2){
        
      }
      else if(address==3){
        
      }

      //Now, power up the servos
      leftfin.attach(13);
      delay(200);
      rightfin.attach(12);
            delay(200);

      //Don't use these
      // // bite.attach(5);
      // // tailfin.attach(4);
      //For some reason they're backwards from the schematic... Use these values?
      bite.attach(4);
      delay(200);
      tailfin.attach(5);
      delay(200);

      //temporarily disabled to prevent driving off the table
      //driveleft.attach(14);
      delay(200);

      //driveright.attach(16);
      delay(200);


      //These things have horrible startup glitches, so try to minimize it by writing right away
      leftfin.write(90);
      rightfin.write(90);
      bite.write(90);
      tailfin.write(90);
      //driveleft.write(90);
      //driveright.write(90);


      state = IDLE;
    };

    void drive() {

    };






    //Do what's appropriate in the current situation
    void update() {
      //update all animations, although most of them are currently idle.
      //those animations will simply do nothing.
      idleFin.update();
      idleTail.update();

      /*
      switch (state) {
        case IDLE:
          break;;
        case DANCE:
          dance();
          break;;
        case TEST:
          idle();
          break;;
        case MANUAL:
          break;;
        default:
          Serial << "Not able to execute state " << state << endl;
          state = IDLE;
      }
      */
    }
};



















#endif

