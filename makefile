fisica: fisica.c fisica.h fisica-test.c
	gcc -o fisica fisica-test.c fisica.c fisica.h 
clean: fisica
	rm fisica
	rm *~

