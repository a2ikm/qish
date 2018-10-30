#include "../qish.h"

char *read_line(FILE *in);

#define EXPECT(expected, actual)                            \
  do {                                                      \
    char *e = (expected);                                   \
    char *a = (actual);                                     \
    if (strcmp(e, a) != 0) {                                \
      fprintf(stderr, "line %d: expected %s, but got %s\n", \
          __LINE__, e, a);                                  \
      exit(1);                                              \
    }                                                       \
  } while(0)

int main(int argc, char **argv) {
  char *line;
  FILE *f = fopen("test/lines.txt", "r");

  line = read_line(f);
  EXPECT("1111", line);
  free(line);

  line = read_line(f);
  EXPECT("2222 3333", line);
  free(line);

  fclose(f);
  return 0;
}
