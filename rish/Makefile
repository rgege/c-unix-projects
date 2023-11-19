CFLAGS = -Wall -Wextra -pedantic

program: main.c
	cc $(CFLAGS) main.c input.c work.c -o rish

test: tests.c 
	cc -D'UTEST_STRING'='"testing"' -I/usr/local/include/ -o test tests.c input.c -L/usr/local/lib -lcunit

clean:
	rm -f rish test
