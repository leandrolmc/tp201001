/*
 * Arquivo onde e feita a implementacao das funcoes do backbone
 *
 * Componentes: Felipe Almeida Tavares
 *              Leandro Lima Monteiro Coelho
 *					 Rafael de Oliveira Costa
 */

#include "backbone.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h> 
#include <sys/poll.h>
#include <arpa/inet.h>


//Estrutura que representa a tabela de emulacao dos enlaces fisicos com os roteadores de borda das subredes
struct table_link_phy {
	int interface;
	char real_border_router_address[20];
	int  real_border_router_port;
};

//Estrutura que representa a tabela de redirecionamento normal do roteador
struct table_redirect {
	int interface;
	char net_addr[20];
	char mask_addr[20];
};

//Declarando as tabelas como variaveis globais
struct table_link_phy table_link_phy[NUMBER_OF_INTERFACES];
struct table_redirect table_redirect[NUMBER_OF_INTERFACES];

int last_interface = -1; // interfaces fisicas (sequencial). -1 = nenhuma usada.

/*

char ipbackbone[15]; // variavel contendo o ip real do backbone

char buffer_conexoes[BUFFER_SIZE]; //buffer onde os bytes recebidos serão armazenados



int socket_conexoes; // socket responsavel por aguardar os links fisicos com o backbone
struct sockaddr_in local_addr; // informacoes de endereco local
struct pollfd ufds_con[1]; //pollfd para conexoes os links fisicos
*/

/*
struct sockaddr_in local_addr_comm[NUMBER_OF_PORTS]; // informacoes de endereco local
int socket_comunicacao[NUMBER_OF_PORTS]; // socket responsavel pela comunicacao
struct pollfd ufds_comm[NUMBER_OF_PORTS]; //pollfd para comunicacao
*/

/*
void init(void) {
	int i; // indice generico para auxiliar na iteração dos vetores

	// zerando as tabelas de emulacao
	for (i = 0; i < NUMBER_OF_INTERFACES; i++) {
		memset(&table_link_phy[i], 0, sizeof(table_link_phy[i]));
		memset(&table_redirect[i], 0, sizeof(table_redirect[i]));
	}

	// criando os sockets
        if ((socket_conexoes = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
           printf("--Erro na criacao do socket\n");
           exit(-1);
        }

	printf("Qual o IP do backbone ?\n");
	fgets(ipbackbone, 15, stdin);
	ipbackbone[strlen(ipbackbone)-1] = '\0';

	// Definindo informações do endereco local
	memset(&local_addr, 0, sizeof(local_addr));
	local_addr.sin_family = AF_INET;
	local_addr.sin_addr.s_addr = inet_addr(ipbackbone);
	local_addr.sin_port = htons(BACKBONE_PORT);

	// associando a porta a maquina local
        if (bind(socket_conexoes,(struct sockaddr *)&local_addr, sizeof(struct sockaddr)) < 0) {
           printf("--Exit com erro no bind \n");
           close(socket_conexoes);
           exit(-1);
        }

	ufds_con[0].fd = socket_conexoes;
	ufds_con[0].events = POLLIN;
}
*/


/*
void verifica_conexoes(void) {
	int resultado = poll(ufds_con, 1, 500);

	if (resultado > 0) {
		if (ufds_con[0].revents & POLLIN) {
			if (recvfrom(socket_conexoes, buffer_conexoes, sizeof(buffer_conexoes), 0, (struct sockaddr *)0, 0) > 0) {
		
			last_link++;

			strcpy(table_link_phy[last_link].border_router_address, strtok(buffer_conexoes, "|"));
			table_link_phy[last_link].border_router_port = atoi(strtok(NULL, "|"));
			table_link_phy[last_link].mac = atoi(strtok(NULL, "|"));
			
		
->
			// Criação da conexao de link fisico com o backbone
			// Criando socket
			if ((socket_comunicacao[last_link] = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
			   printf("--Erro na criacao do socket\n");
			   exit(-1);
			}
			// Definindo informações do endereco local
			memset(&local_addr, 0, sizeof(local_addr));
			local_addr_comm[last_link].sin_family = AF_INET;
			local_addr_comm[last_link].sin_addr.s_addr = INADDR_ANY;
			local_addr_comm[last_link].sin_port = htons(table_link_phy[last_link].border_router_port);

			// associando a porta a maquina local
			if (bind(socket_comunicacao[last_link],(struct sockaddr *)&local_addr_comm[last_link], sizeof(struct sockaddr)) < 0) {
			   printf("--Exit com erro no bind da porta %d\n", table_link_phy[last_link].border_router_port);
			   close(socket_comunicacao[last_link]);
			   exit(-1);
			}
			ufds_comm[last_link].fd = socket_comunicacao[last_link];
			ufds_comm[last_link].events = POLLIN;

			printf("Conexão estabelecida na interface %d. Mac: %d | IP: %s | Porta: %d\n", last_link, table_link_phy[last_link].mac, table_link_phy[last_link].address, table_link_phy[last_link].border_router_port);

			// preenchendo tabela de comutacao
			table_redirect[last_link].mac = table_link_phy[last_link].mac;
			table_redirect[last_link].sec = time(NULL);

			memset(&buffer_conexoes, 0, sizeof(buffer_conexoes));
		}
		}
	}
	else if (resultado == -1) {
		printf("--erro no poll\n");
		exit(-1);
	}


}
*/

int start_backbone(){
//	init();

//	while (1) {
//		verifica_conexoes();
//		recebe_frame();
//		verifica_frame();
//		envia_frame();
//	}

   return 1;
}

int route_add(int interface, char *net_addr,char *mask_addr){

	last_interface++;
	if ((last_interface+1)==NUMBER_OF_INTERFACES){
		return 0;	
	}

	table_redirect[last_interface].interface=interface;	
	strcpy(table_redirect[last_interface].net_addr, net_addr);
	strcpy(table_redirect[last_interface].mask_addr, mask_addr);

	printf("%d\n",table_redirect[last_interface].interface);
	puts(table_redirect[last_interface].net_addr);
	puts(table_redirect[last_interface].mask_addr);
	
	


	return 1;
}

