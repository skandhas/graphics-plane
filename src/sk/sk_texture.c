#include "sk.h"
#include "sk_alloc.h"
#include "sk_node.h"
#include "sk_texture.h"

sk_texture *
sk_texture_create(void *data, sk_size size)
{
  sk_texture *tex = sk_alloc(sizeof(sk_texture)); 
  assert(tex);  
  sk_texture_init(tex, data, size);

  return tex;
}

void
sk_texture_destroy(sk_texture *tex)
{
  sk_texture_release(tex); 
  sk_free(tex);
}

void
sk_texture_release(sk_texture *tex)
{
  glDeleteTextures(1, &tex->id);
}

void
sk_texture_init(sk_texture *tex, void *data, sk_size size)
{
  glPixelStorei(GL_UNPACK_ALIGNMENT, 8); 

  glGenTextures(1, &tex->id); 
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, tex->id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  
  /* RGBA8888 */
  glTexImage2D(GL_TEXTURE_2D,
               0,
               GL_RGBA,
               (GLsizei)size.width,
               (GLsizei)size.height,
               0,
               GL_RGBA,
               GL_UNSIGNED_BYTE,
               data);

  glBindTexture(GL_TEXTURE_2D, 0);
  tex->size = size;
}

void 
sk_texture_draw(sk_texture * tex)
{
  

}
