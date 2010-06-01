fisica: fisica.c fisica.h fisica-test.c
	gcc -o fisica.bin fisica-test.c fisica.c fisica.h 
enlace: fisica
	gcc -o enlace.bin enlace-test.c enlace.c enlace.h fisica.c fisica.h
clean: fisica.bin
	rm fisica
	rm *~

