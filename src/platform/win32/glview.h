#ifndef GLVIEW_H
#define GLVIEW_H

typedef struct  glview glview;

glview * glview_open(int width, int height);
void glview_show(glview * view);
void glview_swap_buffers(glview * view);
void glview_close(glview * view);

 

#endif
