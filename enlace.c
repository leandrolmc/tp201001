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
#include <stdlib.h>
#include <time.h>

unsigned char broadcast=255; //endereco de broadcast
unsigned char my_mac=0; //endereco MAC do host que executar o software de enlace

int L_Activate_Request(unsigned char mac, int switch_port, char *switch_addr){

	/* Cada host irá iniciar o software da camada de enlace definindo o endereço MAC que irá usar. 
	 * Esse endereço ficará armazenado como variável global e poderá ser acessado pelo proprio 
	 * host a qualquer tempo
	 */

	//Verificar se my_mac já foi gerado. Se sim quer dizer que a funcao L_Activate_Request já foi inicializada
	if(my_mac!=0){
		printf("--Failed my_mac ja foi gerado\n");
		return 0;
	}
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

	return 1;
}

void L_Data_Request(unsigned char mac_dest, char *payload, int bytes_to_send){

/*Teste para ver que as informações estão chegando corretas:*/
/*	int mac;*/
/*	mac=(int)mac_dest; */
/*	printf("%d\n",mac);*/
/*	puts(payload);*/
/*	printf("%d\n",bytes_to_send);*/

}

int L_Data_Indication(){
	return 1;
}

int L_Data_Receive(unsigned char *mac_source, char *frame_recv, int max_frame){
	return 1;
}

void L_MainLoop(){
}

void L_Set_Loss_Probability(float percent_lost_frame){
}

void L_Deactivate_Request(void){
	//TODO ver função unplug_host
	//printf("my_mac %d\n",atoi(my_mac));
	if(!unplug_host(my_mac)){
		printf("--Failed unplug_host\n");
	}
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
