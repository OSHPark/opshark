#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <Arduino.h>

/** Bit positions for sending button data over SPI
 *  X X UP DOWN LEFT RIGHT BITE DANCE
 */
#define UP 		5
#define DOWN 	4
#define LEFT 	3
#define RIGHT 	2
#define BITE 	1
#define DANCE 	0

/** Write down the pin positions for our capacitive sense buttons
 */
#define pinUp    15
#define pinLeft  18
#define pinRight 16
#define pinDown  17
#define pinBite  19
#define pinDance 22



class SPIController {
  private:
    /** Class for handling button presses and storing for SPI communcation
     * This is saved as a bitfield, due to SPI interrupts needing to be very fast in accessing data
     */
    byte _state = 0;
    int  _refUp;
    int  _refLeft;
    int  _refRight;
    int  _refDown;
    int  _refBite;
    int  _refDance;

  public:

    /** Initialize all capacitive buttons so the threshhold is just above what the system boots with.
     *
     */

    SPIController() {
      _state = 0;

      _refUp 	= touchRead(pinUp) + 100;
      _refLeft = touchRead(pinLeft) + 100;
      _refRight = touchRead(pinRight) + 100;
      _refDown = touchRead(pinDown) + 100;
      _refBite = touchRead(pinBite) + 100;
      _refDance = touchRead(pinDance) + 100;
    }

    /**
     * Return the raw bitfield, which is usable as an SPI response
     */
    byte read() {
      return _state;
    }

    /*Functions for Marking a button as pressed*/
    void pressUp() {
      bitSet(_state, UP);
    }
    void pressDown() {
      bitSet(_state, DOWN);

    }
    void pressLeft() {
      bitSet(_state, LEFT);

    }
    void pressRight() {
      bitSet(_state, RIGHT);

    }
    void pressBite() {
      bitSet(_state, BITE);

    }
    void pressDance() {
      bitSet(_state, DANCE);

    }

    /*Functions for marking a button as released
     */
    void releaseUp() {
      bitClear(_state, UP);

    }
    void releaseDown() {
      bitClear(_state, DOWN);

    }
    void releaseLeft() {
      bitClear(_state, LEFT);

    }
    void releaseRight() {
      bitClear(_state, RIGHT);

    }
    void releaseBite() {
      bitClear(_state, BITE);

    }
    void releaseDance() {
      bitClear(_state, DANCE);

    }

    //read button states
    byte readUp() {
      return bitRead(_state, UP);
    }
    byte readDown() {
      return bitRead(_state, DOWN);

    }
    byte readLeft() {
      return bitRead(_state, LEFT);

    }
    byte readRight() {
      return bitRead(_state, RIGHT);

    }
    byte readBite() {
      return bitRead(_state, BITE);
    }
    byte readDance() {
      return bitRead(_state, DANCE);
    }

    /** Read all the button capacative values, and update pins appropriately
     */
    void update() {
      if (touchRead(pinUp) > _refUp) {
        pressUp();
      }
      else {
        releaseUp();
      }

      if (touchRead(pinDown) > _refDown) {
        pressDown();
      }
      else {
        releaseDown();
      }

      if (touchRead(pinLeft) > _refLeft) {
        pressLeft();
      }
      else {
        releaseLeft();
      }

      if (touchRead(pinRight) > _refRight) {
        pressRight();
      }
      else {
        releaseRight();
      }

      if (touchRead(pinBite) > _refBite) {
        pressBite();
      }
      else {
        releaseBite();
      }

      if (touchRead(pinDance) > _refDance) {
        pressDance();
      }
      else {
        releaseDance();
      }
    }


};



#endif


