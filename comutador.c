/*
 * Arquivo onde e feita a implementacao das funcoes do comutador
 *
 * Componentes: Felipe Almeida Tavares
 *              Leandro Lima Monteiro Coelho
 *		Rafael de Oliveira Costa
 */

#include "comutador.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h> 
#include <time.h>

//Estrutura que representa a tabela de emulacao das conexoes fisicas com o comutador
struct table_phy {
	int port_switch;
	char *mac;
	char *port;
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

int plug_host(unsigned char mac, int my_port, char *my_addr, int switch_port, char *switch_addr){

	int sockfd;
	int bytes_sent;
	char buffer[BUFFER_SIZE];

	struct sockaddr_in addr;

	// cria o descritor de socket para o servico entrega nao-confiavel
	if ((sockfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		printf("--Erro na criacao do socket\n");
		return 0;
	}

	// configura a estrutura de dados com o endereco local 
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(switch_addr); 
	addr.sin_port = htons(switch_port);
 	
	//Criando Frame Especial contendo mac,porta e endereço do host
	memset(&buffer, 0, strlen(buffer));
	sprintf(buffer, "0|%d|%d|%s|0", mac, my_port, (const char *)my_addr);

	//Enviando Frame Especial
	bytes_sent = sendto(sockfd, &buffer, strlen(buffer), 0, (struct sockaddr*)&addr, sizeof (struct sockaddr_in));
	if (bytes_sent < 0) {
		printf("--Failed Erro no Envio \n");
	}
	close(sockfd); 

	return 1;
}

int unplug_host(unsigned char mac){

	int i;
	
	//Identificando em que porta o host identificado pelo mac passado por parametro 
	for(i=1;i<=NUMBER_OF_PORTS;i++){
		//TODO Fazer essa comparação
		if( ! (table_phy[i].mac==mac) )
		{
			//Remover registro da tabela de emulacao das conexoes fisicas com o comutador
			table_phy[i].port_switch=0;
			return 1;
			//exit(0);
		}	
	}
	//TODO falta remover informacao da tabela de funcionamento normal do comutador

	printf("--Failed MAC nao encontrado\n"); 
	return 0;
}

int start_switch(){

	//Descritor do Socket
	int sockfd;

	struct 	sockaddr_in local_addr; 
	ssize_t recsize;
	socklen_t fromlen;	

	char 	buffer[BUFFER_SIZE];
	char 	*mac_source,
		*mac_dest,
		*data_length,
		*data,
		*error_code;
	
	int port_switch;

	//O endereco do comutador deve ser padrao (nesse caso, 127.0.0.1) 
	//e todos os hosts devem ter conhecimento disso.
	//TODO: ESSE ENDERECO DEVE SER REVISTO
	char *addr="127.0.0.1";

	// cria o descritor de socket para o servico entrega nao-confiavel
	if ((sockfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		printf("--Erro na criacao do socket\n");
		exit(0);
	}

	// configura a estrutura de dados com o endereco local
	memset(&local_addr, 0, sizeof(local_addr));
	local_addr.sin_family = AF_INET;
	local_addr.sin_addr.s_addr = inet_addr(addr);
	local_addr.sin_port = htons(SWITCH_PORT);

	// associa o descritor de socket com o endereco local
	if (bind(sockfd,(struct sockaddr *)&local_addr, sizeof(struct sockaddr)) < 0) {
		printf("--Exit com erro no bind \n");
		close(sockfd);
		exit(0);
	} 

	//Inicializando as tabelas do comutador
	memset(&table_phy, 0, sizeof(table_phy));
	memset(&table_switch, 0, sizeof(table_switch));

	// loop principal do servidor
	for (;;)  {
		memset(buffer, 0, sizeof(buffer));
		printf ("esperando mensagens....\n");
		recsize = recvfrom(sockfd, (void *) buffer, BUFFER_SIZE, 0, (struct sockaddr *)&local_addr, &fromlen);
		if (recsize < 0) {
			printf("--Erro no recebimento \n");
		}
		printf("mensagem recebida: %s (%d bytes)\n",buffer,recsize);

		mac_dest = strtok (NULL, "|");
		mac_source = strtok (buffer,"|");
		data_length = strtok (NULL, "|");
		data = strtok (NULL, "|");
		error_code = strtok (NULL, "|");

		//Verifica se o FRAME e especial.
		//Se for um frame especial significa que o frame veio da funcao plug_host() e portanto
		//devemos colocar as informacoes na tabela de emulacao das conexoes fisicas
		if(!strcmp(mac_dest,"0"))
		{
			table_phy[port_switch].port_switch=generate_switch_port();;
			table_phy[port_switch].mac=mac_source;
			//No frame especial utilizo o campo data-length para guardar a porta do host
			table_phy[port_switch].port=data_length;
			//No frame especial utilizo o campo data para guardar o endereco do host
			table_phy[port_switch].address=data;
		}
		else
		{
			//TODO receber outro tipo de mensagem
			printf("nao eh frame especial\n");
		}

	}
        return 1;
}

int generate_switch_port(){
	int port;

	//Gerando uma porta para o comutador
	srand ( time(NULL) );
	do{
		port = (rand() % NUMBER_OF_PORTS) + 1 ;		
	}while(table_phy[port].port_switch!=0);	//Verificar se a porta ja esta sendo utilizada	

	return port;
}

 //Abaixo estao informacoes tiradas da lista de tp com as respostas da Silvana

 /* 1)Como fazer com que esse endereço 255 seja para todos os hosts conectados ao comutador 
  *   quando este não possui nenhuma entrada na tabela?
  *
  *   Voce deverá manter duas tabelas distintas: uma responsavel pela emulacao das conexoes fisicas 
  *   entre hosts e o comutador; e outra responsavel pela operacao normal de um comutador de enlace 
  *   (da forma como vimos na aula). 
  *
  *   A primeira tabela é preenchida quando os hosts chamam a funcao L_Activate_Request e contactam o comutador 
  *   pela primeira vez (use um formato de mensagem diferenciado para essa primeira comunicaçao). 
  *   A partir daí a emulacao estará pronta (como se voce tivesse plugado fisicamente um host a uma porta de entrada 
  *   do comutador). Para cada host plugado ao comutador, deverá ser guardado na tabela de emulacao o IP desse host 
  *   e a porta para a qual ele fez o bind para que o comutador tenha as informacoes necessarias para redirecionar 
  *   os pacotes destinados a esse host no futuro. Cada entrada na tabela passará a funcionar como a identificaçao 
  *   de uma porta ativa do comutador.
  *
  *   A segunda tabela deverá ser preenchida seguindo a operacao normal de um comutador de enlace. 
  *   Uma mensagem broadcast 
  *   do comutador só atingirá os hosts que já tiverem chamado L_Activate_Request 
  *   (i.e, já tiverem uma entrada na tabela de emulacao)
  * 
  */

  /* 2) Como a tabela de comutação deve ser implementada neste trabalho de forma 
   *    que um host destino que tenha entrada na tabela não force o comutador a redirecionar broadcast, 
   *    ou seja, para o endereço 255?
   *
   *    A tabela de comutaçao será preenchida a medida que os hosts trocarem pacotes entre si (como vimos na aula). 
   *    Se um host  chamou  L_Activate_Request  (está na tabela de emulacao) mas ainda nao enviou nenhum frame, 
   *    a tabela de comutacao ainda nao terá a entrada desse host, e, portanto, um frame destinado a ele 
   *    sera redirecionado em broadcast pelo comutador.
   */
