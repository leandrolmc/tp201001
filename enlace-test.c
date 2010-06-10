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
#include <string.h>

int main(){

	char option;
	char payload_temp[PAYLOAD_SIZE];	
	int mac_temp;
	unsigned char mac;
	char *payload;
	int bytes_to_send=0;

	printf("'a': L_Activate_Request\n");
	printf("'t': L_Data_Request\n");
	printf("'d': L_Deactivate_Request\n");
	printf("'h': Help\n");
	printf("'s': Sair\n");

	scanf("%c",&option);

	do{
		switch(option)
	      	{
               		case 'a':              
				//Gerando um endereco MAC
				srand ( time(NULL) );
				mac = (rand() % 255);
				if(!L_Activate_Request(mac, 5000,"127.0.0.1")){
				       printf("--Failed L_Activate_Request\n");					
				       exit(0);
				}		
				printf("--Sucess L_Activate_Request\n");
				printf("Selecione uma Função\n");
                    		break;

			
	               		case 't':       
				getchar();

				//Lendo do Teclado MAC destino e o PAYLOAD
				printf("Digite MAC destino\n");				
				scanf("%d",&mac_temp);
				mac = (unsigned char)mac_temp;
				printf("Digite PAYLOAD a ser enviado\n");
				scanf("%s",payload_temp);
				payload=payload_temp;
				bytes_to_send=strlen(payload);

				//Solicitando transmissao de um quadro para o mac destino
				L_Data_Request(mac, payload, bytes_to_send);

				printf("--Sucess L_Data_Request\n");
				printf("Selecione uma Função\n");
                    		break;
			

               		case 'd':              
				P_Deactivate_Request();
				printf("--Sucess L_Deactivate_Request\n");
				printf("Selecione uma Função\n");
                    		break;

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
