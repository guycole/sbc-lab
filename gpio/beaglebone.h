/*
 * Title:beaglebone.h 
 *
 * Overview/Description: beaglebone helpers
 *
 * Compiler/Operating System: 
 *   gcc version 8.3.0 (Debian 8.3.0-6)   
 *   BeagleBoard.org Debian Buster IoT Image 2020-04-06    
 */
#ifndef __BEAGLEBONE_H
#define __BEAGLEBONE_H

#define GPIO_BASE_DIRECTORY "/sys/class/gpio/"

typedef enum {
  INPUT, OUTPUT
} GPIO_DIRECTION;

typedef enum {
  LOW, HIGH
} GPIO_VALUE;

typedef enum {
  NONE, RISING, FALLING, BOTH 
} GPIO_EDGE;

typedef struct gpio_struct {
  char *name;
  char *path;
} GPIO, *GPIO_PTR;

extern void gpio_factory(int id, GPIO_PTR result);

#endif
