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

/*
 ****************************************
 ***     Declaracao de Estruturas     ***
 ****************************************
 */

//Estrutura que representa a tabela de emulacao dos enlaces fisicos com os roteadores de borda das subredes
struct table_link_phy {
	int interface;
	char real_border_router_address[20];
	int  real_border_router_port;
};

//Estrutura que representa a tabela de redirecionamento normal do roteador
struct table_redirect {
	int interface;
	char ip_addr[20];
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
struct table_redirect table_redirect[NUMBER_OF_INTERFACES];

int last_interface = -1; // interfaces fisicas (sequencial). -1 = nenhuma usada.

struct sockaddr_in local_addr; // informacoes de endereco local
int socket_conexoes; // socket responsavel por aguardar as conexoes logicas do roteador de borda para o backbone
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

int route_add(int interface, char *ip_addr,char *mask_addr){

	int not_search=0;

	last_interface++;

	while(table_redirect[last_interface].busy){

		if (last_interface==NUMBER_OF_INTERFACES && table_redirect[last_interface].busy && not_search){
			return 0;
		}
		if (last_interface==NUMBER_OF_INTERFACES && table_redirect[last_interface].busy){
			last_interface=-1;
			not_search=1;		
		}
		last_interface++;		
	}

	table_redirect[last_interface].interface=interface;	
	strcpy(table_redirect[last_interface].ip_addr, ip_addr);
	strcpy(table_redirect[last_interface].mask_addr, mask_addr);
	table_redirect[last_interface].busy=1;	

	printf("--Sucess Route Added\n");
	return 1;
}

int route_del(char *ip_addr,char *mask_addr){

	int i;

	for(i=0;i<NUMBER_OF_INTERFACES;i++){
		if(!strcmp(table_redirect[i].ip_addr,ip_addr) && !strcmp(table_redirect[i].mask_addr,mask_addr) && table_redirect[i].busy){
			table_redirect[i].busy=0;
			printf("--Sucess Route Removed\n");
			return 1;
		}
	}
	return 0;
}

void list_table(){

	int i;

	if(last_interface==-1){
		printf("Redirect Table not used\n");
	}

	for(i=0;i<NUMBER_OF_INTERFACES;i++){
		if(table_redirect[i].busy){
			
		printf("   %s%s-|- %s%s-|- %d\n",table_redirect[i].ip_addr,print_space(strlen(table_redirect[i].ip_addr)),table_redirect[i].mask_addr,print_space(strlen(table_redirect[i].mask_addr)),table_redirect[i].interface);
		}
	}
}

void init(){
	int i;

	//Setando todas as entradas da tabela como vazias
	for(i=0;i<NUMBER_OF_INTERFACES;i++){
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


	//Preparando o poll para aguardar eventos que avisem quando dados estão prontos para serem recebidos
	//pela função recv() (POLLIN) no socket socket_conexoes
	ufds_con[0].fd = socket_conexoes;
	ufds_con[0].events = POLLIN;

}

void verifica_conexoes() {	

	int resultado = poll(ufds_con, 1, 500);

	if (resultado > 0) {
		if (ufds_con[0].revents & POLLIN) {
			if (recvfrom(socket_conexoes, buffer_conexoes, sizeof(buffer_conexoes), 0, (struct sockaddr *)0, 0) > 0) {
	
				last_interface++;

				//preenchendo a tabela de conexao logica com os roteadores de borda
				table_link_phy[last_interface].interface=last_interface;
				strcpy(table_link_phy[last_interface].real_border_router_address, strtok(buffer_conexoes, "|"));
				table_link_phy[last_interface].real_border_router_port = atoi(strtok(NULL, "|"));

				// preenchendo tabela de redirecionamento
				table_redirect[last_interface].interface=last_interface;		   
				strcpy(table_redirect[last_interface].ip_addr,strtok(NULL, "|"));
				strcpy(table_redirect[last_interface].mask_addr,strtok(NULL, "|"));
				table_redirect[last_interface].busy=1;

				// TODO Criação da conexao de enlace
				// Criando socket
				if ((socket_comunicacao[last_interface] = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
					printf("--Erro na criacao do socket\n");
					exit(-1);
				}
				// Definindo informações do endereco local
				memset(&local_addr, 0, sizeof(local_addr));
				local_addr_comm[last_interface].sin_family = AF_INET;
				local_addr_comm[last_interface].sin_addr.s_addr = inet_addr(table_link_phy[last_interface].real_border_router_address);
				local_addr_comm[last_interface].sin_port = htons(table_link_phy[last_interface].real_border_router_port);

				// associando a porta a maquina local
				if (bind(socket_comunicacao[last_interface],(struct sockaddr *)&local_addr_comm[last_interface], sizeof(struct sockaddr)) < 0) {
					printf("--Exit com erro no bind da porta %d\n", table_link_phy[last_interface].real_border_router_port);
					close(socket_comunicacao[last_interface]);
					exit(-1);
				}
				ufds_comm[last_interface].fd = socket_comunicacao[last_interface];
				ufds_comm[last_interface].events = POLLIN;

				list_table();

//				printf("Conexão estabelecida na interface %d. Mac: %d | IP: %s | Porta: %d\n", last_interface, table_link_phy[last_interface].mac, table_link_phy[last_interface].address, table_link_phy[last_interface].port);

				memset(&buffer_conexoes, 0, sizeof(buffer_conexoes));
			}
		}
	}
	else if (resultado == -1) {
		printf("--erro no poll\n");
		exit(-1);
	}
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

