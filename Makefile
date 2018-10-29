.PHONY: all
all: qish

qish: main.c
	clang -o qish main.c

.PHONY: clean
clean:
	rm -rf qish
