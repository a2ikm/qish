#include "qish.h"

char **tokenize(char *p) {
  Vector *tokens = vec_new();
  StringBuilder *sb = NULL;

  while (*p) {
    if (isspace(*p)) {
      p++;
      if (sb) {
        vec_push(tokens, sb_flush(sb));
        sb = NULL;
      }
      continue;
    }

    if (sb == NULL) {
      sb = sb_new();
    }

    sb_add(sb, *p);
    p++;
  }

  if (sb) {
    vec_push(tokens, sb_flush(sb));
    sb = NULL;
  }

  return (char **)vec_flush(tokens);
}
