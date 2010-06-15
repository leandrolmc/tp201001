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
#include <string.h>

unsigned char my_mac;

int L_Activate_Request(unsigned char mac, int switch_port, char *host_addr){

	//Verificar se my_mac já foi gerado. Se sim quer dizer que a funcao L_Activate_Request já foi inicializada*/
	if(my_mac!=0){
		printf("--Failed my_mac ja foi gerado\n");
		return 0;
	}
	my_mac=mac;

	return 1;
}

void L_Data_Request(unsigned char mac_dest, char *payload, int bytes_to_send){
}

int L_Data_Indication(){
	return 0;
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
