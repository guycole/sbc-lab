/*
 * Title: beaglebone.c 
 * 
 * Overview/Description: beaglebone gpio helpers
 * 
 * Compiler/Operating System: 
 *   gcc version 8.3.0 (Debian 8.3.0-6)
 *   BeagleBoard.org Debian Buster IoT Image 2020-04-06 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>

#include "bb_gpio.h"

#define MAX_C_BUFFER 64

void gpio_dump(GPIO_PTR candidate)
{
  if (candidate->direction == DIR_IN) {
    printf("direction:%s\n", GPIO_DIRECTION_IN);
  } else {
    printf("direction:%s\n", GPIO_DIRECTION_OUT);
  }

  switch (candidate->edge) {
    case EDGE_NONE:
      printf("edge:%s\n", GPIO_EDGE_NONE);
      break;
    case EDGE_RISING:
      printf("edge:%s\n", GPIO_EDGE_RISING);
      break;
    case EDGE_FALLING:
      printf("edge:%s\n", GPIO_EDGE_FALLING);
      break;
    case EDGE_BOTH:
      printf("edge:%s\n", GPIO_EDGE_BOTH);
      break;
  }

  if (candidate->label == NULL) {
    printf("label:NULL\n");
  } else {
    printf("label:%s\n", candidate->label);
  }

  if (candidate->path == NULL) {
    printf("path:NULL\n");
  } else {
    printf("path:%s\n", candidate->path);
  }

  if (candidate->value == VALUE_LOW) {
    printf("value:low\n");
  } else {
    printf("value:high\n");
  }
}

void gpio_read(char *file_name, char *c_ptr)
{
  FILE *f_ptr;

  if ((f_ptr = fopen(file_name, "r")) == NULL) {
    perror(file_name);
    strcpy(c_ptr, "\0");
    return;
  }

  fscanf(f_ptr, "%s", c_ptr);
  fclose(f_ptr);
}

void gpio_write(char *file_name, char *c_buffer)
{
  printf("gpio_write:%s:%s:\n", file_name, c_buffer);

  FILE *f_ptr;

  if ((f_ptr = fopen(file_name, "w")) == NULL) {
    perror(file_name);
    return;
  }

  fprintf(f_ptr, "%s", c_buffer);
  fclose(f_ptr);
}

void gpio_factory(int id, GPIO_PTR result)
{
  memset(result, 0, sizeof(GPIO));

  char c_buffer[MAX_C_BUFFER];
  sprintf(c_buffer, "%s/gpio%d", GPIO_BASE_DIRECTORY, id);
  result->path = strdup(c_buffer);

  struct stat stat_buffer;
  if (stat(GPIO_BASE_DIRECTORY, &stat_buffer) < 0) {
    perror("GPIO base directory");
    return;
  }

  if (!S_ISDIR(stat_buffer.st_mode)) {
    fprintf(stderr, "GPIO base directory is not a directory\n");
    return;
  }

  sprintf(c_buffer, "%s/direction", result->path);
  gpio_read(c_buffer, &c_buffer[0]);
  if (strlen(c_buffer) > 0) {
    if (strcmp(GPIO_DIRECTION_IN, c_buffer) == 0) {
      result->direction = DIR_IN;
    } else {
      result->direction = DIR_OUT;
    }
  }

  sprintf(c_buffer, "%s/edge", result->path);
  gpio_read(c_buffer, &c_buffer[0]);
  if (strlen(c_buffer) > 0) {
    if (strcmp(GPIO_EDGE_NONE, c_buffer) == 0) {
      result->edge = EDGE_NONE;
    } else if (strcmp(GPIO_EDGE_RISING, c_buffer) == 0) {
      result->edge = EDGE_RISING;
    } else if (strcmp(GPIO_EDGE_FALLING, c_buffer) == 0) {
      result->edge = EDGE_FALLING;
    } else {
      result->edge = EDGE_BOTH;
    }
  }

  sprintf(c_buffer, "%s/label", result->path);
  gpio_read(c_buffer, &c_buffer[0]);
  if (strlen(c_buffer) > 0) {
    result->label = strdup(c_buffer);
  }

  sprintf(c_buffer, "%s/value", result->path);
  gpio_read(c_buffer, &c_buffer[0]);
  if (strlen(c_buffer) > 0) {
    result->value = atoi(c_buffer);
  }
}

void gpio_free(GPIO_PTR result)
{
  if (result->label != NULL) {
    free(result->label);
  }

  if (result->path != NULL) {
    free(result->path);
  }

  memset(result, 0, sizeof(GPIO));
}

void gpio_set_direction(GPIO_DIRECTION direction, GPIO_PTR result)
{
  if (result->direction != direction) {
    char c_buffer[MAX_C_BUFFER];
    char file_name[MAX_C_BUFFER];

    sprintf(file_name, "%s/direction", result->path);
    if (direction == DIR_IN) {
      strcpy(c_buffer, GPIO_DIRECTION_IN);
    } else {
      strcpy(c_buffer, GPIO_DIRECTION_OUT);
    }

    gpio_write(file_name, c_buffer);

    result->direction = direction;
  }
}

void gpio_set_edge(GPIO_EDGE edge, GPIO_PTR result)
{
  if (result->edge != edge) {
    char c_buffer[MAX_C_BUFFER];
    char file_name[MAX_C_BUFFER];

    sprintf(file_name, "%s/edge", result->path);
    switch (result->edge) {
      case EDGE_NONE:
        strcpy(c_buffer, GPIO_EDGE_NONE);
        break;
      case EDGE_RISING:
        strcpy(c_buffer, GPIO_EDGE_RISING);
        break;
      case EDGE_FALLING:
        strcpy(c_buffer, GPIO_EDGE_FALLING);
        break;
      case EDGE_BOTH:
        strcpy(c_buffer, GPIO_EDGE_BOTH);
        break;
    }

    gpio_write(file_name, c_buffer);

    result->edge = edge;
  }
}

void gpio_set_value(GPIO_VALUE value, GPIO_PTR result)
{
  if (result->direction == DIR_IN) {
    fprintf(stderr, "unable to set value for input direction\n");
    return;
  }

  if (result->value != value) {
    char c_buffer[MAX_C_BUFFER];
    char file_name[MAX_C_BUFFER];

    sprintf(file_name, "%s/value", result->path);

    if (value == VALUE_LOW) {
      strcpy(c_buffer, GPIO_VALUE_LOW);
    } else {
      strcpy(c_buffer, GPIO_VALUE_HIGH);
    }

    gpio_write(file_name, c_buffer);

    result->value = value;
  }
}
