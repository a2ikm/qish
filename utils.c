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

StringBuilder *sb_new(void) {
  StringBuilder *sb = malloc(sizeof(StringBuilder));
  sb->len = 0;
  sb->capacity = 16;
  sb->data = malloc(sizeof(char) * sb->capacity);
  return sb;
}

void sb_free(StringBuilder *sb) {
  free(sb->data);
  free(sb);
}

void sb_add(StringBuilder *sb, char c) {
  if (sb->len >= sb->capacity) {
    sb->capacity *= 2;
    sb->data = realloc(sb->data, sizeof(char) * sb->capacity);
  }
  sb->data[sb->len++] = c;
}

char *sb_flush(StringBuilder *sb) {
  sb_add(sb, '\0');
  char *string = sb->data;
  free(sb);
  return string;
}
