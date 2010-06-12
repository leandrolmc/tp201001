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
	char *payload;
	char  payload_temp[PAYLOAD_SIZE];	
	unsigned char mac;	
	int mac_temp;
	int bytes_to_send=0;

	printf("'a': L_Activate_Request\n");
	printf("'t': L_Data_Request\n");
	printf("'d': L_Deactivate_Request\n");
	printf("'s': Sair\n");

	scanf("%c",&option);

	do{
		switch(option)
	      	{
               		case 'a':      
				/*
					chamar L_Activate_Request
					chamar L_Data_Request para enviar o frame especial
				*/        
				//Gerando um endereco MAC
				srand ( time(NULL) );
				mac = (rand() % 255);

				if(!L_Activate_Request(mac, SWITCH_PORT,SWITCH_ADDR)){
				       printf("--Failed L_Activate_Request\n");					
				}
				else{
					printf("--Sucess L_Activate_Request\n");
				}		
				printf("Selecione uma Função\n");
                    		break;

	               	case 't':       
				getchar();
				//Lendo do Teclado o MAC destino e o PAYLOAD
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
				L_Deactivate_Request();
				printf("--Sucess L_Deactivate_Request\n");
				printf("Selecione uma Função\n");
               			break;

               		case 's':              
                    		exit(1);
		}
		scanf("%c",&option);
	}while(option!='s');

   return 0;
}
