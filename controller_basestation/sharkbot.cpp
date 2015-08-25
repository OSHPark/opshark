#include <elapsedMillis.h>

class Sharkbot{
  private:
    elapsedMillis  _lastUpdate;

  public:
    Sharkbot(int address);
    
    boolean write();

    
};

