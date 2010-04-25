/*
 * Arquivo contendo uma aplicacao para teste das funcoes da camada fisica
 *
 * Componentes: Felipe Almeida Tavares
 *              Leandro Lima Monteiro Coelho
 *		Rafael de Oliveira Costa
 */

#include <stdio.h>
#include "fisica.h"

int main() {

	if(!P_Activate_Request(9090, "127.0.0.1")){
		printf("--Failed P_Activate_Request\n");
		P_Deactivate_Request();
	}

	printf("--Sucess P_Activate_Request\n");

	if (P_Data_Indication()) {
		printf("Byte recebido: %c\n", P_Data_Receive());
	} else {
		printf("Nenhum byte recebido\n");
	}

	P_Data_Request('o');

	if (P_Data_Indication()) {
		printf("Byte recebido: %c\n", P_Data_Receive());
	} else {
		printf("Nenhum byte recebido\n");
	}
	if (P_Data_Indication()) {
		printf("Byte recebido: %c\n", P_Data_Receive());
	} else {
		printf("Nenhum byte recebido\n");
	}

	P_Deactivate_Request();

   return 0;
}
