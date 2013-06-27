#ifndef GFX_PROGRAM_H
#define GFX_PROGRAM_H

#include "plotter/gl.h"

typedef struct gl_program_t {
  GLuint v_shader;
  GLuint f_shader;
  GLuint id;
} gl_program_t;

gl_program_t *gl_shader_open(const char *, const char *);
int gl_program_link(gl_program_t *);
void gl_program_use(gl_program_t *);
void gl_program_close(gl_program_t *);

#endif
