#include "sk.h"
#include "sk_alloc.h"

void *
sk_alloc(size_t size)
{
  assert(size > 0);
  return calloc(1, size);
}

void
sk_free(void *ptr)
{
  assert(ptr);
  free(ptr);
}



