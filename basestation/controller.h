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

struct Button {
  boolean pressed;         // true means pressed, false means not pressed
  boolean newValue;          // True if the button has not been read since last change
  elapsedMillis holdTime;  // time since button was last changed;
};


struct ControllerState {
  Button up;
  Button down;
  Button left;
  Button right;
  Button bite;
  Button dance;
};

class SPIController {
  private:
    byte _address;
    byte _ss_pin;
    elapsedMillis  _lastUpdate;
    ControllerState  _state;
    byte  _statebyte, _modified;

    ControllerState controller; //internal represenation of our button states


    // Private buttons which contain the button logic regarding new/read values. 
    boolean setButton(Button& button, boolean value) {
      if (button.pressed != value) {
        button.pressed = value;
        button.holdTime = 0;
        button.newValue = true;
        return true;
      }
      else {
        return false;
      }
    }

    boolean buttonUpdated(Button& button) {
        return button.newValue;

    }
    boolean buttonPressed(Button& button) {
          button.newValue=false;
          return button.pressed;
    }
   
    boolean buttonHeld(Button& button,int time) {
      return (button.pressed && (button.holdTime > time ) );
    }
    boolean buttonHeld(Button& button) {
       buttonHeld(button,200);
    }


  public:
    SPIController(byte address, int ss_pin) {
      _address = address;
      _ss_pin = ss_pin;

      digitalWrite (_ss_pin, HIGH);
      pinMode(_ss_pin, OUTPUT);
      SPI.begin();
    }


    ControllerState update() {
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
        setButton(controller.up,lsb & (1 << UP));
        setButton(controller.down,lsb & (1 << DOWN));
        setButton(controller.left,lsb & (1 << LEFT));
        setButton(controller.right,lsb & (1 << RIGHT));
        setButton(controller.dance,lsb & (1 << DANCE));
        setButton(controller.bite,lsb & (1 << BITE));
        
      }

      return _state;
    }
    
    boolean upPressed(){ return buttonPressed(controller.up);}
    boolean upUpdated(){ return buttonUpdated(controller.up);}
    boolean upHeld(){ return buttonHeld(controller.up);}

    boolean downPressed(){ return buttonPressed(controller.down);}
    boolean downUpdated(){ return buttonUpdated(controller.down);}
    boolean downHeld(){ return buttonHeld(controller.down);}

    boolean leftPressed(){ return buttonPressed(controller.left);}
    boolean leftUpdated(){ return buttonUpdated(controller.left);}
    boolean leftHeld(){ return buttonHeld(controller.left);}

    boolean rightPressed(){ return buttonPressed(controller.right);}
    boolean rightUpdated(){ return buttonUpdated(controller.right);}
    boolean rightHeld(){ return buttonHeld(controller.right);}

    boolean bitePressed(){ return buttonPressed(controller.bite);}
    boolean biteUpdated(){ return buttonUpdated(controller.bite);}
    boolean biteHeld(){ return buttonHeld(controller.bite);}

    boolean dancePressed(){ return buttonPressed(controller.dance);}
    boolean danceUpdated(){ return buttonUpdated(controller.dance);}
    boolean danceHeld(){ return buttonHeld(controller.dance);}
    
    
    byte debug(){
      return  controller.up.pressed << UP |
        controller.down.pressed << DOWN |
        controller.left.pressed << LEFT |
        controller.right.pressed << RIGHT |
        controller.dance.pressed << DANCE |
        controller.bite.pressed << BITE ;
    }
      
};

#endif
