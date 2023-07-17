CC      = gcc
CFLAGS  = -W -Wall -Wextra -pedantic
LDFLAGS = -shared

obj/cstring.o: src/cstring.c
	$(CC) $(CFLAGS) -fPIC -c src/cstring.c -o $@

lib/libcstring.so: obj/*.o
	$(CC) $(CFLAGS) $(LDFLAGS) obj/*.o -o $@

bin/test01: test/test01.c src/cstring.c
	$(CC) $(CFLAGS) test/test01.c src/cstring.c -o $@

bin/test02: test/test01.c src/cstring.c
	$(CC) $(CFLAGS) test/test02.c src/cstring.c -o $@