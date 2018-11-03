#include "qish.h"

void run_command(char **argv, FILE *out) {
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    // child
    int out_fd = fileno(out);
    close(1);
    dup2(out_fd, 1);
    close(out_fd);

    if (execvp(argv[0], argv) == -1) {
      fprintf(stderr, "qish: %s\n", strerror(errno));
    }
    exit(1);
  } else if (pid < 0) {
    fprintf(stderr, "qish: fork error\n");
    exit(1);
  } else {
    // parent
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
}

#define QISH_LINE_BUFSIZE 256

char *read_line(FILE *in) {
  int ch;
  int pos = 0;
  int bufsize = QISH_LINE_BUFSIZE;
  char *buffer = malloc(sizeof(char) * bufsize);

  if (buffer == NULL) {
    fprintf(stderr, "qish: memory allocation error\n");
    exit(1);
  }

  while (1) {
    ch = fgetc(in);
    if (ch == EOF || ch == '\n') {
      buffer[pos] = '\0';
      return buffer;
    }

    buffer[pos] = ch;
    pos++;

    if (pos >= bufsize) {
      bufsize *= 2;
      buffer = realloc(buffer, bufsize);
      if (buffer == NULL) {
        fprintf(stderr, "qish: memory allocation error\n");
        exit(1);
      }
    }
  }
}

void evaluate(char *script, FILE *out) {
  char **tokens;

  tokens = tokenize(script);
  run_command(tokens, out);
  free(tokens);
}

int run_loop(FILE *in, FILE *out) {
  char *line;
  char **tokens;

  while(1) {
    printf("> ");
    line = read_line(in);
    evaluate(line, out);
    free(line);

    if (feof(in)) {
      break;
    }
  }
  return 0;
}
