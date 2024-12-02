/*
 * Title:main.c 
 *
 * Overview/Description: gpio dev driver
 *
 * Compiler/Operating System:
 *   gcc version 8.3.0 (Debian 8.3.0-6)
 *   BeagleBoard.org Debian Buster IoT Image 2020-04-06
 */
#include <stdio.h>

#include "bb_gpio.h"

int main(int argc, char *argv[])
{
  GPIO gpio;

  printf("start\n");

  gpio_dump(&gpio);

  gpio_factory(60, &gpio);
  gpio_dump(&gpio);

  printf("-x-x-x-x-x-x-\n");

  gpio_set_direction(DIR_IN, &gpio);
  gpio_dump(&gpio);

  gpio_set_value(VALUE_LOW, &gpio);
  gpio_dump(&gpio);

  gpio_free(&gpio);

  printf("stop\n");
}
