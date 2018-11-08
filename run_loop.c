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

char *read_line(void) {
  int ch;
  StringBuilder *sb = sb_new();

  while (1) {
    ch = fgetc(stdin);
    if (ch == EOF || ch == '\n') {
      return sb_flush(sb);
    }

    sb_add(sb, ch);
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
