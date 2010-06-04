/*
 * Arquivo onde e feita a implementacao das funcoes da camada de enlace
 *
 * Componentes: Felipe Almeida Tavares
 *              Leandro Lima Monteiro Coelho
 *		Rafael de Oliveira Costa
 */

#include "enlace.h"
#include "comutador.h"
#include <stdio.h>

unsigned char broadcast=255 //endereco de broadcast
unsigned char my_mac;



/* Efetua as inicializacoes do nivel de enlace (recebe o endereco local da maquina) e inicializa o nivel  
 * fisico (recebe a especificacao da porta que sera usada para a comunicacao e o endereco IP do comutador de enlace)
 * Faz o bind para a porta escolhida e faz as inicializacoes necessarias para a camada de enlace
 * Retorna 1 em caso de sucesso e 0 em caso de falha
 */

int L_Activate_Request(unsigned char mac, int port, char *addr){

	/* Cada host irá iniciar o software da camada de enlace definindo o endereço MAC que irá usar. 
	 * Esse endereço ficará armazenado como variável global e poderá ser acessado pelo proprio host a qualquer tempo
	 */
	my_mac=mac;


	
	if(P_Activate_Request(port, addr)){
		printf("Conectou com a camada fisica\n");
	}

}

