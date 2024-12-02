//
// Title:main.cc
//
// Description:
//   LedLight test driver
//   g++ -o x1 -Wall -std=c++11 main.cc LedLight.cc
//
// Development Environment:
//   bone-debian-8.7-iot-armhf-2017-03-19-4gb.img
//   gcc version 4.9.2 (Debian 4.9.2-10) 
//

#include <iostream>

#include "LedLight.h"

using namespace std;

int main(int argc, char *argv[]) {
  cout << "start start start" << endl;

  LedLight *test1 = new LedLight(60);
  test1->lightFlag(true);

  cout << "end end end" << endl;
}
