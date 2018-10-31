#include "qish.h"

char **tokenize(char *line) {
  Vector *tokens = vec_new();
  vec_push(tokens, line);
  return (char **)vec_flush(tokens);
}
