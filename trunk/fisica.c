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
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h> 

int phy_sd;
struct sockaddr_in phy_addr;

int P_Activate_Request(int port, char *addr){
        
        if ((phy_sd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        {
           printf("--Erro na criacao do socket\n");
           return 0;
        }

        memset(&phy_addr, 0, sizeof(phy_addr));
        phy_addr.sin_family = AF_INET;
        phy_addr.sin_addr.s_addr = inet_addr("addr");
        phy_addr.sin_port = htons(port);

        if (bind(phy_sd,(struct sockaddr *)&phy_addr, sizeof(struct sockaddr)) < 0) {
           printf("--Exit com erro no bind \n");
           close(phy_sd);
           return 0;
        } 

        return 1;

}

// Solicita a transmissao de 1 byte e recebe o byte a ser transmitido
void P_Data_Request(char byte_to_send){
  
	int bytes_sent;
	bytes_sent = sendto(phy_sd, &byte_to_send, strlen(&byte_to_send), 0, (struct sockaddr*)&phy_addr, sizeof (struct sockaddr_in));
	
	if (bytes_sent < 0) {
	  printf("--Error: byte nao transmitido \n");
	  exit(0);
	}
}

/*
int P_Data_Indication(void){

    ssize_t recsize;
    socklen_t fromlen;
  
    	recsize = recvfrom(phy_sd, (void *)&byte, 1, 0, (struct sockaddr *)&addr, &fromlen);
    	if (recsize < 0) {
       		printf("--Error byte nao recebido \n");
		return 0;
    	}
	qstore(byte);
	return 1;
}

*/

void P_Deactivate_Request(void){
  close(phy_sd); 
}
