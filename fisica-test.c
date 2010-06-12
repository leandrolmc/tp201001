/*
 * Arquivo contendo uma aplicacao para teste das funcoes da camada fisica
 *
 * Componentes: Felipe Almeida Tavares
 *              Leandro Lima Monteiro Coelho
 *		Rafael de Oliveira Costa
 */

#include <stdio.h>
#include <stdlib.h>
#include "fisica.h"

int main() {

	char option;
	int param_port;
	char param_address[15];
	char byte;

	printf("'a': P_Activate_Request\n");
	printf("'t': P_Data_Request\n");
	printf("'i': P_Data_Indication\n");
	printf("'d': P_Deactivate_Request\n");
	printf("'h': Help\n");
	printf("'s': Sair\n");

	scanf("%c",&option);

	do{
		
		switch(option)
	      	{
               		case 'a':              
				printf("P_Activate_Request(int, char *)\n");
				scanf("%d %s", &param_port, param_address);

				if(!P_Activate_Request(param_port, param_address)){
					printf("--Failed P_Activate_Request\n");
					P_Deactivate_Request();
					printf("Selecione uma FunÃ§Ã£o\n");
					continue;
				}
				printf("--Sucess P_Activate_Request %d %s\n",param_port,param_address);
				printf("Selecione uma FunÃ§Ã£o\n");
                    		break;

               		case 't':              
				getchar();
				printf("P_Data_Request(char)\n");
				scanf("%c",&byte);
				P_Data_Request(byte);
				printf("Selecione uma FunÃ§Ã£o\n");
                    		break;

               		case 'i':              
				printf("P_Data_Indication(void)\n");        
				
				if (P_Data_Indication()) {
				  printf("O Byte recebido foi %c\n",P_Data_Receive());
				} else {
				  printf("Nenhum byte recebido\n");
				}
				printf("Selecione uma Função\n");
                    		break;

               		case 'd':              
				printf("P_Deactivate_Request(void)\n");  
				P_Deactivate_Request();
				printf("--Sucess P_Deactivate_Request\n");
				printf("Selecione uma FunÃ§Ã£o\n");
                    		break;

               		case 'h':              
				printf("'a': P_Activate_Request\n");
				printf("'t': P_Data_Request\n");
				printf("'i': P_Data_Indication\n");
				printf("'d': P_Deactivate_Request\n");
				printf("'h': Help\n");
				printf("'s': Sair\n");
                    		break;

               		case 's':              
                    		exit(1);

		}
		scanf("%c",&option);
	}while(option!='s');
   return 0;
}

