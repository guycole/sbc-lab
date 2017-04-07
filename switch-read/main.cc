//
// Title:main.cc
//
// Description:
//   SwitchRead test driver
//   g++ -o x1 -Wall -std=c++11 main.cc SwitchRead.cc
//
// Development Environment:
//   bone-debian-8.7-iot-armhf-2017-03-19-4gb.img
//   gcc version 4.9.2 (Debian 4.9.2-10) 
//

#include <iostream>

#include "SwitchRead.h"

using namespace std;

int main(int argc, char *argv[]) {
  cout << "start start start" << endl;

  SwitchRead *test1 = new SwitchRead(117);
  cout << test1->gpioRead() << endl;

  cout << "end end end" << endl;
}
