/*
 * Arquivo onde e feita a implementacao das funcoes do roteador
 *
 * Componentes: Felipe Almeida Tavares
 *              Leandro Lima Monteiro Coelho
 *					 Rafael de Oliveira Costa
 */

#include "roteador.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h> 
#include <sys/poll.h>
#include <arpa/inet.h>


/*
 ****************************************
 ***        Variaveis Globais         ***
 ****************************************
 */

char *router_addr; 					//variavel que ira armazenar o IP logico do roteador de borda
char *router_mask;					//variavel que ira armazenar a mascara logica do roteador de borda
char *real_router_addr; 					//variavel que ira armazenar o IP do roteador de borda
int real_router_port; 						//variavel que ira armazenar a porta do roteador de borda

int router_sd; 						// descritor do socket
struct sockaddr_in local_addr; 	// informacoes de endereco local
struct sockaddr_in remote_addr; 	// informacoes de endereco remoto

/*
 ****************************************
 ***        Funcoes Auxiliares        ***
 ****************************************
 */

//Funcao inicia o funcionamento do roteador de borda
void init(){

	// criando o socket
	if ((router_sd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		printf("--Erro na criacao do socket\n");
		exit(-1);
	}

	// Definindo informações do endereco local
	memset(&local_addr, 0, sizeof(local_addr));
	local_addr.sin_family = AF_INET;
	local_addr.sin_addr.s_addr = inet_addr(real_router_addr);
	local_addr.sin_port = htons(real_router_port);
	memset(local_addr.sin_zero, 0, sizeof(local_addr.sin_zero));

	// associando a porta a maquina local
        if (bind(router_sd,(struct sockaddr *)&local_addr, sizeof(struct sockaddr)) < 0) {
           printf("--Exit com erro no bind \n");
           close(router_sd);
           exit(-1);
        } 
}


//Funcao utilizada para fazer a conexao logica do roteador de borda com o backbone
int link_to_backbone(){

	char buffer_send[DATAGRAMA_SIZE]; //buffer de onde os bytes do datagrama especial serao enviados serão armazenados

	memset(&remote_addr, 0, sizeof(remote_addr));
	
	// Definindo informações do endereco remoto
	remote_addr.sin_family = AF_INET;
	remote_addr.sin_addr.s_addr = inet_addr(BACKBONE_IP);
	remote_addr.sin_port = htons(BACKBONE_PORT);

	//datagrama especial contem apenas o ip real | porta real | ip logico | mascara logica do roteador de borda
	sprintf(buffer_send, "%s|%d|%s|%s", inet_ntoa(local_addr.sin_addr), real_router_port,router_addr,router_mask);

	if ((sendto(router_sd, buffer_send, strlen(buffer_send), 0, (struct sockaddr*)&remote_addr, sizeof (struct sockaddr_in))) < 0) {
		printf("--Erro na transmissão\n");
		close(router_sd);
		return 0;
	}
	else {
		printf("-- Dados transmitidos com sucesso.\n");
		close(router_sd);
	}
   return 1;
}

/*
 ****************************************
 ***    Funcoes da API do Roteador    ***
 ****************************************
 */

int start_router(char *real_addr,int real_port,char * logic_addr,char *logic_mask){

	real_router_addr  = (char*) malloc (20 * sizeof(char));
	strcpy (real_router_addr,real_addr);

	real_router_port=real_port;

	router_addr  = (char*) malloc (20 * sizeof(char));
	strcpy (router_addr,logic_addr);		

	router_mask  = (char*) malloc (20 * sizeof(char));
	strcpy (router_mask,logic_mask);		

	init();
	link_to_backbone();

	return 1;
}
