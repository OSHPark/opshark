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
  {1000, LINE, {100, 100}},
  {2000, LINE, {80, 80}},
  {5000, RESET, {80, 80}},
  {3000, RESET, {85, 85}},
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
  {4000, RESET, {75}},
};

void idleTailFunction(AnimationStep shark) {
  tailfin.write(shark.param[0]);
}
Animation idleTail(idleTailAnimation, idleTailFunction);

//This function is oddly named due to existing things. Ugly, but works
AnimationStep biteAnimationSequence[10] = {
  {0, PAUSE, {120}},  //open mouth
  {200, LINE, {120}},  //will be restarted and looped here
  {300, LINE, {90}},  //End function by closing mouth
};

void biteFunction(AnimationStep shark) {
  bite.write(shark.param[0]);
}
Animation biteAnimation(biteAnimationSequence, biteFunction);


AnimationStep danceSequence[10] = {
  {0, PAUSE, {0, 90, 45}}, //left fin down, right fin up, tail to left ,
  {500, PAUSE, {10, 80, 35}}, //left fin down, right fin up, tail to left ,
  {700, PAUSE, {0, 90, 45}}, //left fin down, right fin up, tail to left ,
  {1000, LINE, {90, 0, 135}}, //left fin down, right fin up, tail to left ,
  {1500, PAUSE, {80, 10, 125}}, //left fin down, right fin up, tail to left ,
  {1700, PAUSE, {90, 0, 135}}, //left fin down, right fin up, tail to left ,
  {2500, PAUSE, {45}},

};

void danceFunction(AnimationStep shark) {
  leftfin.write(shark.param[0]);
  rightfin.write(shark.param[1]);
  tailfin.write(shark.param[2]);

  //update pixels with other stuff
}
Animation danceAnimation(danceSequence, danceFunction);



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
        Serial.println("Starting Idle animations");
        idleTail.reset();
        idleTail.start();
      }

      driveright.write(90);
            yield();

      driveleft.write(90);
    }

    void notidle() {
      idleFin.stop();
      idleFin.stop();
      leftfin.write(90);
      yield();
      rightfin.write(90);
      yield();
      tailfin.write(90);

    }

    void balance() {
    }

    Sharkbot(int address) {
      //Step 1: Write out some safe limits so our servos don't destroy anything
      leftfin.mirror();
      leftfin.restrictMapped(80, 110);

      rightfin.restrictMapped(80, 110);

      bite.restrict(70, 110); //currently not allowed to move

      tailfin.restrict(60, 120);

      driveleft.mirror();
      driveleft.restrictMapped(80, 105);
      //driveleft.map(0, 180, -90, 90);

      driveright.restrictMapped(80, 105);
      //driveright.map(0, 180, -90, 90);

      //add some shark specific tuning parameters
      if (address = 1) {
        tailfin.offset(5);

        driveright.offset(0);

      }
      else if (address == 2) {

      }
      else if (address == 3) {

      }


      //Now, power up the servos
      leftfin.attach(13);
      rightfin.attach(12);

      //Don't use these
      // // bite.attach(5);
      // // tailfin.attach(4);
      //For some reason they're backwards from the schematic... Use these values?
      bite.attach(4);
      tailfin.attach(5);
      
      //also backward from schematic!?
      //driveleft.attach(14);
      //driveright.attach(16);
      driveleft.attach(16);
      driveright.attach(14);

      //These things have horrible startup glitches, so try to minimize it by writing right away
      leftfin.write(90);
      rightfin.write(90);
      bite.write(90);
      tailfin.write(90);

      state = IDLE;
    };


    void manual(ControllerState control) {
      //disable any ongoing idle animations
      notidle();

      if (control.up) {
        driveleft.write(90+20);
        driveright.write(90+20);
        Serial.println("++");
      }
      else if (control.left) {
        driveleft.write(90+5);
        driveright.write(90+20);
        Serial.println("+-");
      }
      else if (control.right) {
        driveleft.write(90+20);
        driveright.write(90+5);
       Serial.println("-+");
      }

      else if (control.down) {
        driveleft.write(90-10);
        driveright.write(90-10);
        
        
      }
      else { 
          driveleft.write(90+0);
          driveright.write(90+0);
      }



      //BITE
      if ( control.bite ) {
        //This one will hold the mouth open until you let go
        biteAnimation.reset();
        biteAnimation.start();
      }
      //DANCE PARTY
      if ( control.dance) {
        //This will only do a dance if it's not happening
        if (! danceAnimation.isEnabled() ) {
          Serial.println("COMMENCING DANCE PARTY");
          danceAnimation.start();
          danceAnimation.reset();
        }
      }


      // This delay and button update speed on the controller will determine how fast the
      // accelleration profiles change
    }



    //Do what's appropriate in the current situation
    void update() {
      //update all animations, although most of them are currently idle.
      //those animations will simply do nothing.
      idleFin.update();
      idleTail.update();
      biteAnimation.update();
      danceAnimation.update();
      
      Serial<<"L " <<  driveleft.read()  <<endl;
      Serial<<"R " <<  driveright.read()  <<endl;
      
      driveleft.offset(-20);
      delay(2);
    }
};



















#endif

