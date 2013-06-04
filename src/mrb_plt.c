#ifndef MRB_PLOTTER_H
#define MRB_PLOTTER_H
#include <mruby.h>
#include <plotter.h>

void mrb_plt_vector_init(plt_state * plotter);

void
mrb_plt_init(plt_state * plt)
{
  plt->plotter_module = mrb_define_module(plt->mrb, "Plotter");

  mrb_plt_vector_init(plt);

}

#endif

