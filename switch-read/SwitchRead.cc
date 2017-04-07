//
// Title:
//   SwitchRead.cc
//
// Description:
//   Read a push button switch via GPIO port
//
// Development Environment:
//   bone-debian-8.7-iot-armhf-2017-03-19-4gb.img
//   gcc version 4.9.2 (Debian 4.9.2-10) 
//

#include <fstream>
#include <iostream>
#include <string>

#include "SwitchRead.h"

using namespace std;

SwitchRead::SwitchRead(int gpio) {
  string dirName = "/sys/class/gpio/gpio" + to_string(gpio);
  gpioFileName = dirName + "/value";

  if (ifstream(dirName)) {
    ofstream outfile1(dirName + "/direction");
    outfile1 << "in" << endl;
    outfile1.close();

    ofstream outfile2(dirName + "/active_low");
    outfile2 << "0" << endl;
    outfile2.close();

    gpioRead();
  } else {
    throw;
  }
}

bool SwitchRead::gpioRead() {
  char buffer[2];

  ifstream infile(gpioFileName);
  infile >> buffer;
  infile.close();

  if (buffer[0] < 0x31) { // ascii 1
    gpioFlag = false;
  } else {
    gpioFlag = true;
  }

  return gpioFlag;
}
