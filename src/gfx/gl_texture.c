#include "gl_texture.h"

gl_texture_t *
gl_texture_open(GLenum target)
{
  gl_texture_t * texture = calloc(1, sizeof(gl_texture_t));
  glGenTextures(1, &texture->id);
  glBindTexture(target, texture->id);
  return texture;
}

void
gl_texture_close(gl_texture_t * texture)
{
  if (texture) {
    glDeleteTextures(1, &texture->id);
    free(texture);
  }
}
