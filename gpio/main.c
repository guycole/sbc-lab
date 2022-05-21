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

#include "beaglebone.h"

int main(int argc, char *argv[]) {
	GPIO gpio;

	printf("start\n");

	gpio_factory(666, &gpio);

	printf("%s\n", gpio.name);
	printf("%s\n", gpio.path);

	printf("stop\n");
}
