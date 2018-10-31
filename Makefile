.PHONY: all
all: qish

main.o: main.c
	clang -c main.c

run_loop.o: run_loop.c
	clang -c run_loop.c

qish: main.o run_loop.o
	clang -o qish main.o run_loop.o

.PHONY: test
test: clean test_run_loop test_utils

test_run_loop: run_loop.o run_loop_test.c
	clang -o run_loop.test run_loop.o run_loop_test.c
	./run_loop.test

test_utils: utils.o utils_test.c
	clang -o utils.test utils.o utils_test.c
	./utils.test

.PHONY: clean
clean:
	rm -rf qish *.o *.test
