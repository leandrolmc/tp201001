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

#define BUFFER_SIZE 1024

int phy_sd; // descritor do socket
int last=0; //aponta pro ultimo byte recebido em buffer
struct sockaddr_in local_addr; // informacoes de endereco local
struct sockaddr_in remote_addr; // informacoes de endereco remoto
char *raddress; // endereco da maquina remota
char buffer[BUFFER_SIZE]; //buffer onde os bytes recebidos serão armazenados

void setAddress(struct sockaddr_in, sa_family_t, unsigned int, int);

/*
 * Efetua as inicializacoes necessarias da camada fisica.
 *
 * Parametros
 * port: porta que sera usada para a comunicacao
 * addr: endereco da maquina remota
 *
 * Retorna 1 em caso de sucesso e 0 em caso de falha
 */
int P_Activate_Request(int port, char *addr){
        
	// criando o socket
        if ((phy_sd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
           printf("--Erro na criacao do socket\n");
           return 0;
        }

	// Definindo informações do endereco local
	setAddress(local_addr, AF_INET, INADDR_ANY, port);

	// associando a porta a maquina local
        if (bind(phy_sd,(struct sockaddr *)&local_addr, sizeof(struct sockaddr)) < 0) {
           printf("--Exit com erro no bind \n");
           close(phy_sd);
           return 0;
        } 


	// Definindo informações do endereco local
	setAddress(remote_addr, AF_INET, inet_addr(addr), port);

        return 1;

}

void P_Data_Request(char byte_to_send){
	buffer[0] = byte_to_send;
	buffer[1] = '\0'; // temporario. melhorar esta parte.

	if ((sendto(phy_sd, buffer, strlen(buffer), 0, (struct sockaddr*)&remote_addr, sizeof (struct sockaddr))) < 0) {
		printf("--Erro na transmissão\n");
	}
	else {
		printf("-- Dados transmitidos com sucesso.");
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

// Busca na camada fisica o ultimo byte recebido e retorna o byte recebido
char P_Data_Receive(void){
	return buffer[last];
}

// Encerra o canal de comunicacao estabelecido
void P_Deactivate_Request(void){
	close(phy_sd);
}

/* ***** FUNÇÕES AUXILIARES ***** */
void setAddress(struct sockaddr_in addr, sa_family_t sin_family, unsigned int s_addr, int port) {
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = sin_family;
	addr.sin_addr.s_addr = s_addr;
	addr.sin_port = htons(port);
}
