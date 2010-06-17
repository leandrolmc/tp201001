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
#include <sys/poll.h>

struct pollfd input; 

/*
int main()
{
	struct pollfd input;
	char buffer[BUFFERSIZE];
	int n, m;
	
	input.fd      = 0;
	input.events  = POLLIN | POLLPRI;
	input.revents = 0;
	
	while (1) {
		n = poll(&input, 1, 1000);
		printf("poll returned with result = %d and revents = %d.\n",
		       n, input.revents);
		if (n > 0) {
			m = read(0, buffer, sizeof(buffer));
			printf("read returned %d.\n", m);
			if  (m == 0)
				break;
		}
	}
	return 0;
}
*/

void menu(){
/*	char buffer[80];
	int n,m;

	n = poll(&input, 1, 1000);
	if(n>0){
			m = read(0, buffer, sizeof(buffer));
			printf("read returned %d.\n", m);
			if  (m == 0)
				break;
			
							do{
										switch(option){
									  		case 'a':      
												getchar();        
												printf("Digite o MAC do host\n");
												scanf("%d",&mac_temp);
												mac=(unsigned char)mac_temp;

												getchar();
												printf("Digite a porta do comutador\n");
												scanf("%d",&switch_port);

												getchar();
												switch_addr  = (char*) malloc (15);
												buffer  = (char*) malloc (15);
												do{
													printf("Digite o IP do comutador\n");
													gets(switch_addr);
													strcpy (buffer,switch_addr);
													temp = strtok (buffer,".");
													while (temp != NULL)
													{
														if(atoi(temp)>255 || atoi(temp)<0){
															not_leave=1;
															printf("--Failed endereco invalido\n");
															break;
														}
											 			temp = strtok (NULL, ".");
														not_leave=0;
													}	
												}while(not_leave);
												free(buffer);

												if(!L_Activate_Request(mac, switch_port,switch_addr)){
														 printf("--Failed L_Activate_Request\n");
														 break;
												}

												printf("--Sucess L_Activate_Request\n");
												printf("Selecione uma Função\n");
												break;
									  		
											case 'd':
												getchar();        
												printf("Digite o MAC destino\n");
												scanf("%d",&mac_temp);
												mac=(unsigned char)mac_temp;
	
												getchar();
												message_to_send  = (char*) malloc (PAYLOAD_SIZE);
												printf("Digite a mensagem a ser enviada\n");
												gets(message_to_send);

												L_Data_Request(mac,message_to_send,strlen(message_to_send));

												printf("--Sucess L_Data_Request\n");	
												printf("Selecione uma Função\n");
												break;

											case 's':            
												exit(1);
										}
										scanf("%c",&option);
									}while(option!='s');
*/
}

int main(){

	unsigned char mac;
	char *switch_addr;
	char *message_to_send;
	char *buffer;
	char *temp;
	int switch_port;
	int mac_temp;
	int not_leave=0;

	input.fd      = 0;
	input.events  = POLLIN | POLLPRI;
	input.revents = 0;

	printf("'a': L_Activate_Request\n");
	printf("'d': L_Data_Request\n");
	printf("'s': Sair\n");
	while(1){
		menu();
		L_MainLoop();
	}



   return 0;
}
