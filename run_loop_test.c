#include "qish.h"
#include "qish_test.h"

char *read_line(FILE *in);

int main(int argc, char **argv) {
  char *line;
  FILE *f = fopen("test/lines.txt", "r");

  line = read_line(f);
  EXPECT_S("1111", line);
  free(line);

  line = read_line(f);
  EXPECT_S("2222 3333", line);
  free(line);

  fclose(f);
  return 0;
}
