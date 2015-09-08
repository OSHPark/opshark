#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <elapsedMillis.h>
#include <SPI.h>

/** Bit positions for sending button data over SPI
 *  X X UP DOWN LEFT RIGHT BITE DANCE
 */
#define UP 	5
#define DOWN 	4
#define LEFT 	3
#define RIGHT 	2
#define BITE 	1
#define DANCE 	0

struct ControllerState {
  byte up;
  byte down;
  byte left;
  byte right;
  byte bite;
  byte dance;
};

class SPIController {
  private:
    byte _address;
    byte _ss_pin;
    elapsedMillis  _lastUpdate;
    ControllerState  _state;
    byte  _statebyte,_modified;
    
    
public:
    SPIController(byte address, int ss_pin) {
      _address = address;
      _ss_pin = ss_pin;

      digitalWrite (_ss_pin, HIGH);
      pinMode(_ss_pin, OUTPUT);
      SPI.begin(); 

    }

    ControllerState read() {
      byte reply;
      if (_lastUpdate > 100) {
        _lastUpdate = 0;

        //Grab the data from the SPI bus
        //NOTE: The SPI speed may need to be adjusted, depending on the cabling and wire used.
        SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
        digitalWrite(_ss_pin, LOW);

        //We only need one byte, but the code is written for 2 for no particular reason
        //Stuff the outgoing data with the controller address
        byte msb = SPI.transfer(_address);
        byte lsb = SPI.transfer(0);

        //End by returning SS high
        digitalWrite(_ss_pin, HIGH);
        SPI.endTransaction();

        // do bit parsing and save to controllerstate
        _state.up =  lsb & (1 << UP);
        _state.down= lsb & (1 << DOWN);
        _state.left= lsb & (1 << LEFT);
        _state.right=lsb & (1 << RIGHT);
        _state.dance=lsb & (1 << DANCE);
        _state.bite= lsb & (1 << BITE);
        _state.up=   lsb & (1 << DANCE);

        // XORing the previous state with the current one provides us with recently modified pins
        _modified=_modified ^ _statebyte;

        //Save the input as a local byte, mostly for debugging
        _statebyte=lsb;

      }
      
      return _state;
    }

    //Short utility functions to simplify reading
    boolean upPressed() {
      return read().up;
    }
    boolean downPressed() {
      return read().down;
    }
    boolean leftPressed() {
      return read().left;
    }
    boolean rightPressed() {
      return read().right;
    }
    boolean bitePressed() {
      return read().bite;
    }
    boolean dancePressed() {
      return read().dance;
    }

    byte readByte(){
      return _statebyte;
    }
    
    
       
};

#endif
