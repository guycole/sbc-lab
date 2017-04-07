//
// Title:
//   SwitchRead.h
//
// Description:
//   Read a push button switch via GPIO port
//
// Development Environment:
//   bone-debian-8.7-iot-armhf-2017-03-19-4gb.img
//   gcc version 4.9.2 (Debian 4.9.2-10) 
//

#include <string> 

using namespace std;

#ifndef _SWITCH_READ_H_
#define _SWTICH_READ_H_

class SwitchRead {
private:
  bool gpioFlag;
  string gpioFileName;
public:
  SwitchRead(int gpio);
  bool gpioRead();
  bool isPressed(){return gpioFlag;}
};

#endif
