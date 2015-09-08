#include <elapsedMillis.h>

class WifiShark{
  private:
    elapsedMillis  _lastUpdate;

  public:
    WifiShark(int address);
    
    boolean write();

    
};

