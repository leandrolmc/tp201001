/*
 * Arquivo onde e feita a implementacao das funcoes do comutador
 *
 * Componentes: Felipe Almeida Tavares
 *              Leandro Lima Monteiro Coelho
 *		Rafael de Oliveira Costa
 */

#include "fisica.h"
#include "comutador.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h> 

//Estrutura que representa a tabela de emulacao das conexoes fisicas com o comutador
struct table_phy {
	int port_switch; //socket descriptor?
	char *mac;
	int port;
	char *address;
};

//Estrutura que representa a tabela de funcionamento normal do comutador
struct table_switch {
	//Essa porta do switch remete ao socket(endereco IP, porta) do host ao qual se quer conectar
	int port_switch;
	char *mac;
};

//Declarando as tabelas como variaveis globais
struct table_phy table_phy[NUMBER_OF_PORTS];
struct table_switch table_switch[NUMBER_OF_PORTS];

int start_switch(){

        return 1;
}
