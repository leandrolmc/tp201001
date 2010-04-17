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
	char bts = 'r';
	char tmp;

	retorno = P_Activate_Request(90, "127.0.0.1");
	if(retorno==1){
		printf("--Sucess P_Activate_Request\n");
		P_Data_Request(bts);
		printf("--Sucess P_Data_Request\n");
		retorno=P_Data_Indication();
		if(retorno==1){
			printf("--Sucess P_Data_Indication\n");
			tmp=qretrieve();
			printf("%c\n",tmp);

		}
	}


   return 0;
}
