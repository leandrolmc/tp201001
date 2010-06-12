fisica: fisica.c fisica.h fisica-test.c
	gcc -o fisica.bin fisica-test.c fisica.c fisica.h 

comutador: comutador.c comutador.h comutador-test.c
	gcc -o comutador.bin comutador.c comutador-test.c comutador.h -g -Wall

enlace: fisica.c fisica.h enlace-test.c enlace.c enlace.h comutador.c comutador.h 
	gcc -o enlace.bin enlace-test.c enlace.c enlace.h comutador.c comutador.h fisica.c fisica.h -g -Wall

clean:
	rm *.bin
	rm *~ 

