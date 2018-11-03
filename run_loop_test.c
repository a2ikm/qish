#include "qish.h"
#include "qish_test.h"

char *read_line(FILE *in);
void evaluate(char *script, FILE *out);

void test_read_line(void) {
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
  fclose(in);
}

void test_evaluate_output(char *command, char *expected) {
  char actual[256];
  FILE *out;

  out = fopen("test/output.txt", "w");
  evaluate(command, out);
  fclose(out);

  out = fopen("test/output.txt", "r");
  fgets(actual, sizeof(actual), out);
  fclose(out);

  if (strcmp(expected, actual) != 0) {
    fprintf(stderr, "command \"%s\": expected \"%s\", but got \"%s\"\n",
        command, expected, actual);
  }
}

void test_evaluate(void) {
  test_evaluate_output("echo 1", "1\n");
  test_evaluate_output("echo 1 2", "1 2\n");
}

int main(int argc, char **argv) {
  test_read_line();
  test_evaluate();
  return 0;
}
