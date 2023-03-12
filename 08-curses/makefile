LDFLAGS = -l curses
obj = ${patsubst %.c, %, $(wildcard *.c)};

all : ${obj}

hello1 : hello1.c
	$(CC) $< $(LDFLAGS) -o $@

hello2 : hello2.c
	$(CC) $< $(LDFLAGS) -o $@

hello3 : hello3.c
	$(CC) $< $(LDFLAGS) -o $@

hello4 : hello4.c
	$(CC) $< $(LDFLAGS) -o $@

hello5 : hello5.c
	$(CC) $< $(LDFLAGS) -o $@

bounce1d : bounce1d.c
	$(CC) $< $(LDFLAGS) -o $@

bounce2d : bounce2d.c
	$(CC) $< $(LDFLAGS) -o $@

bounce_async : bounce_async.c
	$(CC) $< $(LDFLAGS) -o $@

bounce_aio : bounce_aio.c
	$(CC) $< $(LDFLAGS) -o $@ -lrt

.PHONY : clean
clean :
	-rm ${obj}