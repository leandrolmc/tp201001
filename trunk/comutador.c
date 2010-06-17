/*
 * Arquivo onde e feita a implementacao das funcoes do comutador
 *
 * Componentes: Felipe Almeida Tavares
 *              Leandro Lima Monteiro Coelho
 *		Rafael de Oliveira Costa
 */

#include "comutador.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h> 
#include <sys/poll.h>

//Estrutura que representa a tabela de emulacao das conexoes fisicas com o comutador
struct table_phy {
//	int port_switch;
	unsigned char mac;
	int port;
	char *address;
};

//Estrutura que representa a tabela de funcionamento normal do comutador
struct table_switch {
	int port_switch;
	char *mac;
};

int last_used_port = -1; // portas fisicas (sequencial). -1 = nenhuma usada.

//Declarando as tabelas como variaveis globais
struct table_phy table_phy[NUMBER_OF_PORTS];
struct table_switch table_switch[NUMBER_OF_PORTS];

struct sockaddr_in local_addr; // informacoes de endereco local
int socket_conexoes; // socket responsavel por aguardar as conexoes fisicas
int socket_comunicacao; // socket responsavel pela comunicacao
struct pollfd ufds_con[1]; //pollfd para conexoes fisicas
struct pollfd ufds_comm[1]; //pollfd para comunicacao

char buffer_recv[BUFFER_SIZE]; //buffer onde os bytes recebidos serão armazenados
char buffer_env[BUFFER_SIZE]; //buffer onde os bytes enviados serão armazenados



void init(void) {
	int i; // indice generico para auxiliar na iteração dos vetores

	// zerando as tabelas de emulacao
	for (i = 0; i < NUMBER_OF_PORTS; i++) {
		memset(&table_phy[i], 0, sizeof(table_phy[i]));
		memset(&table_switch[i], 0, sizeof(table_switch[i]));
	}

	// criando os sockets
        if ((socket_conexoes = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
           printf("--Erro na criacao do socket\n");
           exit(-1);
        }
        if ((socket_comunicacao = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
           printf("--Erro na criacao do socket\n");
           exit(-1);
        }

	// Definindo informações do endereco local
	memset(&local_addr, 0, sizeof(local_addr));
	local_addr.sin_family = AF_INET;
	local_addr.sin_addr.s_addr = INADDR_ANY;
	local_addr.sin_port = htons(SWITCH_PORT);

	// associando a porta a maquina local
        if (bind(socket_conexoes,(struct sockaddr *)&local_addr, sizeof(struct sockaddr)) < 0) {
           printf("--Exit com erro no bind \n");
           close(socket_conexoes);
           exit(-1);
        }

	ufds_con[0].fd = socket_conexoes;
	ufds_con[0].events = POLLIN;

	ufds_comm[0].fd = socket_comunicacao;
	ufds_comm[0].events = POLLIN;
}

void verifica_conexoes(void) {
	int resultado = poll(ufds_con, 1, 1000);

	if (resultado > 0) {
		if (ufds_con[0].revents & POLLIN) {
			recvfrom(socket_conexoes, buffer_recv, sizeof(buffer_recv), 0, (struct sockaddr *)0, 0);
		}
		last_used_port++;

		table_phy[last_used_port].address = strtok(buffer_recv, "|");
		table_phy[last_used_port].port = atoi(strtok(NULL, "|"));
		table_phy[last_used_port].mac = atoi(strtok(NULL, "|"));
	}
	else if (resultado == -1) {
		printf("--erro no poll\n");
		exit(-1);
	}
}

void recebe_frame(void) {
	
}

int start_switch(){
/*
Loop:
verifica conexoes
recebe pacotes
comuta pacotes
envia pacotes

*/
	init();

	while (1) {
		verifica_conexoes();
		recebe_frame();
	}

        return 1;
}
