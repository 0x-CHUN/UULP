obj = smsh2

smsh2 : 
	gcc ${obj}.c splitline.c execute.c process.c controlflow.c -o ${obj}

.PHONY : clean
clean :
	-rm ${obj}
