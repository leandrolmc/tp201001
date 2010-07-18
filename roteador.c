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

/*
 ****************************************
 ***        Variaveis Globais         ***
 ****************************************
 */

char *router_addr; //variavel que ira armazenar o IP do roteador de borda

/*
 ****************************************
 ***        Funcoes Auxiliares        ***
 ****************************************
 */

//Funcao utilizada para fazer a conexao logica do roteador de borda com o backbone
void link_to_backbone(){
}

//Funcao inicia o funcionamento do roteador de borda
void init(){
}

/*
 ****************************************
 ***    Funcoes da API do Roteador    ***
 ****************************************
 */

int start_router(char *net_addr){
	router_addr  = (char*) malloc (20 * sizeof(char));
	strcpy (router_addr,net_addr);
	//link_to_backbone();
	//init();

	return 1;
}
