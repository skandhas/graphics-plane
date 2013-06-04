#include <mruby.h>
#include <plotter.h>

void mrb_plt_init(plt_state * plt);

plt_state *
plt_open(void)
{
  plt_state *plt = malloc(sizeof(plt_state)); 
  plt->mrb = mrb_open();
  mrb_plt_init(plt);
  return plt;
}

void
plt_close(plt_state * plt)
{
  mrb_close(plt->mrb);
  free(plt);
}



