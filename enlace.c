/*
 * Arquivo onde e feita a implementacao das funcoes da camada de enlace
 *
 * Componentes: Felipe Almeida Tavares
 *              Leandro Lima Monteiro Coelho
 *		Rafael de Oliveira Costa
 */

#include "enlace.h"
#include "comutador.h"
#include "fisica.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned char broadcast=255; //endereco de broadcast
unsigned char my_mac=0; //endereco MAC do host que executar o software de enlace

struct buffer_enlace l_buffer;

int L_Activate_Request(unsigned char mac, int switch_port, char *switch_addr){

	//Verificar se my_mac já foi gerado. Se sim quer dizer que a funcao L_Activate_Request já foi inicializada*/
	if(my_mac!=0){
		printf("--Failed my_mac ja foi gerado\n");
		return 0;
	}
	my_mac=mac;

	//inicializando a camada física	
	if(!P_Activate_Request(SWITCH_PORT, SWITCH_ADDR)){
		printf("--Failed P_Activate_Request\n");
		return 0;
	}
 	
	return 1;
}

void L_Data_Request(unsigned char mac_dest, char *payload, int bytes_to_send){

	sprintf(buffer, "%d|0|%d|%s|0", mac, SWITCH_PORT, payload);

	printf("entrou L_Data_Request\n");
/*Teste para ver que as informações estão chegando corretas:*/
	int mac;
	mac=(int)mac_dest;
	printf("mac: %d\n",mac);
	printf("payload: %s\n",payload);
	printf("bytes enviados: %d\n",bytes_to_send);

}

int L_Data_Indication(){
	if (P_Data_Indication() && P_Data_Receive() == '$') return 0; // nenhum frame
	return 0; // frame recebido
}

int L_Data_Receive(unsigned char *mac_source, char *frame_recv, int max_frame){
return 0;

}

void L_MainLoop(){
}

void L_Set_Loss_Probability(float percent_lost_frame){
}

void L_Deactivate_Request(void){
}

void l_Recebe_Byte(void) {
}

void l_Valida_Quadro(void) {
}

void l_Transmite_Byte(void) {
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
