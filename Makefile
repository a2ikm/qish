.PHONY: all
all: qish

main.o: main.c
	clang -c main.c

run_loop.o: run_loop.c
	clang -c run_loop.c

qish: main.o run_loop.o
	clang -o qish main.o run_loop.o

run_loop_test.o: test/run_loop_test.c
	clang -c test/run_loop_test.c

.PHONY: test
test: clean test_run_loop

test_run_loop: run_loop.o run_loop_test.o
	clang -o run_loop.test run_loop.o run_loop_test.o
	./run_loop.test

.PHONY: clean
clean:
	rm -rf qish *.o *.test
