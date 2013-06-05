#ifndef GLVIEW_H
#define GLVIEW_H

typedef struct  glview glview;

glview * glview_open(int width, int height);
void glview_show(glview *);
int glview_width(glview *);
int glview_height(glview *);
void * glview_target(glview *);
void glview_set_target(glview *, void *);
void glview_swap_buffers(glview *);
void glview_close(glview *);

 

#endif
