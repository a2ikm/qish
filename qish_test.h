#define EXPECT_S(expected, actual)                                  \
  do {                                                              \
    char *e = (expected);                                           \
    char *a = (actual);                                             \
    if (strcmp(e, a) != 0) {                                        \
      fprintf(stderr, "line %d: expected \"%s\", but got \"%s\"\n", \
          __LINE__, e, a);                                          \
      exit(1);                                                      \
    }                                                               \
  } while(0)

#define EXPECT_I(expected, actual)                          \
  do {                                                      \
    int e = (expected);                                     \
    int a = (actual);                                       \
    if (e != a) {                                           \
      fprintf(stderr, "line %d: expected %d, but got %d\n", \
          __LINE__, e, a);                                  \
      exit(1);                                              \
    }                                                       \
  } while(0)
