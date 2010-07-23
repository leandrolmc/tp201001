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
#include <sys/poll.h>
#include <errno.h>
#include <unistd.h> 

#define BUFFER_SIZE 1024

int phy_sd; // descritor do socket
socklen_t fromlen;

struct sockaddr_in local_addr; // informacoes de endereco local
struct sockaddr_in remote_addr; // informacoes de endereco remoto

struct pollfd ufds[1];

char buffer_send[BUFFER_SIZE]; //buffer onde os bytes enviados serão armazenados
char buffer_recv[BUFFER_SIZE]; //buffer onde os bytes recebidos serão armazenados
int last=0; //aponta pro ultimo byte recebido em buffer

char ipreal[15];

/*
 * Efetua as inicializacoes necessarias da camada fisica.
 *
 * Parametros
 * port: porta que sera usada para a comunicacao; o valor dessa porta deve ser diferente de 5000 (porta do comutador)
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
	memset(&local_addr, 0, sizeof(local_addr));
	local_addr.sin_family = AF_INET;
	local_addr.sin_addr.s_addr = inet_addr(ipreal);
	local_addr.sin_port = htons(port);

	// associando a porta a maquina local
        if (bind(phy_sd,(struct sockaddr *)&local_addr, sizeof(struct sockaddr)) < 0) {
           printf("--Exit com erro no bind \n");
           close(phy_sd);
           return 0;
        } 

	memset(&remote_addr, 0, sizeof(remote_addr));
	if (addr != NULL) {
		// Definindo informações do endereco remoto
		remote_addr.sin_family = AF_INET;
		remote_addr.sin_addr.s_addr = inet_addr(addr);
		remote_addr.sin_port = htons(port);
	}

	ufds[0].fd = phy_sd;
	ufds[0].events = POLLIN;

        return 1;
}

/*
 * Solicita a transmissao de 1 byte
 *
 * Parametros
 * byte_to_send: o byte (caracter) a ser transmitido
 */
void P_Data_Request(char byte_to_send){
	sprintf(buffer_send, "%c", byte_to_send); // melhorar essa parte. não mais.

	if ((sendto(phy_sd, buffer_send, strlen(buffer_send), 0, (struct sockaddr*)&remote_addr, sizeof (struct sockaddr_in))) < 0) {
		printf("--Erro na transmissão\n");
		close(phy_sd);
	}
	else {
		printf("-- Byte \'%c\' transmitido com sucesso.\n", byte_to_send);
	}
}

/*
 * Testa se há um byte recebido na camada física.
 *
 * Retorna 1 em caso exista um byte recebido na camada física
 */
int P_Data_Indication(void){
	int resultado = poll(ufds, 1, 500);
	if (resultado == -1) {
		printf("--erro no poll\n");
		return 0;
	}
	return resultado;
}

/*
 * Busca na camada fisica o ultimo byte recebido
 *
 * Retorna o byte recebido
 */
char P_Data_Receive(void){
	if (ufds[0].revents & POLLIN) {
		recvfrom(phy_sd, buffer_recv, sizeof(buffer_recv), 0, (struct sockaddr *)&remote_addr, &fromlen);
	}

	return buffer_recv[last];
}

/*
 * Encerra o canal de comunicacao estabelecido
 */
void P_Deactivate_Request(void){
	close(phy_sd);
}

/* ** funcao auxiliar ** */
void fisica_definirIPreal(char * ip) {
	strcpy(ipreal, ip);

}
