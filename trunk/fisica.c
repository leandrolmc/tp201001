/*
 * Arquivo onde e feita a implementacao das funcoes da camada fisica
 *
 * Componentes: Felipe Almeida Tavares
 *              Leandro Lima Monteiro Coelho
 *		Rafael de Oliveira Costa
 */

#include "fisica.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h> 

#define QUEUESIZE 10

int sockfd;
struct sockaddr_in addr;

//Fila circular onde os bytes recebidos na camada física serao armazenados
char phy_queue[QUEUESIZE+1];

//Representa o byte que esta sendo movimentado na camada fisica
char byte;

//Indica a posicao da  fila onde o byte sera inserido
int spos=0;

//Indica a posicao da  fila do byte a ser retirado
int rpos=0;

//Insere um byte na fila
void qstore(char q){
    if(spos+1==rpos || (spos+1==QUEUESIZE && !rpos)){
	printf("fila cheia");
	exit(0);
    }
    phy_queue[spos] = q;
    spos++;
    if(spos==QUEUESIZE) spos=0;
}

//Retira um byte da pilha
char qretrieve(void){
    if(spos==QUEUESIZE) rpos=0;
    if(rpos==spos) return -1;
    rpos++;
    return phy_queue[rpos-1]; 
}

int P_Activate_Request(int port, char *end){
	
	if ((sockfd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0)
	{
	   printf("--Error: na criacao do socket\n");
	   return 0;
	}

	memset(&addr, 0, sizeof(addr));
  	addr.sin_family = AF_UNIX;
  	addr.sin_addr.s_addr = inet_addr(end);
  	addr.sin_port = htons(port);

	if (bind(sockfd,(struct sockaddr *)&addr, sizeof(struct sockaddr)) < 0) {
    	   printf("--Error: problemas no bind \n");
    	   close(sockfd);
    	   return 0;
  	} 

	return 1;
}

void P_Data_Request(char byte_to_send){
  
	int bytes_sent;
	
	byte = byte_to_send;
	bytes_sent = sendto(sockfd, &byte, strlen(&byte), 0, (struct sockaddr*)&addr, sizeof (struct sockaddr_in));
	
	if (bytes_sent < 0) {
	  printf("--Error: byte nao transmitido \n");
	  exit(0);
	}
}

int P_Data_Indication(void){

    ssize_t recsize;
    socklen_t fromlen;
  
    	recsize = recvfrom(sockfd, (void *)&byte, 1, 0, (struct sockaddr *)&addr, &fromlen);
    	if (recsize < 0) {
       		printf("--Error byte nao recebido \n");
		return 0;
    	}
	qstore(byte);
	return 1;
}

