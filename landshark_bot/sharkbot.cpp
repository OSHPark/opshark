#ifndef SHARKBOT
#define SHARKBOT

//#include <Adafruit_NeoPixel.h>
#include <Servo.h>
#include <Streaming.h>

//Needed for breaking up Controller object
#include "RemoteController.cpp"


class Sharkbot {
  private:

    Servo leftfin;
    Servo rightfin;
    Servo bite;
    Servo tailfin;

    Servo driveleft;
    Servo driveright;

    typedef enum {IDLE, MANUAL, DANCE, TEST } State;
    State state;
    /*
      Utility functions to ensure that the outputs are constrained, sensible, and balanced
      //Basically all the same, save for fiddled values
    */
    void writeleftfin( int val ) {

      //Since we'll have a mechanical advantage, let's simplify this by removing some oddities
      //This is also helpful to mirror the off-side servos.
      val = map(val, -90, 90, 0, 180);

      //and, then ensure that it's properly within any mechanical limitations we may have
      val = constrain(val, 10, 170);

      //Write servos out
      leftfin.write(val);
    }
    void writerightfin(int val) {
      val = map(val, -90, 90, 0, 180);
      val = constrain(val, 10, 170);
      rightfin.write(val);
    }
    void writebite(int val ) {
      val = map(val, -90, 90, 0, 180);
      val = constrain(val, 10, 170);
      bite.write(val);
    }
    void writetailfin(int val ) {
      val = map(val, -90, 90, 0, 180);
      val = constrain(val, 10, 170);
      tailfin.write(val);
    }

    //Control the drive with some easier code
    void writedrive(int left, int right) {
    }

  public:


    //Do random cool things
    void dance() {
    }


    //Stuff to do if no one's providing input
    void idle() {
      state=IDLE;
    }

    void balance() {
    }



    Sharkbot() {
      //attach servos, etc.
    leftfin.attach(13);
    rightfin.attach(12);
    bite.attach(5);
    tailfin.attach(4);

    driveleft.attach(14);
    driveright.attach(16);

      state=IDLE;
    };

    void drive() {
      
    };
    
    
    
    
    

    //Do what's appropriate in the current situation
    void update() {
      
      switch (state) {
        case IDLE:
          idle();
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
          state=IDLE;
      }
    }
};


#endif

