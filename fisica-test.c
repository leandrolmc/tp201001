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
	retorno = P_Activate_Request(9090, "127.0.0.1");
	if(!retorno){
		printf("--Failed P_Activate_Request\n");
		P_Deactivate_Request();
	}

	printf("--Sucess P_Activate_Request\n");
	P_Deactivate_Request();

   return 0;
}
