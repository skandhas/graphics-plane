#ifndef GLCONTROLLER_H
#define GLCONTROLLER_H

typedef struct glcontroller {
  glview        *view;
  plt_director  *director;
  struct controller_action_vector * actions;
}glcontroller;

typedef struct controller_action_vector{
  int  (*left_button_up)(glcontroller * controller, WPARAM state, int x, int y);
  int  (*left_button_down)(glcontroller * controller, WPARAM state, int x, int y);
  void (*draw)(glcontroller * controller);
}controller_action_vector;

glcontroller * glcontroller_open(plt_director *, glview *);
void glcontroller_close(glcontroller *);
#endif