//
// Title:
//   LedLight.h
//
// Description:
//   Control a LED via GPIO port
//
// Development Environment:
//   bone-debian-8.7-iot-armhf-2017-03-19-4gb.img
//   gcc version 4.9.2 (Debian 4.9.2-10) 
//

#include <string> 

using namespace std;

#ifndef _LED_LIGHT_H_
#define _LED_LIGHT_H_

class LedLight {
private:
  bool litFlag;
  string gpioFileName;
public:
  LedLight(int gpio);
  void lightFlag(bool flag);
  bool isLit(){return litFlag;}
};

#endif
