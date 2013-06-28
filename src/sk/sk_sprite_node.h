#ifndef SK_SPRITE_NODE_H
#define SK_SPRITE_NODE_H

typedef struct sk_sprite_node {
  sk_node *node;
  sk_texture * tex; 
  sk_point anchor;
  sk_rect center;
  SKBlendMode blend;
  sk_float blend_factor;
  struct sk_color *color;
  sk_size size;
}sk_sprite_node;


void sk_sprite_node_draw(sk_sprite_node *sprite);

#endif
