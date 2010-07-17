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
	int link;
	char border_router_address[20];
};

//Estrutura que representa a tabela de redirecionamento normal do roteador
struct table_redirect {
	int link;
	char address[20];
	char mask[20];
};

//Declarando as tabelas como variaveis globais
struct table_link_phy table_link_phy[NUMBER_OF_INTERFACES];
struct table_redirect table_redirect[NUMBER_OF_INTERFACES];


void init(void) {
	int i; // indice generico para auxiliar na iteração dos vetores

	// zerando as tabelas de emulacao
	for (i = 0; i < NUMBER_OF_INTERFACES; i++) {
		memset(&table_link_phy[i], 0, sizeof(table_link_phy[i]));
		memset(&table_redirect[i], 0, sizeof(table_redirect[i]));
	}
/*
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
*/
}


int start_backbone(){
	init();

//	while (1) {
//		verifica_conexoes();
//		recebe_frame();
//		verifica_frame();
//		envia_frame();
//	}

   return 1;
}
