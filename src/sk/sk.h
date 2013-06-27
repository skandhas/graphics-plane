#ifndef SK_H
#define SK_H

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

typedef uint8_t sk_byte;
typedef uint8_t sk_bool;
typedef float sk_float;

typedef struct sk_point {
  sk_float x, y;  
}sk_point;

typedef struct sk_size {
   sk_float width;
   sk_float height;
}sk_size;

typedef struct sk_rect {
   sk_point origin;
   sk_size  size;
}sk_rect;


typedef enum SKBlendMode {
  SKBlendModeAlpha      = 0,
  SKBlendModeAdd        = 1,
  SKBlendModeSubtract   = 2,
  SKBlendModeMultiply   = 3,
  SKBlendModeMultiplyX2 = 4,
  SKBlendModeScreen     = 5,
  SKBlendModeReplace    = 6,
}SKBlendMode;

typedef enum SKTextureFilteringMode { 
  SKTextureFilteringNearest,
  SKTextureFilteringLinear,
}SKTextureFilteringMode;


#endif

