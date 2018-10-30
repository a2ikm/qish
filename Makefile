.PHONY: all
all: qish

main.o: main.c
	clang -c main.c

run_loop.o: run_loop.c
	clang -c run_loop.c

qish: main.o run_loop.o
	clang -o qish main.o run_loop.o

.PHONY: clean
clean:
	rm -rf qish *.o
