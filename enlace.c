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
	 * Esse endereço ficará armazenado como variável global e poderá ser acessado pelo proprio 
	 * host a qualquer tempo
	 */
	my_mac=mac;

	//Gerando uma porta para que o comutador possa contactar o host
	int   my_port;  
	srand ( time(NULL) );
	while((my_port = rand() % 9999)<1000);

	//Obtendo o endereco IP do host para que o comutador possa contactar o host
	//TODO my_addr = ??? 
	char *my_addr = "192.168.1.103";	

	if(!plug_host(my_mac, my_port, my_addr, switch_port, switch_addr)){
		printf("--Failed plug_host\n");
	}
}

/* Solicita a transmissao de um quadro
 * Recebe o endereco MAC de destino, os dados a serem transmitidos e o numero de bytes
 */                        

void L_Data_Request(unsigned char mac_dest, char *payload, int bytes_to_send){

/*	int mac;*/
/*	mac=(int)mac_dest; */

/*	printf("%d\n",mac);*/
/*	puts(payload);*/
/*	printf("%d\n",bytes_to_send);*/

}

/* Neste trabalho, o host emissor terá que enviar o quadro para o comutador e este comutador terá que redirecionar o
   quadro para o host destino cujo endereço MAC está contido no frame enviado pelo host emissor.

   O MAC fonte (host local), a porta e o IP do comutador serão definidos na inicializaçao da camada de enlace
   (L_Activate_Request) e permanecerão válidos durante toda a execução. 
   O MAC destino deverá ser informado a cada chamada da funçao L_Data_Request

   O quadro conterá os endereços MAC fonte e destino, mas apenas o MAC destino precisará ser informado 
   pela camada superior (nesse trabalho pelo programa de teste).

   Quando o comutador recebe o quadro do host fonte, ele não tem nada na sua tabela de comutação 
   inicialmente e usa o endereço broadcast 255 para enviar esse quadro para todos os hosts.
*/

void L_Deactivate_Request(void){
	if(!unplug_host(my_mac)){
		printf("--Failed unplug_host\n");
	}
}

