#ifndef PLOTTER_H
#define PLOTTER_H

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
typedef uint8_t plt_bool;

#ifndef FALSE
# define FALSE 0
#endif

#ifndef TRUE
# define TRUE 1
#endif

typedef  struct plt_state {
  struct mrb_state * mrb;
  struct RClass *plotter_module;
  struct RClass *vector2_class;
  struct RClass *vector3_class;
  struct RClass *plane_class;
  struct RClass *matrix3_class;
  struct RClass *matrix4_class;
}plt_state;

plt_state * plt_open(void);
void plt_close(plt_state *);

#endif
