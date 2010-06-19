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
#include <unistd.h>

void menu(char option){

	unsigned char mac;
	char *switch_addr;
	char *message_to_send;
	char *buffer;
	char *temp;
	int switch_port;
	int mac_temp;
	int not_leave=0;

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
				fgets(switch_addr, 15, stdin);
				switch_addr[strlen(switch_addr)-1] = '\0';
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

		case 'i':
			getchar();
			if(!L_Data_Indication()){
				printf("nao ");
			}        
				printf("existe um quadro recebido na camada de enlace\n");

		case 'd':
			getchar();        
			printf("Digite o MAC destino\n");
			scanf("%d",&mac_temp);
			mac=(unsigned char)mac_temp;

			getchar();
			message_to_send  = (char*) malloc (PAYLOAD_SIZE * sizeof(char));
			printf("Digite a mensagem a ser enviada\n");
			fgets(message_to_send, PAYLOAD_SIZE, stdin);
			message_to_send[strlen(message_to_send)-1] = '\0';

			L_Data_Request(mac,message_to_send,strlen(message_to_send));

			printf("--Sucess L_Data_Request\n");	
			printf("Selecione uma Função\n");
			break;

		case 's':            
			exit(1);
	}
}

int kbhit()
{
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

int getch()
{
    int r;
    unsigned char c;

    if ((r = read(0, &c, sizeof(c))) < 0) {
        return r;
    } else {
        return c;
    }
}

int main(){
	char ipreal[15];
	printf("Qual o IP real desta maquina?\n");
	fgets(ipreal, 15, stdin);
	ipreal[strlen(ipreal)-1] = '\0';

	definirIPreal(ipreal);

	while(1){
		printf("'a': L_Activate_Request\n");
		printf("'i': L_Data_Indication\n");
		printf("'d': L_Data_Request\n");
		printf("'s': Sair\n");

		while (!kbhit()) {
			L_MainLoop();
		}
		menu(getch());
	}

   return 0;
}
