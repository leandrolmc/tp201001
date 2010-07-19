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
	int busy;
};

//Estrutura que representa o buffer de recebimento e envio de datagramas da camada de rede
struct buffer_backbone {
	char buf[DATAGRAMA_SIZE];
	int full;
	int pos;
} buffer_recv, buffer_env;

/*
 ****************************************
 ***        Variaveis Globais         ***
 ****************************************
 */

//Declarando as tabelas como variaveis globais
struct table_link_phy table_link_phy[NUMBER_OF_INTERFACES];
struct table_redirect table_redirect[TABLE_LENGTH];

int last_interface = -1; // interfaces fisicas (sequencial). -1 = nenhuma usada.

// variavel que aponta para a ultima posicao da tabela de redirecionamento(sequencial). -1 = nenhuma usada.
int last_table = -1; 

struct sockaddr_in local_addr; // informacoes de endereco local
int socket_conexoes; // socket responsavel por aguardar as conexoes logicas entre o roteador de borda e o backbone
struct pollfd ufds_con[1]; //pollfd para conexoes logicas entre o roteador de borda e o backbone

char buffer_conexoes[BUFFER_SIZE]; //buffer onde os bytes recebidos serão armazenados

struct sockaddr_in local_addr_comm[NUMBER_OF_INTERFACES]; 	// informacoes de endereco local
int socket_comunicacao[NUMBER_OF_INTERFACES]; 					// socket responsavel pela comunicacao
struct pollfd ufds_comm[NUMBER_OF_INTERFACES]; 			  		// pollfd para comunicacao

/*
 ****************************************
 ***        Funcoes Auxiliares        ***
 ****************************************
 */

//funcao que imprime espacos em branco
char* print_space(int tam){
	int i;
	char *spaces;

	tam=16-tam;
	spaces = (char*) malloc (tam * sizeof(char));

	for (i=0;i<tam;i++){
		spaces[i]='\ ';
	}
		spaces[i+1]='\0';

	return spaces;
}

/*
 ****************************************
 ***    Funcoes da API do Backbone    ***
 ****************************************
 */

int route_add(int interface, char *net_addr,char *mask_addr){

	int not_search=0;

	last_table++;

	while(table_redirect[last_table].busy){

		if (last_table==TABLE_LENGTH && table_redirect[last_table].busy && not_search){
			return 0;
		}
		if (last_table==TABLE_LENGTH && table_redirect[last_table].busy){
			last_table=-1;
			not_search=1;		
		}
		last_table++;		
	}

	table_redirect[last_table].interface=interface;	
	strcpy(table_redirect[last_table].net_addr, net_addr);
	strcpy(table_redirect[last_table].mask_addr, mask_addr);
	table_redirect[last_table].busy=1;	

	printf("--Sucess Route Added\n");
	return 1;
}

int route_del(char *net_addr,char *mask_addr){

	int i;

	for(i=0;i<TABLE_LENGTH;i++){
		if(!strcmp(table_redirect[i].net_addr,net_addr) && !strcmp(table_redirect[i].mask_addr,mask_addr) && table_redirect[i].busy){
			table_redirect[i].busy=0;
			printf("--Sucess Route Removed\n");
			return 1;
		}
	}


	return 0;
}

void list_table(){

	int i;

	if(last_table==-1){
		printf("Redirect Table not used\n");
	}

	for(i=0;i<TABLE_LENGTH;i++){
		if(table_redirect[i].busy){
			
		printf("   %s%s-|- %s%s-|- %d\n",table_redirect[i].net_addr,print_space(strlen(table_redirect[i].net_addr)),table_redirect[i].mask_addr,print_space(strlen(table_redirect[i].mask_addr)),table_redirect[i].interface);
		}
	}
}

void init(){
	int i;

	//Setando todas as entradas da tabela como vazias
	for(i=0;i<TABLE_LENGTH;i++){
		table_redirect[i].busy=0;
	}

	// criando os sockets
        if ((socket_conexoes = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
           printf("--Erro na criacao do socket\n");
           exit(-1);
        }

	// Definindo informações do endereco local
	memset(&local_addr, 0, sizeof(local_addr));
	local_addr.sin_family = AF_INET;
	local_addr.sin_addr.s_addr = inet_addr(BACKBONE_IP);
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


int start_backbone(){
	init();

	while (1) {
		verifica_conexoes();
//		recebe_frame();
//		verifica_frame();
//		envia_frame();
	}

   return 1;
}

void verifica_conexoes() {	
}
