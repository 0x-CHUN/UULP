all: dgrecv dgsend

dgrecv: dgrecv.c dgram.c
	gcc dgrecv.c dgram.c -o dgrecv

dgsend: dgsend.c dgram.c
	gcc dgsend.c dgram.c -o dgsend

.PHONY : clean
clean :
	-rm dgrecv dgsend