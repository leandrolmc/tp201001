fisica: fisica.h fisica.c fisica-test.c
	gcc -o fisica.bin fisica.h fisica.c fisica-test.c 

comutador: comutador.h comutador.c comutador-test.c
	gcc -o comutador.bin comutador.h comutador.c comutador-test.c fisica.h fisica.c

enlace: fisica.h fisica.c enlace.h enlace.c enlace-test.c comutador.h comutador.c 
	gcc -o enlace.bin enlace.h enlace.c enlace-test.c fisica.h fisica.c

rede:  fisica.h fisica.c enlace.h enlace.c rede.h rede.c rede-test.c 
	gcc -o rede.bin rede.h rede.c rede-test.c enlace.c enlace.h fisica.h fisica.c

roteador: roteador.h roteador.c roteador-test.c rede.h rede.c
	gcc -o roteador.bin roteador.h roteador.c roteador-test.c 

backbone: backbone.h backbone.c backbone-test.c
	gcc -o backbone.bin backbone.h backbone.c backbone-test.c 

clean:
	rm *.bin
	rm *~ 

