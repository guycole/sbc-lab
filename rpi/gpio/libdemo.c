//
// gcc -o demo libdemo.c -lgpiod
//
// mostly copy of v1.6 gpioinfo.c
//
#include <errno.h>
#include <gpiod.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*(x)))
typedef bool (*is_set_func)(struct gpiod_line *);

struct flag {
  const char *name;
  is_set_func is_set;
};


static bool line_bias_is_pullup(struct gpiod_line *line) {
  return gpiod_line_bias(line) == GPIOD_LINE_BIAS_PULL_UP;
}

static bool line_bias_is_pulldown(struct gpiod_line *line) {
  return gpiod_line_bias(line) == GPIOD_LINE_BIAS_PULL_DOWN;
}

static bool line_bias_is_disabled(struct gpiod_line *line) {
  return gpiod_line_bias(line) == GPIOD_LINE_BIAS_DISABLE;
}

static const struct flag flags[] = {
  {
    .name = "used",
    .is_set = gpiod_line_is_used,
  },
  {
    .name = "open-drain",
    .is_set = gpiod_line_is_open_drain,
  },
  {
    .name = "open-source",
    .is_set = gpiod_line_is_open_source,
  },
  {
    .name = "pull-up",
    .is_set = line_bias_is_pullup,
  },
  {
    .name = "pull-down",
    .is_set = line_bias_is_pulldown,
  },
  {
    .name = "bias-disabled",
    .is_set = line_bias_is_disabled,
  },
};

static void list_lines(struct gpiod_chip *chip) {
  struct gpiod_line_iter *iter;
  int direction, active_state;
  const char *name, *consumer;
  struct gpiod_line *line;
  unsigned int ii, offset;
  bool flag_printed;

  iter = gpiod_line_iter_new(chip);
  if (!iter) {
    printf("line iterator failure\n");
    return;
  }

  printf("%s - %u lines:\n", gpiod_chip_name(chip), gpiod_chip_num_lines(chip));

  gpiod_foreach_line(iter, line) {
    offset = gpiod_line_offset(line);
    name = gpiod_line_name(line);
    consumer = gpiod_line_consumer(line);
    direction = gpiod_line_direction(line);
    active_state = gpiod_line_active_state(line);

    printf(" line ");
    printf("%3.1u: ", offset);

    if (name == NULL) {
      printf("unnamed");
    } else {
      printf("%17s", name);
    }

    if (gpiod_line_is_used(line)) {
      if (consumer == NULL) {
	printf(" kernel ");
      } else {
	printf(" %s ", consumer);
      }
    } else {
      printf(" unused ");
    }

    printf("%s ", direction == GPIOD_LINE_DIRECTION_INPUT ? "input":"output");

    printf("%s ", active_state == GPIOD_LINE_ACTIVE_STATE_LOW ? "active-low":"active-high");

    flag_printed = false;
    for (ii = 0; ii < ARRAY_SIZE(flags); ii++) {
      if (flags[ii].is_set(line)) {
	if (flag_printed)
	  printf(" ");
	else
	  printf("[");

	printf("%s", flags[ii].name);
	flag_printed = true;
      }
    }
    
    if (flag_printed) printf("]");

    printf("\n");
  }
    
  gpiod_line_iter_free(iter);
}

int main(void) {
  const char *chip_path = "/dev/gpiochip0";
  //  const char *chip_path = "/dev/gpiochip1";

  struct gpiod_chip_info *info;
  struct gpiod_chip *chip;
  
  printf("start\n");

  chip = gpiod_chip_open(chip_path);

  if (chip) {
    printf("chip open\n");
  } else {
    fprintf(stderr, "open chip failure: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }

  list_lines(chip);

#if 0
	info = gpiod_chip_get_info(chip);
	if (!info) {
		fprintf(stderr, "failed to read info: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	printf("%s [%s] (%zu lines)\n", gpiod_chip_info_get_name(info),
	       gpiod_chip_info_get_label(info),
	       gpiod_chip_info_get_num_lines(info));

	gpiod_chip_info_free(info);
#endif
	gpiod_chip_close(chip);

	return EXIT_SUCCESS;
}
