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
	char *host_addr=0;
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
				
				//chamar L_Activate_Request
				//chamar L_Data_Request para enviar o frame especial
				        
			        //Enviando o endereço do host dentro do payload do frame especial
				payload = (char*) malloc (15);
				buffer  = (char*) malloc (15);

				do{
					printf("Digite o IP do host\n");
					fgets(host_addr,16,stdin);
					strcpy (buffer,host_addr);
					temp = strtok (buffer,".");
					while (temp != NULL)
					{
						if(atoi(temp)>255 || atoi(temp)<0){
							not_leave=1;
							printf("end inv\n");
							break;
						}
		    				temp = strtok (NULL, ".");
						not_leave=0;
					}	
				}while(not_leave);

				if(!L_Activate_Request(mac, SWITCH_PORT,SWITCH_ADDR)){
				       printf("--Failed L_Activate_Request\n");
				       break;
				}
				else{
                                        //Criando Frame Especial
				       	//FRAME ESPECIAL: MACORIGEM|000|PORTA|ENDERECOHOST|000|

					memset(&payload, 0, strlen(payload));
        				sprintf(payload, "%d|0|%d|%s|0", mac, SWITCH_PORT, host_addr);

					///Solicitando a transmissao do frame especial
					//L_Data_Request(unsigned char mac_dest, char *payload, int bytes_to_send)
					bytes_to_send=strlen(payload);
					L_Data_Request(0, payload,bytes_to_send);
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
