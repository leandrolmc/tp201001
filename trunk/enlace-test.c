/*
 * Arquivo contendo uma aplicacao para teste das funcoes da camada de enlace
 *
 * Componentes: Felipe Almeida Tavares
 *              Leandro Lima Monteiro Coelho
 *		Rafael de Oliveira Costa
 */

#include "enlace.h"
#include "comutador.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

	char option;	
	unsigned char mac;

	printf("'a': L_Activate_Request\n");
//	printf("'d': L_Data_Request(mac_dest, data, bytes_to_send)\n");
	printf("'h': Help\n");
	printf("'s': Sair\n");

	scanf("%c",&option);

	do{
		switch(option)
	      	{
               		case 'a':              
				printf("L_Activate_Request()\n");

				//Gerando um endereco MAC
				srand ( time(NULL) );
				mac = (rand() % 255);

				if(!L_Activate_Request(mac, 5000,"127.0.0.1")){
					printf("--Failed L_Activate_Request\n");					
					exit(1);
				}		
				printf("--Sucess L_Activate_Request\n");
				printf("Selecione uma Função\n");
                    		break;
			/*
               		case 'd':       
				getchar();
				printf("L_Data_Request(unsigned char mac_dest, char *data, int bytes_to_send)\n");
				//FALTA PASSAR AS INFORMACOES
				scanf("%c",);
				scanf("%s",);

				if(!L_Data_Request(mac_dest, data, bytes_to_send)){
					printf("--Failed L_Data_Request\n");
					exit(1);					
				}		
				printf("--Sucess L_Data_Request\n");
				printf("Selecione uma Função\n");
                    		break;
			*/

               		case 'h':              
				printf("---------------------------------------------------------------------------\n");
				printf("'a': P_Activate_Request(int, char *)\n");
				printf("Efetua as inicializacoes necessarias da camada fisica,recebe a especiﬁcacao da porta que sera usada para a comunicacao e do endereco da maquina remota, retorna 1 em caso de sucesso e 0 em caso de falha\n\n");
				printf("'h': Help\n");
				printf("'s': Sair\n");
				printf("--------------------------------------------------------------------------\n");
                    		break;

               		case 's':              
                    		exit(1);
		}
		scanf("%c",&option);
	}while(option!='s');

   return 0;
}
