#include <windows.h>
#include "plotter.h"
#include "plotter/glview.h"
#include "plotter/director.h"
#include "glcontroller.h"

static void
draw(glcontroller * controller)
{
   plt_director_draw(controller->director);
   glview_swap_buffers(controller->view);
}

static struct controller_action_vector controller_actions = {
  0,
  0,
  &draw
};

glcontroller *
glcontroller_open(plt_director * director, glview * view)
{
   glcontroller * controller = calloc(1, sizeof(glcontroller));
   controller->director = director;
   controller->view = view;
   controller->actions = &controller_actions; 
   glview_set_target(view, controller);
   plt_director_set_viewport(director, glview_width(view), glview_height(view));
   return controller;
}

void 
glcontroller_close(glcontroller * controller)
{
  free(controller);
}

