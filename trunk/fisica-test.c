/*
 * Arquivo contendo uma aplicacao para teste das funcoes da camada fisica
 *
 * Componentes: Felipe Almeida Tavares
 *              Leandro Lima Monteiro Coelho
 *		Rafael de Oliveira Costa
 */

#include <stdio.h>
#include "fisica.h"

int main()
{
	int retorno;
		
	printf("Port: %d, End: %s\n",port,end);
	
	retorno = P_Activate_Request(port, end);
	if(retorno==1){
		printf("--Sucess P_Activate_Request\n");
	}


   return 0;
}
