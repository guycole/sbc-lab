//
// read gpio like gpioinfo(1)
// gcc -o rr reader1.c -lgpiod
//
#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  printf("start\n");
  
  printf("end\n");
  return 0;
}
