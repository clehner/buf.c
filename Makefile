CFLAGS = -std=c99 -Wall -Werror -pedantic

test: buf-test
	./$<

debug: CFLAGS += -g
debug: buf-test
	gdb ./$<

buf-test: buf.o buf-test.o

clean:
	rm -f buf.o buf-test.o buf-test
