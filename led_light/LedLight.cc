//
// Title:
//   LedLight.cc
//
// Description:
//   Control a LED via GPIO port
//
// Development Environment:
//   bone-debian-8.7-iot-armhf-2017-03-19-4gb.img
//   gcc version 4.9.2 (Debian 4.9.2-10) 
//

#include <fstream>
#include <iostream>
#include <string>

#include "LedLight.h"

using namespace std;

LedLight::LedLight(int gpio) {
  lit_flag = false;
  gpio_filename = "/sys/class/gpio/gpio" + to_string(gpio) + "/value";
}

void LedLight::lightFlag(bool flag) {
  ofstream outfile;
  outfile.open(gpio_filename);

  if (flag) {
    lit_flag = true;
    outfile << "1" << endl;
  } else {
    lit_flag = false;
    outfile << "0" << endl;
  }

  outfile.close();
}
