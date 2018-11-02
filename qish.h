#ifndef QISH_H
#define QISH_H

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// parse.c

char **tokenize(char *line);

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

typedef struct {
  char *data;
  int capacity;
  int len;
} StringBuilder;

StringBuilder *sb_new(void);
void sb_free(StringBuilder *sb);
void sb_add(StringBuilder *sb, char c);
char *sb_flush(StringBuilder *sb);

#endif
