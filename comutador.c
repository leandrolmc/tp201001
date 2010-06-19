/*
 * Arquivo onde e feita a implementacao das funcoes do comutador
 *
 * Componentes: Felipe Almeida Tavares
 *              Leandro Lima Monteiro Coelho
 *					 Rafael de Oliveira Costa
 */

#include "enlace.h"
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
#include <time.h>
#include <string.h>
#include <arpa/inet.h>

//Estrutura que representa a tabela de emulacao das conexoes fisicas com o comutador
struct table_phy {
	unsigned char mac;
	int port;
	char address[20];
};

//Estrutura que representa a tabela de funcionamento normal do comutador
struct table_switch {
	unsigned char mac;
	time_t sec;
};

int last_port = -1; // portas fisicas (sequencial). -1 = nenhuma usada.

//Declarando as tabelas como variaveis globais
struct table_phy table_phy[NUMBER_OF_PORTS];
struct table_switch table_switch[NUMBER_OF_PORTS];

int porta_origem;
int porta_destino;
#define TODAS_PORTAS -1

struct sockaddr_in local_addr; // informacoes de endereco local
int socket_conexoes; // socket responsavel por aguardar as conexoes fisicas
struct pollfd ufds_con[1]; //pollfd para conexoes fisicas

struct sockaddr_in local_addr_comm[NUMBER_OF_PORTS]; // informacoes de endereco local
int socket_comunicacao[NUMBER_OF_PORTS]; // socket responsavel pela comunicacao
struct pollfd ufds_comm[NUMBER_OF_PORTS]; //pollfd para comunicacao

char buffer_conexoes[BUFFER_SIZE]; //buffer onde os bytes recebidos serão armazenados

struct buffer_comutador {
	char buf[FRAME_SIZE];
	int full;
	int pos;
} buffer_recv, buffer_env;


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
}

void verifica_conexoes(void) {
	int resultado = poll(ufds_con, 1, 1000);

	if (resultado > 0) {
		if (ufds_con[0].revents & POLLIN) {
			if (recvfrom(socket_conexoes, buffer_conexoes, sizeof(buffer_conexoes), 0, (struct sockaddr *)0, 0) > 0) {
		
			last_port++;

			strcpy(table_phy[last_port].address, strtok(buffer_conexoes, "|"));
			table_phy[last_port].port = atoi(strtok(NULL, "|"));
			table_phy[last_port].mac = atoi(strtok(NULL, "|"));
			
		
			// Criação da conexao de enlace
			// Criando socket
			if ((socket_comunicacao[last_port] = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
			   printf("--Erro na criacao do socket\n");
			   exit(-1);
			}
			// Definindo informações do endereco local
			memset(&local_addr, 0, sizeof(local_addr));
			local_addr_comm[last_port].sin_family = AF_INET;
			local_addr_comm[last_port].sin_addr.s_addr = INADDR_ANY;
			local_addr_comm[last_port].sin_port = htons(table_phy[last_port].port);

			// associando a porta a maquina local
			if (bind(socket_comunicacao[last_port],(struct sockaddr *)&local_addr_comm[last_port], sizeof(struct sockaddr)) < 0) {
			   printf("--Exit com erro no bind da porta %d\n", table_phy[last_port].port);
			   close(socket_comunicacao[last_port]);
			   exit(-1);
			}
			ufds_comm[last_port].fd = socket_comunicacao[last_port];
			ufds_comm[last_port].events = POLLIN;

			printf("Conexão estabelecida. Mac: %d | IP: %s | Porta: %d\n", table_phy[last_port].mac, table_phy[last_port].address, table_phy[last_port].port);

			// preenchendo tabela de comutacao
			table_switch[last_port].mac = table_phy[last_port].mac;
			table_switch[last_port].sec = time(NULL);

			memset(&buffer_conexoes, 0, sizeof(buffer_conexoes));
		}
		}
	}
	else if (resultado == -1) {
		printf("--erro no poll\n");
		exit(-1);
	}


}

void recebe_frame(void) {
	int i;

	char temp_buffer[1];

	int resultado = poll(ufds_comm, NUMBER_OF_PORTS, 100);

	if (resultado > 0) {
		if (buffer_recv.pos == 0 && !buffer_recv.full) {
			memset(&buffer_recv, 0, sizeof(buffer_recv));
		}

		for (i = 0; i < NUMBER_OF_PORTS; i++) {
			if (ufds_comm[i].revents & POLLIN) {
				recvfrom(ufds_comm[i].fd, temp_buffer, sizeof(temp_buffer), 0, (struct sockaddr *)0, 0);
				buffer_recv.buf[buffer_recv.pos] = temp_buffer[0];
				porta_origem = i;
				if (temp_buffer[0] == '$') {
					buffer_recv.pos = 0;
					buffer_recv.full = 1;
					printf("-- Recebendo byte %c da interface %d\n", temp_buffer[0], porta_origem);
				}
				else {
					buffer_recv.pos++;
					printf("-- Recebendo byte %c da interface %d\n", temp_buffer[0], porta_origem);
				}
			
			}
		}
	}
	else if (resultado == -1) {
		printf("--erro no poll\n");
		exit(-1);
	}
	
}

void verifica_frame() {
	int i;

	char frame[FRAME_SIZE];
	unsigned char mac_origem;
	unsigned char mac_destino;
	

	if (buffer_recv.full && !buffer_env.full) {
		printf("Frame recebido: %s\n", buffer_recv.buf);
		strcpy(frame, buffer_recv.buf);

		mac_origem = atoi(strtok(frame, "|"));
		mac_destino = atoi(strtok(NULL, "|"));

		if (mac_origem == mac_destino) { // descarta pacote
			memset(&buffer_recv.buf, 0, sizeof(buffer_recv.buf));
			buffer_recv.full = 0;
			buffer_env.full = 0;
			printf("mac destino = mac origem. pacote descartado.\n");

		}
		else {
			for (i = 0; i < NUMBER_OF_PORTS; i++) {
				if (table_switch[i].mac == mac_destino) {
					porta_destino = i; // encontrou a interface
					strcpy(buffer_env.buf, buffer_recv.buf);
					buffer_env.full = 1;
					printf("mac destino %d na porta %d\n", table_switch[i].mac, porta_destino);
					break;
				}
			}


			if (i == NUMBER_OF_PORTS) { // Não encontrou.. broadcast!
				porta_destino = TODAS_PORTAS;
				strcpy(buffer_env.buf, buffer_recv.buf);
				buffer_env.full = 1;
				printf("Broadcast!\n");
		
			}
		}


		memset(&buffer_recv.buf, 0, sizeof(buffer_recv.buf));
		buffer_recv.full = 0;
	}
}

void envia_frame() {
	int i;
	struct sockaddr_in remote_addr;

	char temp_buffer[1];
	
	if (buffer_env.full) {
	
	for (i = 0; i < NUMBER_OF_PORTS; i++) {
		if ((porta_destino == i) || (porta_destino == TODAS_PORTAS && porta_origem != i && table_switch[i].mac != 0)) {
			temp_buffer[0] = buffer_env.buf[buffer_env.pos];

			memset(&remote_addr, 0, sizeof(remote_addr));

			// Definindo informações do endereco remoto
			remote_addr.sin_family = AF_INET;
			remote_addr.sin_addr.s_addr = inet_addr(table_phy[i].address);
			remote_addr.sin_port = htons(table_phy[i].port);
			
			

			if ((sendto(socket_comunicacao[i], temp_buffer, sizeof(temp_buffer), 0, (struct sockaddr*)&remote_addr, sizeof (struct sockaddr_in))) < 0) {
				printf("--Erro na transmissão\n");
				close(socket_comunicacao[i]);
			}
			else {
				printf("-- Enviando byte %c pela interface %d\n", temp_buffer[0], i);
			}
		}
	}
	buffer_env.pos++;
	if (temp_buffer[0] == '$') {
		buffer_env.pos = 0;
		buffer_env.full = 0;
	}

	}
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
		verifica_frame();
		envia_frame();
	}

        return 1;
}
