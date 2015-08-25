#include <elapsedMillis.h>

#define BIT_UP     (1<<0)
#define BIT_DOWN   (1<<1)
#define BIT_LEFT   (1<<2)
#define BIT_RIGHT  (1<<3)
#define BIT_MISC   (1<<4)
#define BIT_BITE   (1<<5)



struct ControllerState {
  byte up;
  byte down;
  byte left;
  byte right;
  byte bite;
  byte misc;
};

class Controller_I2C {
  private:
    elapsedMillis  _lastUpdate;
    ControllerState  _state;

  public:
    Controller_I2C(int address);

    ControllerState read() {
      byte reply;
      if (_lastUpdate > 100) {
        //Read out over I2C and grab the data
        reply=4;
        // do bit parsing and save to controllerstate
        _state.up = reply & BIT_UP;
        _state.down = reply & BIT_DOWN;
        _state.left = reply & BIT_LEFT;
        _state.right = reply & BIT_RIGHT;
        _state.misc = reply & BIT_MISC;
        _state.bite = reply & BIT_BITE;
        _state.up = reply & BIT_UP;
      }
    return _state;


    }
    boolean upPressed(){    return read().up;    }
    boolean downPressed(){  return read().down;  }
    boolean leftPressed(){  return read().left;  }
    boolean rightPressed(){ return read().right; }
    boolean bitePressed(){  return read().bite;  }
    boolean miscPressed(){  return read().misc;  }


};
