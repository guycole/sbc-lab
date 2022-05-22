/*
 * Title:bb_gpio.h 
 *
 * Overview/Description: beaglebone gpio helpers
 *
 * Compiler/Operating System: 
 *   gcc version 8.3.0 (Debian 8.3.0-6)   
 *   BeagleBoard.org Debian Buster IoT Image 2020-04-06    
 */
#ifndef __BEAGLEBONE_H
#define __BEAGLEBONE_H

#define GPIO_BASE_DIRECTORY "/sys/class/gpio"

#define GPIO_DIRECTION_IN "in"
#define GPIO_DIRECTION_OUT "out"

typedef enum {
  DIR_IN, DIR_OUT
} GPIO_DIRECTION;

#define GPIO_EDGE_NONE "none"
#define GPIO_EDGE_RISING "rising"
#define GPIO_EDGE_FALLING "falling"
#define GPIO_EDGE_BOTH "both"

typedef enum {
  EDGE_NONE, EDGE_RISING, EDGE_FALLING, EDGE_BOTH
} GPIO_EDGE;

#define GPIO_VALUE_LOW "0"
#define GPIO_VALUE_HIGH "1"

typedef enum {
  VALUE_LOW, VALUE_HIGH
} GPIO_VALUE;

typedef struct gpio_struct {
  GPIO_DIRECTION direction;
  GPIO_EDGE edge;
  char *label;
  char *path;
  GPIO_VALUE value;
} GPIO, *GPIO_PTR;

extern void gpio_dump(GPIO_PTR candidate);
extern void gpio_factory(int id, GPIO_PTR result);
extern void gpio_free(GPIO_PTR result);
extern void gpio_set_direction(GPIO_DIRECTION direction, GPIO_PTR result);
extern void gpio_set_edge(GPIO_EDGE edge, GPIO_PTR result);
extern void gpio_set_value(GPIO_VALUE value, GPIO_PTR result);

#endif
