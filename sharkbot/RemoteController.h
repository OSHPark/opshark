/*
Abstracted class for handling and storing controller inputs recieved over MQTT

*/
#ifndef REMOTECONTROLLER
#define REMOTECONTROLLER

#include <Arduino.h>
#include <elapsedMillis.h>
#include <Streaming.h>

struct ControllerState {
  bool up ;
  bool down;
  bool left;
  bool right;
  bool bite;
  bool dance;
};


class RemoteController {
  private:
    //Button values
    ControllerState _control = {false, false, false, false, false, false};


    elapsedMillis _lastPress;
  public:

    RemoteController(int address) {}


    // Figure out the "truthyness" of the input, since everything is arbitrary strings.
    bool truthy(String string) {
      string.trim();
      string = string.substring(0, 1);

      if (
        string == "1" || // 0 / 1 scheme
        string == "t" || // true false scheme
        string == "p" || // pressed/released scheme
        string == "u"    // up /down
      ) {
        return true;
      }

      //invalid input, or the falsified side of one of the above
      return false;

    }

    ControllerState controllerState() {
      return _control;
    }

    bool upPressed() {
      return _control.up;
    }
    bool downPressed() {
      return _control.down;
    }
    bool leftPressed() {
      return _control.left;
    }
    bool rightPressed() {
      return _control.right;
    }
    bool bitePressed() {
      return _control.bite;
    }
    bool dancePressed() {
      return _control.dance;
    }

    bool isIdle() {
      if ( _lastPress > 10000) {
        //just to be safe, hard reset our controller state
        _control = {false, false, false, false, false, false};
        return true;
      }
      else {
        return false;
      }
    }

    bool isActive() {
      return !isIdle();
    }
    void  setButton(String button, String value) {
      bool tvalue = truthy(value);

      //reset our active button timer
      _lastPress = 0;

      Serial << "Button " << button << " has been " << (tvalue ? "pressed" : "released") << endl;
      if (     button == "up") {
        _control.up = tvalue;
        Serial << "Forward ho!" << endl;
      }
      else if (button == "down") {
        _control.down = tvalue;
        Serial << "Wriggle back!" << endl;
      }
      else if (button == "left") {
        _control.left = tvalue;
        Serial << "Starboard" << endl;
      }
      else if (button == "right") {
        _control.right = tvalue;
        Serial << "Port!" << endl;
      }
      else if (button == "bite") {
        _control.bite = tvalue;
        Serial << "Nom nom nom..." << endl;
      }
      else if (button == "dance") {
        _control.dance = tvalue;
        Serial << "Dance party!" << endl;
      }
      else {
        Serial << "I don't even have a " << button << " button!" << endl;
      }
    }

};

#endif

