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
#include <time.h>

unsigned char broadcast=255; //endereco de broadcast
unsigned char my_mac; //endereco MAC

/* Efetua as inicializacoes do nivel de enlace (recebe o endereco local da maquina) e inicializa o nivel  
 * fisico (recebe a especificacao da porta que sera usada para a comunicacao e o endereco IP do comutador de enlace)
 * Faz o bind para a porta escolhida e faz as inicializacoes necessarias para a camada de enlace
 * Retorna 1 em caso de sucesso e 0 em caso de falha
 */

int L_Activate_Request(unsigned char mac, int switch_port, char *switch_addr){

	/* Cada host irá iniciar o software da camada de enlace definindo o endereço MAC que irá usar. 
	 * Esse endereço ficará armazenado como variável global e poderá ser acessado pelo proprio host a qualquer tempo
	 */
	my_mac=mac;

	int   my_port;  
	char *my_addr = "192.168.1.103";

	//Gerando uma porta para que o comutador possa contactar o host
	srand ( time(NULL) );
	while((my_port = rand() % 9999)<1000);

	//Obtendo o endereco IP do host para que o comutador possa contactar o host
	//my_addr = ??? 

	if(!plug_host(my_mac, my_port, *my_addr, switch_port, switch_addr)){
		printf("--Failed plug_host\n");
	}
 
	if(!P_Activate_Request(switch_port, switch_addr)){
		printf("--Failed P_Activate_Request\n");
	}			

}

