#include "../qish.h"

char *read_line(FILE *in);

int main(int argc, char **argv) {
  char *line;
  FILE *f = fopen("test/lines.txt", "r");

  line = read_line(f);
  if (strcmp("1111", line) != 0) {
    fprintf(stderr, "expected \"1111\" but got \"%s\"\n", line);
    exit(1);
  }
  free(line);

  line = read_line(f);
  if (strcmp("2222 3333", line) != 0) {
    fprintf(stderr, "expected \"2222 3333\" but got \"%s\"\n", line);
    exit(1);
  }
  free(line);

  fclose(f);
  return 0;
}
