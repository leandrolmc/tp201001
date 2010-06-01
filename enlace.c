/*
 * Arquivo onde e feita a implementacao das funcoes da camada de enlace
 *
 * Componentes: Felipe Almeida Tavares
 *              Leandro Lima Monteiro Coelho
 *		Rafael de Oliveira Costa
 */

#include "enlace.h"
#include <stdio.h>

/* Efetua as inicializacoes do nivel de enlace (recebe o endereco local da maquina) e inicializa o nivel  
 * fisico (recebe a especificacao da porta que sera usada para a comunicacao e o endereco IP do comutador de enlace)
 * Faz o bind para a porta escolhida e faz as inicializacoes necessarias para a camada de enlace
 * Retorna 1 em caso de sucesso e 0 em caso de falha
 */

int L_Activate_Request(unsigned char mac, int port, char *addr){
	
	if(P_Activate_Request(port, addr)){
		printf("Conectou com a camada fisica\n");
	}

}

