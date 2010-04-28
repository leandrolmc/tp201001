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

	printf("Selecione uma Função\n");
	printf("'a': P_Activate_Request\n");
	printf("'t': P_Data_Request\n");
	printf("'i': P_Data_Indication\n");
	printf("'r': P_Data_Receive\n");
	printf("'d': P_Deactivate_Request\n");
	printf("'h': Help\n");
	printf("'s': Sair\n");

	scanf("%c",&option);
	printf("\n");

	do{
		
		switch(option)
	      	{
               		case 'a':              
				printf("P_Activate_Request(int, char *)\n");
				scanf("%d %s", &param_port, param_address);

				if(!P_Activate_Request(param_port, param_address)){
					printf("--Failed P_Activate_Request\n");
					P_Deactivate_Request();
				}
				printf("--Sucess P_Activate_Request %d %s\n",param_port,param_address);
				printf("Selecione uma Função\n");
                    		break;

               		case 't':              
				getchar();
				printf("P_Data_Request(char)\n");
				scanf("%c",&byte);
				P_Data_Request(byte);
				printf("Selecione uma Função\n");
                    		break;

               		case 'i':              
				printf("P_Data_Indication(void)\n");        
				
				if (P_Data_Indication()) {
				  printf("Byte recebido: %c\n", P_Data_Receive());
				} else {
				  printf("Nenhum byte recebido\n");
				}
				printf("Selecione uma Função\n");
                    		break;

               		case 'r':              
				printf("P_Data_Receive(void)\n");
				printf("Selecione uma Função\n");
                    		break;

               		case 'd':              
				printf("P_Deactivate_Request(void)\n");                 
				printf("Selecione uma Função\n");
                    		break;

               		case 'h':              
				printf("------------------------------------------------------------------------------------\n");
				printf("'a': P_Activate_Request(int, char *)\n");
				printf("Efetua as inicializacoes necessarias da camada fisica,recebe a especiﬁcacao da porta que sera usada para a comunicacao e do endereco da maquina remota, retorna 1 em caso de sucesso e 0 em caso de falha\n\n");
				printf("'t': P_Data_Request(char)\n");
				printf("Solicita a transmissao de 1 byte e recebe o byte a ser transmitido\n\n");
				printf("'i': P_Data_Indication(void)\n");
				printf("Testa se ha um byte recebido na camada fisica, retorna 1 caso exista um byte recebido na camada fisica\n\n");
				printf("'r': P_Data_Receive(void)\n");
				printf("Busca na camada fisica o ultimo byte recebido e retorna o byte recebido\n\n");
				printf("'d': P_Deactivate_Request(void)\n");
				printf("Encerra o canal de comunicacao estabelecido\n\n");
				printf("'h': Help\n");
				printf("'s': Sair\n");
				printf("------------------------------------------------------------------------------------\n");
                    		break;

               		case 's':              
                    		exit(1);



		}
		scanf("%c",&option);
	}while(option!='s');
   return 0;
}
