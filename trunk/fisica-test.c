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
	int r;

	r = P_Activate_Request(90, "127.0.0.1");
	
	printf("%d",r);

   return 0;
}
