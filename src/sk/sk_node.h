#ifndef SK_NODE_H
#define SK_NODE_H

typedef struct sk_node {
  struct sk_node  *parent;
  struct sk_scene *scene;
  sk_point position;
  sk_float speed;
  sk_float alpha;
  sk_float x_scale;
  sk_float y_scale;
  sk_float z_position;
  sk_float z_rotation;
}sk_node;

void sk_node_add_child(sk_node *node, sk_node *child);

#endif
