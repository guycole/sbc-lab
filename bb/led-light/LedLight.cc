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
  string dirName = "/sys/class/gpio/gpio" + to_string(gpio);
  gpioFileName = dirName + "/value";

  if (ifstream(dirName)) {
    ofstream outfile1(dirName + "/direction");
    outfile1 << "out" << endl;
    outfile1.close();

    ofstream outfile2(dirName + "/active_low");
    outfile2 << "0" << endl;
    outfile2.close();

    lightFlag(false);
  } else {
    throw;
  }
}

void LedLight::lightFlag(bool flag) {
  ofstream outfile(gpioFileName);

  if (flag) {
    litFlag = true;
    outfile << "1" << endl;
  } else {
    litFlag = false;
    outfile << "0" << endl;
  }

  outfile.close();
}
