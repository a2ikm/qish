#include "qish.h"

void run_command(char **argv) {
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    // child
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

char *read_line(void) {
  int ch;
  int pos = 0;
  int bufsize = QISH_LINE_BUFSIZE;
  char *buffer = malloc(sizeof(char) * bufsize);

  if (buffer == NULL) {
    fprintf(stderr, "qish: memory allocation error\n");
    exit(1);
  }

  while (1) {
    ch = fgetc(stdin);
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

void evaluate(char *script) {
  char **tokens;

  tokens = tokenize(script);
  run_command(tokens);
  free(tokens);
}

int run_loop(void) {
  char *line;
  char **tokens;

  while(1) {
    printf("> ");
    line = read_line();
    evaluate(line);
    free(line);

    if (feof(stdin)) {
      break;
    }
  }
  return 0;
}
