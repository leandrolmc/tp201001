/*
 * Arquivo contendo uma aplicacao para teste das funcoes do comutador
 *
 * Componentes: Felipe Almeida Tavares
 *              Leandro Lima Monteiro Coelho
 *		Rafael de Oliveira Costa
 */

#include "comutador.h"
#include <stdio.h>

int main(){
	printf("--Iniciando comutador...");

	if(!start_switch()){
		printf("--Failed start_switch\n");
	}

   return 0;
}
