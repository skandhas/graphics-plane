#ifndef SK_TEXTURE_H
#define SK_TEXTURE_H

typedef struct sk_texture{
  SKTextureFilteringMode filtering_mode;
  sk_size size;
  sk_rect rect;
  GLuint id;
} sk_texture;

sk_texture * sk_texture_create(void *data, sk_size size);
void sk_texture_destroy(sk_texture *tex);
void sk_texture_release(sk_texture *tex);
void sk_texture_init(sk_texture *tex, void *data, sk_size size);
void sk_texture_preload(sk_texture *tex);
void sk_texture_draw(sk_texture *tex);

#endif
