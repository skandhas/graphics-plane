#ifndef SK_TEXTURE_H
#define SK_TEXTURE_H

typedef struct sk_texture{
  SKTextureFilteringMode filtering_mode;
  sk_size size;
  sk_rect rect;
} sk_texture;

sk_texture * sk_texture_create(sk_byte * data, sk_size size);
void sk_texture_preload(sk_texture * tex);
#endif
