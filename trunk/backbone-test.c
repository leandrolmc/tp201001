/*
 * Arquivo contendo uma aplicacao para teste das funcoes do backbone
 *
 * Componentes: Felipe Almeida Tavares
 *              Leandro Lima Monteiro Coelho
 *					 Rafael de Oliveira Costa
 */

#include "backbone.h"
#include <stdio.h>

int main(){
	printf("--Iniciando o backbone...\n");

	if(!start_backbone()){
		printf("--Failed start_backbone\n");
	}

   return 0;
}
