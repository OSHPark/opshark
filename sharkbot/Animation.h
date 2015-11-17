#ifndef ANIMATION_H
#define ANIMATION_H



#include <elapsedMillis.h>

//Interpolation methods:
#define STOP   0  //End of function
#define PAUSE  1  //Move instantly, then wait
#define SNAP   3  //Move instantly, then wait
#define LINE   4  //linear progression during duration
#define SMOOTH 5  //approximate sine curve
#define RESET  16  //Declare start conditions.


struct AnimationStep {
  long int time;
  byte motion;
  int param[10];
};


class Animation {
  private:
    boolean enabled;
    byte _numSteps, _numParams;
    void (*userFunction)(AnimationStep);
  public:
    elapsedMillis timer;

    //Create a reference to the array data
    AnimationStep (&scriptData)[10];

    Animation( AnimationStep (&script)[10] )
      : scriptData(script) //Save a reference to the external script data in our class
    {
      //setup things

      //Figure out precisely how many elements are in our script, so we can intelligently cap our process
      _numSteps = sizeof(scriptData) / sizeof(AnimationStep);
      _numParams = sizeof(AnimationStep::param) / sizeof(int);
    }
    
    //optional call with function already attached
    Animation( AnimationStep (&script)[10] , void (userfunction)(AnimationStep))
      : scriptData(script) //Save a reference to the external script data in our class
      , userFunction(userfunction)
    {
      //setup things

      //Figure out precisely how many elements are in our script, so we can intelligently cap our process
      _numSteps = sizeof(scriptData) / sizeof(AnimationStep);
      _numParams = sizeof(AnimationStep::param) / sizeof(int);
    }


    void blank(AnimationStep ignored ) {
      Serial.println("...");
      delay(10);
    }
    void start() {
      enabled = true;
      timer = 0;
    }
    void stop() {
      enabled = false;
    }
    boolean isEnabled() {
      return enabled;
    }
    void reset() {
      timer = 0;
    }
    // This gnarly thing is a function that accepts an array of integers
    // You would use this to attach your own function that processes integers
    void script( void (&function)(AnimationStep)  ) {
      //save function reference to the userScript variable
      userFunction = function;
    }

    //This generic function calculates the current time interval, and figures out what value should be returned for each bit of data
    //Returns true if the script stops or restarts
    boolean update() {
      //Set up a blank set of values which we can pass to the user's handling method
      AnimationStep current;
      long int now = timer; //Save our current clock to make calculations more consisent
      
      //Do nothing if we're not enabled
      if ( !enabled)return false;

      //Figure out what step we're on by scanning through the provided timers
      //TODO : Save this to provide some more sane startup procedures
      int i = 0;
      while ( (now > scriptData[i].time) ) {
        i++;
      }
      //The above code winds up pushing i just farther than it should. Pull it back down, patch it later. 
      i= i>0?i-1:0;
      
      
      if ( (i + 1) > (_numSteps-1) ){
        //The math on this is weird:
        //A list of 10 items results in _numSteps of 10. 
        // However we use lookahead logic, which means that i+1 must yield a value of 9 or less, so i+1 must be 10-1 or less
        // This condition happens when i above loops over bad values, or if we simply full the entire buffer
        
        //TODO: This whole check is really wonky and inaccurate, and needs to be fixed. 
        // Animations that run over a reset time RESET get stopped instead of resetting
        //WORKAROUND: Always give RESET instructions a very large time, which will always cause it to behave immediately after
        // prior instructions (which is inaccurate, since the function should simply reset at the indicated time)
        stop();
        return true;
      }

      //Great, we've incrimented i to the point where i is pointing at the largest value with a time
      // behind us and has at least time ahead of us

      //The best defaults for our current situation are the last selected values
      current = scriptData[i];
      
      //update the user on what time we're executing with
      current.time = now;

      //Loop through every parameter, to update everything
      for (byte j = 0; j < _numParams; j++) {

        //Now, we interpolate what value we should be generating, and pass it to the user's function
        switch (scriptData[i].motion) {
          case LINE:
            current.param[j] = map(now,
                                   scriptData[i].time, scriptData[i + 1].time ,
                                   scriptData[i].param[j] , scriptData[i + 1].param[j]
                                  );
            break;;
          case SMOOTH:
            //Do maths for a smooth sine wave motion
            break;
          case PAUSE:
            // Pause at the current value
            //This requires no action, as we set the value already
            break;;
          case SNAP:
            // snap to the next value up, and wait
            current.param[j] = scriptData[i + 1].param[j];
            break;;
          case STOP:
            //This has a defined value of 0, and is the default behaviour if the script just "ends".
            stop();
            break;;
          case RESET:
            reset();
            start();
            break;;

          default:
            Serial.print("====ERROR: motion: ");
            Serial.println(scriptData[i].motion);
            stop();
            return true;
        }

      }
      

      //Call the user-specified handling function
      userFunction(current);
      return false;
    }
};

#endif
