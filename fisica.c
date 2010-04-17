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
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <unistd.h> 
#include <stdlib.h>

int sockfd;
struct sockaddr_in addr;

int P_Activate_Request(int port, char *end){
	
	if ((sockfd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0)
	{
	   printf("--Erro na criacao do socket\n");
	   return 0;
	}

	memset(&addr, 0, sizeof(addr));
  	addr.sin_family = AF_UNIX;
  	addr.sin_addr.s_addr = inet_addr(end);
  	addr.sin_port = htons(port);

	if (bind(sockfd,(struct sockaddr *)&addr, sizeof(struct sockaddr)) < 0) {
    	   printf("--Exit com erro no bind \n");
    	   close(sockfd);
    	   return 0;
  	} 

	return 1;

}
