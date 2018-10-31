#ifndef QISH_H
#define QISH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// run_loop.c

int run_loop(FILE *in);

// utils.c

typedef struct {
  void **data;
  int capacity;
  int len;
} Vector;

Vector *vec_new(void);
void vec_free(Vector *v);
void vec_push(Vector *v, void *elm);
void **vec_flush(Vector *v);

#endif
