#include "qish.h"

Vector *vec_new(void) {
  Vector *v = malloc(sizeof(Vector));
  v->len = 0;
  v->capacity = 16;
  v->data = malloc(sizeof(void *) * v->capacity);
  return v;
}

void vec_free(Vector *v) {
  free(v->data);
  free(v);
}

void vec_push(Vector *v, void *elm) {
  if (v->len >= v->capacity) {
    v->capacity *= 2;
    v->data = realloc(v->data, sizeof(void *) * v->capacity);
  }
  v->data[v->len++] = elm;
}

void **vec_flush(Vector *v) {
  vec_push(v, NULL);
  void **data = v->data;
  free(v);
  return data;
}
