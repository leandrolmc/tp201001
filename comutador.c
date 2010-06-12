/*
 * Arquivo onde e feita a implementacao das funcoes do comutador
 *
 * Componentes: Felipe Almeida Tavares
 *              Leandro Lima Monteiro Coelho
 *		Rafael de Oliveira Costa
 */

#include "fisica.h"
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
	int port_switch; //socket descriptor?
	char *mac;
	int port;
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

	P_Activate_Request(SWITCH_PORT, NULL);

	//Inicializando as tabelas do comutador
	memset(&table_phy, 0, sizeof(table_phy));
	memset(&table_switch, 0, sizeof(table_switch));

	// loop principal do servidor
	for (;;)  {
		memset(buffer, 0, sizeof(buffer));
		printf ("esperando mensagens....\n");

		while(P_Data_Indication()) {
			char c = P_Data_Receive()
			printf("O Byte recebido foi %c\n", c);
			if (c == "$") break;
			// Vamos ter que ir pegando byte a byte ate montar o quadro ate chegar a $ (final do quadro)
			// concatenação de string
		}


		printf("mensagem recebida: %s (%d bytes)\n",buffer,recsize);

		mac_dest = strtok (buffer, "|");
		mac_source = strtok (NULL,"|");
		data_length = strtok (NULL, "|");
		data = strtok (NULL, "|");
		error_code = strtok (NULL, "|");

		//Verifica se o FRAME e especial.
		//Se for um frame especial significa que o frame veio da funcao plug_host() e portanto
		//devemos colocar as informacoes na tabela de emulacao das conexoes fisicas
		if(!strcmp(mac_dest,"0"))
		{
			port_switch=generate_switch_port();
			table_phy[port_switch].port_switch=port_switch;
			table_phy[port_switch].mac=mac_source;
			//No frame especial utilizo o campo data-length para guardar a porta do host
			table_phy[port_switch].port=atoi(data_length);
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
		port = (rand() % NUMBER_OF_PORTS);		
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
