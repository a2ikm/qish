#include "qish.h"
#include "qish_test.h"

char *read_line(FILE *in);

int main(int argc, char **argv) {
  char *line;
  FILE *in;

  in = fopen("test/input.txt", "w");
  fputs("1111", in);
  fclose(in);
  in = fopen("test/input.txt", "r");
  line = read_line(in);
  EXPECT_S("1111", line);
  free(line);
  fclose(in);

  in = fopen("test/input.txt", "w");
  fputs("2222 3333", in);
  fclose(in);
  in = fopen("test/input.txt", "r");
  line = read_line(in);
  EXPECT_S("2222 3333", line);
  free(line);

  fclose(f);
  return 0;
}
