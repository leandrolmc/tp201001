/*
 * Arquivo contendo uma aplicacao para teste das funcoes da camada de rede
 *
 * Componentes: Felipe Almeida Tavares
 *              Leandro Lima Monteiro Coelho
 *		Rafael de Oliveira Costa
 */

#include "fisica.h"
#include "enlace.h"
#include "rede.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>
#include <unistd.h>

int indicacao_datagrama;

void exibir_menu() {
	printf("Selecione uma Função\n");
	printf("'a': N_Activate_Request\n");
	printf("'d': N_Data_Request\n");
	printf("'i': N_Data_Indication\n");
	printf("'r': N_Data_Receive\n");
	printf("'x': N_Deactivate_Request\n");
	printf("'s': Sair\n");
}

int validar_ip_logico(char *ip) {
	int i;
	char *temp;
	char *temp_ip;
	char *temp_mask;
	char *buffer = (char*) malloc (18 * sizeof(char));

	strcpy (buffer, ip);
	temp_ip = strtok (buffer,"/");
	temp_mask = strtok(NULL, "/");
	temp = strtok (temp_ip,".");
	for (i = 0; i < 4 && temp != NULL; i++){
		if(atoi(temp)>255 || atoi(temp)<0){
			return 0;
		}
		temp = strtok (NULL, ".");
	}
	if (temp_mask != NULL) {
		if(atoi(temp_mask)>32 || atoi(temp_mask)<1){
			return 0;
		}
	}

	free(buffer);

	return 1;
}

void menu(char option){

	unsigned char mac;
	char *my_addr;
	char *dest_addr;
	char *router_addr;
	char *switch_addr;
	char *message_to_send;
	char *buffer;
	char *temp;
	int id_protocol;
	int switch_port;
	int mac_temp;
	int not_leave=0;
	
	char ip_source[18];
	char datagrama_recv[200];
	int max_datagrama;

	switch(option){
  		case 'a':
			not_leave = 0;
			router_addr  = (char*) malloc (18 * sizeof(char));
			buffer  = (char*) malloc (18 * sizeof(char));
			do{
				printf("Digite o IP do roteador de borda (formato N.N.N.N/M):\n");
				scanf("%s", router_addr);

				if (!validar_ip_logico(router_addr)) {
					not_leave = 1;
				}

				if (not_leave) {
					printf("--Failed endereco invalido\n");
				}
			}while(not_leave);

			my_addr  = (char*) malloc (18 * sizeof(char));

			do{
				printf("Digite o IP do host (formato N.N.N.N/M):\n");
				scanf("%s", my_addr);

				if (!validar_ip_logico(my_addr)) {
					not_leave = 1;
				}

				if (not_leave) {
					printf("--Failed endereco invalido\n");
				}
			}while(not_leave);
			free(buffer);
			

			do {
				printf("Digite o MAC do host\n");
				scanf("%d",&mac_temp);
				if (mac_temp < 1 || mac_temp > 255)
					printf("MAC inválido. Escolha um entre 0 e 255\n");
			} while (mac_temp < 1 || mac_temp > 255);
			mac=(unsigned char)mac_temp;

			printf("Digite a porta do comutador\n");
			scanf("%d",&switch_port);
			getchar(); // a proxima entrada eh por fgets
			
			switch_addr  = (char*) malloc (15 * sizeof(char));
			buffer  = (char*) malloc (15 * sizeof(char));
			do{
				printf("Digite o IP do comutador\n");
				fgets(switch_addr, 15, stdin);
				switch_addr[strlen(switch_addr)-1] = '\0'; //remover o \n consumido
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

			if(!N_Activate_Request(router_addr, my_addr, mac, switch_port,switch_addr)){
					 printf("--Failed N_Activate_Request\n");
					 break;
			}

			printf("--Sucess N_Activate_Request\n");
			exibir_menu();
			break;

		case 'd':
			printf("Digite a identificação do protocolo (1 - TCP, 2 - UDP):\n");
			scanf("%d",&id_protocol);

			not_leave = 0;
			dest_addr  = (char*) malloc (18 * sizeof(char));
			do{
				printf("Digite o IP destino (formato N.N.N.N/M):\n");
				scanf("%s", dest_addr);

				if (!validar_ip_logico(dest_addr)) {
					not_leave = 1;
				}

				if (not_leave) {
					printf("--Failed endereco invalido\n");
				}
			}while(not_leave);

			getchar(); // a proxima entrada eh por fgets

			message_to_send  = (char*) malloc (PAYLOAD_SIZE * sizeof(char));
			printf("Digite a mensagem a ser enviada\n");
			fgets(message_to_send, PAYLOAD_SIZE, stdin);
			message_to_send[strlen(message_to_send)-1] = '\0';

			N_Data_Request(id_protocol, dest_addr,message_to_send,strlen(message_to_send));

			printf("--Sucess N_Data_Request\n");	
			exibir_menu();
			break;

		case 'i':
			printf("Digite a identificação do protocolo (1 - TCP, 2 - UDP):\n");
			scanf("%d",&id_protocol);

			indicacao_datagrama = N_Data_Indication(id_protocol);

			if(!indicacao_datagrama){
				printf("nao ");
			}        
			printf("existe um datagrama recebido na camada de rede\n");
			exibir_menu();
			break;

		case 'r':
			printf("Digite a identificação do protocolo (1 - TCP, 2 - UDP):\n");
			scanf("%d",&id_protocol);

			if (indicacao_datagrama) {
				printf("Qual o tamanho maximo dos dados do datagrama?\n");
				scanf("%d", &max_datagrama);

				memset(&datagrama_recv, 0, sizeof(datagrama_recv));
				memset(&ip_source, 0, sizeof(ip_source));
				printf("recuperando..\n");
				if (N_Data_Receive(id_protocol, ip_source, datagrama_recv, max_datagrama) >= 0) {
				printf("A mensagem recebida do ip %s foi: %s\n", ip_source, datagrama_recv); 
				}
				else {
					printf("A mensagem recebida é maior que o tamanho maximo de dados do datagrama\n"); 
				}
			}
			else {
				printf("Verifique antes de tentar receber!\n");
			}
			exibir_menu();
			break;
	
		case 'x':
			N_Deactivate_Request();            
			printf("--Sucess N_Deactivate_Request\n");
			exibir_menu();

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

	enlace_definirIPreal(ipreal);
	fisica_definirIPreal(ipreal);

	exibir_menu();
	while(1){
		while (!kbhit()) {
			L_MainLoop();
		}
		menu(getch());
	}

   return 0;
}
