#include "qish.h"

char **tokenize(char *line) {
  char **tokens = malloc(sizeof(char *) * 2);
  tokens[0] = line;
  tokens[1] = NULL;
  return tokens;
}
