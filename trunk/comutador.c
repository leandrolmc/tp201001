/*
 * Arquivo onde e feita a implementacao das funcoes do comutador
 *
 * Componentes: Felipe Almeida Tavares
 *              Leandro Lima Monteiro Coelho
 *		Rafael de Oliveira Costa
 */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h> 
#include <stdlib.h>

#define BUFFERSIZE	1024
#define NUMBER_OF_PORTS 32

//Estrutura que representa a tabela de emulacao das conexoes fisicas com o comutador
struct table_phy {
	unsigned char mac;
	int port;
	char *address;
	int port_switch;
};

//Estrutura que representa a tabela de funcionamento normal do comutador
struct table_switch {
	unsigned char mac;
	//Essa porta do switch descreve o socket(endereco IP, porta) do host ao qual se quer conectar
	int port_switch;
};

int plug_host(mac, my_port, my_addr, switch_port, switch_addr){

	//implementar cliente udp


	return 1;
}

int start_switch(){

	int sockfd;
	struct sockaddr_in local_addr; 
	char buffer[BUFFERSIZE];
	ssize_t recsize;
	socklen_t fromlen;

	//A porta do comutador deve ser padrao e todos os hosts devem ter conhecimento disso.
       int port = 5000;

	//O endereco do comutador deve ser padrao (nesse caso, 127.0.0.1) e todos os hosts devem ter conhecimento disso.
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
	local_addr.sin_port = htons(port);

	// associa o descritor de socket com o endereco local
	if (bind(sockfd,(struct sockaddr *)&local_addr, sizeof(struct sockaddr)) < 0) {
		printf("--Exit com erro no bind \n");
		close(sockfd);
		exit(0);
	} 

	//Inicializando as tabelas do comutador

	struct table_phy table_phy[NUMBER_OF_PORTS];
	memset(&table_phy, 0, sizeof(table_phy));

	struct table_switch table_switch[NUMBER_OF_PORTS];
	memset(&table_switch, 0, sizeof(table_switch));


	// loop principal do servidor
	for (;;)  {
		memset(buffer, 0, sizeof(buffer));
		printf ("esperando mensagens....\n");
		recsize = recvfrom(sockfd, (void *) buffer, BUFFERSIZE, 0, (struct sockaddr *)&local_addr, &fromlen);
		if (recsize < 0) {
			printf("--Erro no recebimento \n");
		}
		printf("mensagem recebida: %s (%d bytes)\n",buffer,recsize);
	}

	


        return 1;
}

 //Abaixo estao informacoes tiradas da lista de tp com as respostas da Silvana

 /* 1)Como fazer com que esse endereço 255 seja para todos os hosts conectados ao comutador 
  *   quando este não possui nenhuma entrada na tabela?
  *
  * Voce deverá manter duas tabelas distintas: uma responsavel pela emulacao das conexoes fisicas 
  * entre hosts e o comutador; e outra responsavel pela operacao normal de um comutador de enlace 
  * (da forma como vimos na aula). 
  *
  * A primeira tabela é preenchida quando os hosts chamam a funcao L_Activate_Request e contactam o comutador 
  * pela primeira vez (use um formato de mensagem diferenciado para essa primeira comunicaçao). 
  * A partir daí a emulacao estará pronta (como se voce tivesse plugado fisicamente um host a uma porta de entrada 
  * do comutador). Para cada host plugado ao comutador, deverá ser guardado na tabela de emulacao o IP desse host 
  * e a porta para a qual ele fez o bind para que o comutador tenha as informacoes necessarias para redirecionar 
  * os pacotes destinados a esse host no futuro. Cada entrada na tabela passará a funcionar como a identificaçao 
  * de uma porta ativa do comutador.
  *
  * A segunda tabela deverá ser preenchida seguindo a operacao normal de um comutador de enlace. Uma mensagem broadcast 
  * do comutador só atingirá os hosts que já tiverem chamado L_Activate_Request (i.e, já tiverem uma entrada na tabela 
  * de emulacao).
  * 
  */


  /* 2) Como a tabela de comutação deve ser implementada neste trabalho de forma que um host destino que tenha entrada 
   *    na tabela não force o comutador a redirecionar broadcast, ou seja, para o endereço 255?
   *
   *    A tabela de comutaçao será preenchida a medida que os hosts trocarem pacotes entre si (como vimos na aula). 
   *    Se um host  chamou  L_Activate_Request  (está na tabela de emulacao) mas ainda nao enviou nenhum frame, a tabela
   *    de comutacao ainda nao terá a entrada desse host, e, portanto, um frame destinado a ele sera redirecionado 
   *    em broadcast pelo comutador.
   */

  /*  Os hosts deverao informar seu IP e porta no primeiro contato com o comutador para preenchimento da tab. de emulacao.
   *  Apenas os hosts que fizerem esse primeiro contato estarao ativos para broadcast
   */ 

