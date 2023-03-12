all: hello_single hello_multi incrprint twordcount

hello_single: hello_single.c
	gcc hello_single.c -o hello_single

hello_multi: hello_multi.c
	gcc hello_multi.c -lpthread -o hello_multi

incrprint: incrprint.c
	gcc incrprint.c -lpthread -o incrprint

twordcount: twordcount.c
	gcc twordcount.c -lpthread -o twordcount

.PHONY : clean
clean :
	-rm hello_single hello_multi incrprint