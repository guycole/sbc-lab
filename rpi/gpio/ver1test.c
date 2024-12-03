// write gpiod library version
//
// gcc -o ver1test ver1test.c -lgpiod
//
#include <gpiod.h>
#include <stdio.h>

int main(int argc, char **argv)
{
  printf("gpiod version:%s\n", gpiod_version_string());
}
