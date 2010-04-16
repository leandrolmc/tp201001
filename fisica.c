/*
 * Arquivo onde e feita a implementacao das funcoes da camada fisica
 *
 * Componentes: Felipe Almeida Tavares
 *              Leandro Lima Monteiro Coelho
 *		Rafael de Oliveira Costa
 */

#include "fisica.h"
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>

int P_Activate_Request(int port, char *end){

	int sockfd;
	
	sockfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

	//teste

}

