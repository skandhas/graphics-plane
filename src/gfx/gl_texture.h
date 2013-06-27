#ifndef GL_TEXTURE_H
#define GL_TEXTURE_H

#include "plotter/gl.h"

typedef struct gl_texture_t {
  GLuint id;  
}gl_texture_t;

gl_texture_t * gl_texture_open(GLenum);
void gl_texture_close(gl_texture_t *);

#endif
