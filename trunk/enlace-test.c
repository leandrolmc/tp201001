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
	char *buffer;
	char *temp;	
	unsigned char mac=0;	
	int bytes_to_send=0;
	int not_leave=0;

	printf("'a': L_Activate_Request\n");
	printf("'t': L_Data_Request\n");
	printf("'d': L_Deactivate_Request\n");
	printf("'s': Sair\n");

	scanf("%c",&option);
	do{
		switch(option)
	      	{
               		case 'a':      
				getchar();
				        
				/* Cada host irá iniciar o software da camada de enlace definindo 
				 * o endereço MAC que irá usar. 
				 * Esse endereço ficará armazenado como variável global e poderá ser 
				 * acessado pelo proprio host a qualquer tempo
				 */

				//Gerando um endereco MAC
				srand ( time(NULL) );
				mac = (rand() % 255);

			        //Enviando o endereço do host dentro do payload do frame especial
				payload = (char*) malloc (15);
				buffer  = (char*) malloc (15);

				do{
					//Durante a ativação da camada de enlace o payload contem somente 
					//o endereço do host
					printf("Digite o IP do host\n");
					//fgets(payload,16,stdin);
					gets(payload);
					strcpy (buffer,payload);
					temp = strtok (buffer,".");
					while (temp != NULL)
					{
						if(atoi(temp)>255 || atoi(temp)<0){
							not_leave=1;
							printf("--Failed Endereco invalido\n");
							break;
						}
		    				temp = strtok (NULL, ".");
						not_leave=0;
					}	
				}while(not_leave);

				free(buffer);

				if(!L_Activate_Request(mac, SWITCH_PORT,SWITCH_ADDR)){
				       printf("--Failed L_Activate_Request\n");
				       break;
				}
				else{
			                //Criando Frame Especial
				       	//FRAME ESPECIAL: MACORIGEM|000|PORTA|ENDERECOHOST|000|

					buffer  = (char*) malloc (FRAME_SIZE);

					memset(&buffer, 0, strlen(buffer));
        				sprintf(buffer, "%d|0|%d|%s|0", mac, SWITCH_PORT, payload);

					///Solicitando a transmissao do frame especial
					//L_Data_Request(unsigned char mac_dest, char *payload, int bytes_to_send)
					bytes_to_send=strlen(buffer);
					L_Data_Request(0, buffer,bytes_to_send);
					free(buffer);
				}	
				printf("--Sucess L_Activate_Request\n");	
				printf("Selecione uma Função\n");
                    		break;

/*	               	case 't':       */
/*				getchar();*/
/*				//Lendo do Teclado o MAC destino e o PAYLOAD*/
/*				printf("Digite MAC destino\n");				*/
/*				fgets(temp,4,stdin);*/
/*				mac=atoi(temp);*/
/*				printf("Digite PAYLOAD a ser enviado\n");*/
/*				fgets(payload,PAYLOAD_SIZE,stdin);*/
/*				bytes_to_send=strlen(payload);*/

/*				//Solicitando transmissao de um quadro para o mac destino*/
/*				L_Data_Request(mac, payload, bytes_to_send);*/

/*				printf("--Sucess L_Data_Request\n");*/
/*				printf("Selecione uma Função\n");*/
/*       	            		break;*/
			
/*       	       		case 'd':              */
/*				L_Deactivate_Request();*/
/*				printf("--Sucess L_Deactivate_Request\n");*/
/*				printf("Selecione uma Função\n");*/
/*               			break;*/

               		case 's':              
                    		exit(1);
		}
		scanf("%c",&option);
	}while(option!='s');

   return 0;
}
