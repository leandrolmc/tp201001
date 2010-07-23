/*
 * Arquivo contendo uma aplicacao para teste das funcoes do comutador
 *
 * Componentes: Felipe Almeida Tavares
 *              Leandro Lima Monteiro Coelho
 *		Rafael de Oliveira Costa
 */

#include "comutador.h"
#include <stdio.h>
#include <string.h>

int main(){

	char ipreal[15];
	printf("Qual o IP real desta maquina?\n");
	fgets(ipreal, 15, stdin);
	ipreal[strlen(ipreal)-1] = '\0';

	comutador_definirIPreal(ipreal);

	printf("--Iniciando comutador...\n");

	if(!start_switch()){
		printf("--Failed start_switch\n");
	}

   return 0;
}
