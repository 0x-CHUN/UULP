obj = smsh4

smsh2 : 
	gcc ${obj}.c splitline.c execute.c process.c controlflow.c builtin.c \
	varlib.c -o ${obj}

.PHONY : clean
clean :
	-rm ${obj}
