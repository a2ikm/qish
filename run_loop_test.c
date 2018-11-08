#include "qish.h"
#include "qish_test.h"

char *read_line(void);
void evaluate(char *script);

#define EXPECT_READ_LINE(expected)                                  \
  do {                                                              \
    char *e = (expected);                                           \
    int old_stdin = write_and_redirect_input_fd(e);                 \
    char *a = read_line();                                          \
    reset_input_fd(old_stdin);                                      \
    if (strcmp(e, a) != 0) {                                        \
      fprintf(stderr, "line %d: expected \"%s\", but got \"%s\"\n", \
          __LINE__, e, a);                                          \
      exit(1);                                                      \
    }                                                               \
    free(a);                                                        \
  } while(0)

#define EXPECT_EVALUATE(script, expected)                           \
  do {                                                              \
    char *s = (script);                                             \
    char *e = (expected);                                           \
    int old_stdout = redirect_output_fd(e);                         \
    evaluate(s);                                                    \
    char a[256];                                                    \
    read_and_reset_output_fd(old_stdout, a);                        \
    if (strcmp(e, a) != 0) {                                        \
      fprintf(stderr, "line %d: expected \"%s\", but got \"%s\"\n", \
          __LINE__, e, a);                                          \
      exit(1);                                                      \
    }                                                               \
  } while(0)

int write_and_redirect_input_fd(char *script) {
  FILE *in;
  int old_stdin;

  in = fopen("test/input.txt", "w");
  fputs(script, in);
  fclose(in);

  in = fopen("test/input.txt", "r");
  old_stdin = dup(STDIN_FILENO);
  close(STDIN_FILENO);
  dup2(fileno(in), STDIN_FILENO);
  fclose(in);
  rewind(stdin);

  return old_stdin;
}

void reset_input_fd(int old_stdin) {
  close(STDIN_FILENO);
  dup2(old_stdin, STDIN_FILENO);
  close(old_stdin);
}

int redirect_output_fd(char *script) {
  FILE *out;
  int old_stdout;

  out = fopen("test/output.txt", "w");
  old_stdout = dup(STDOUT_FILENO);
  close(STDOUT_FILENO);
  dup2(fileno(out), STDOUT_FILENO);
  fclose(out);
  rewind(stdout);

  return old_stdout;
}

void read_and_reset_output_fd(int old_stdout, char *output) {
  FILE *out;

  close(STDOUT_FILENO);
  dup2(old_stdout, STDOUT_FILENO);
  close(old_stdout);

  out = fopen("test/output.txt", "r");
  fgets(output, sizeof(output), out);
  fclose(out);
}

void test_read_line(void) {
  char *line;
  int old_stdin;

  EXPECT_READ_LINE("1111");
  EXPECT_READ_LINE("1111 2222");
}

void test_evaluate(void) {
  EXPECT_EVALUATE("echo 1", "1\n");
  EXPECT_EVALUATE("echo 1 2", "1 2\n");
}

int main(int argc, char **argv) {
  test_read_line();
  test_evaluate();
  return 0;
}
