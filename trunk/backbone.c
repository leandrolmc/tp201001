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

//Declarando as tabelas como variaveis globais
struct table_link_phy table_link_phy[TABLE_LENGTH];
struct table_redirect table_redirect[TABLE_LENGTH];

int last_interface = -1; // interfaces fisicas (sequencial). -1 = nenhuma usada.

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

void init(){
	int i;

	//Setando todas as entradas da tabela como vazias
	for(i=0;i<TABLE_LENGTH;i++){
		table_redirect[i].busy=0;
	}
}

int route_add(int interface, char *net_addr,char *mask_addr){

	int not_search=0;

	last_interface++;

	while(table_redirect[last_interface].busy){

		if (last_interface==TABLE_LENGTH && table_redirect[last_interface].busy && not_search){
			return 0;
		}
		if (last_interface==TABLE_LENGTH && table_redirect[last_interface].busy){
			last_interface=-1;
			not_search=1;		
		}
		last_interface++;		
	}

	table_redirect[last_interface].interface=interface;	
	strcpy(table_redirect[last_interface].net_addr, net_addr);
	strcpy(table_redirect[last_interface].mask_addr, mask_addr);
	table_redirect[last_interface].busy=1;	

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

	if(last_interface==-1){
		printf("Redirect Table not used\n");
	}

	for(i=0;i<TABLE_LENGTH;i++){
		if(table_redirect[i].busy){
			
		printf("   %s%s-|- %s%s-|- %d\n",table_redirect[i].net_addr,print_space(strlen(table_redirect[i].net_addr)),table_redirect[i].mask_addr,print_space(strlen(table_redirect[i].mask_addr)),table_redirect[i].interface);
		}
	}
}
