/*
 * Title: beaglebone.c 
 * 
 * Overview/Description: beaglebone helpers
 * 
 * Compiler/Operating System: 
 *   gcc version 8.3.0 (Debian 8.3.0-6)
 *   BeagleBoard.org Debian Buster IoT Image 2020-04-06 
 */
#include <stdio.h>
#include <string.h>

#include "beaglebone.h"

void gpio_factory(int id, GPIO_PTR result) {
  result->name = strdup("name2");
  result->path = strdup("path2");
}
