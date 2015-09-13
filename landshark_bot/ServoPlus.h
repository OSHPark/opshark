#ifndef SERVOPLUS_H
#define SERVOPLUS_H

#include <Arduino.h>
#include <Servo.h>


class ServoPlus{
private:
	struct Map{
		int inlow;
		int inhigh;
		int outlow;
		int outhigh;
	} _map	;
	
	int _max;
	int _min;
	int _offset;
	
	int _lastValue;
	Servo servo;
public:
	ServoPlus(){
		_map={0,180,0,180};
		_max=180;
		_min=0;
		_offset=0;
	}
	
	
	void attach(int pin){
		servo.attach(pin);
	}
	void writeMicroSeconds(int microseconds){
		//This function is inherently unsafe, so it's not advised to use it directly.
		//servo.writeMicroSeconds();
	}
	
	int read(){
		return _lastValue;
	}
	void write(int position){
		_lastValue=position;
		position+=_offset;
		
		position=::map(position, _map.inlow, _map.inhigh, _map.outlow,  _map.outhigh);
		
		position=constrain(position,_min,_max);
		
        
		//TODO: Ideally, this should write to microseconds to get better precision mapping.   
		servo.write(position);
	}
	
	void detach(){
		servo.detach();
	}
	
	void restrict(int min, int max){
		_min=constrain(min,0,180);
		_max=constrain(max,0,180);
	}

	void restrictMapped(int min, int max){
		restrict(
			::map(min, _map.inlow, _map.inhigh, _map.outlow,  _map.outhigh)
			,::map(max, _map.inlow, _map.inhigh, _map.outlow,  _map.outhigh)
		);
	}

	void mirror(){
		//This function just inverts the output range, which mirrors the servo across any given
		//inputs
		_map={_map.inlow,_map.inhigh,_map.outhigh,_map.outlow};
	}
	
	void map(int inlow, int inhigh,int outlow,int outhigh){
		_map={inlow,inhigh,outlow,outhigh};
		
	}
	void offset(int offset){
		_offset=offset;
	}

};



#endif
