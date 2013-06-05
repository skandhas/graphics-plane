#ifndef PLOTTER_DIRECTOR_H
#define PLOTTER_DIRECTOR_H

typedef struct plt_director plt_director;

plt_director * plt_director_open(void);
void plt_director_draw(plt_director *);
void plt_director_set_viewport(plt_director *, int, int);
void plt_director_close(plt_director *);

#endif
