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
#include <limits.h>
#include <string.h>

unsigned char my_mac;

struct buffer_enlace buffer_enlace;

int generate_code_error(char *buffer)
{
//	int temp;
//	unsigned char bit;
	//char *cod_bin;

//	temp=atoi(buffer);
	//cod_bin = (char *) malloc (CHAR_BIT*sizeof(temp)+1);

//	for ( bit = 1 << (CHAR_BIT - 1); bit; bit >>= 1 )
  // {
    //  *dst++ = value & bit ? '1' : '0';
   //}
   //*dst = '\0';
	
   return 0;
}

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

	char buffer[BUFFER_SIZE];
	int cod_erro;

	memset(&buffer, 0, sizeof(buffer));
	sprintf(buffer, "%d|%d|%s|%d", (int)my_mac,(int)mac_dest, payload,strlen(payload));
	cod_erro=generate_code_error(buffer);	
	sprintf(buffer, "%s|%d", buffer,cod_erro);

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


