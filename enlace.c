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

//Buffers para armazenar os quadros a serem transmitidos e quadros recebidos

struct buffer_env{
	//char frame[FRAME_SIZE];
	char *frame;
	int empty;
};

struct buffer_recv{
	//char frame[FRAME_SIZE];
	char *frame;
	int empty;
};

struct buffer_env buffer_env[2];
struct buffer_recv buffer_recv[2];

//Frame Temporario usado para l_Recebe_Bytes
char frame_temp[FRAME_SIZE];	

void dec2bin(int decimal, char *binary){
	int k = 0, n = 0;
	int neg_flag = 0;
	int remain;
	int old_decimal;
	char temp[80];

	// Verifica os negativos
	if (decimal < 0){
		decimal = -decimal;
		neg_flag = 1;
	}

	do{
		old_decimal = decimal;
		remain = decimal % 2;
		decimal = decimal / 2;

		// convertendo os digitos 0 ou 1 para os caracteres '0' ou '1'
		temp[k++] = remain + '0';
	} while (decimal > 0);

	// revertendo a ordem
	while (k >= 0)
		binary[n++] = temp[--k];
		
	binary[n-1] = 0;
}

int generate_code_error(char *buffer)
{
	int tam_buffer=strlen(buffer);
	int soma=0;
	int paridade=0;
	int i;	
	char binary[80];
	
	memset(&binary, 0, sizeof(binary));
	for(i=0;i<tam_buffer;i++){
		soma+=(int)buffer[i];
	}

	dec2bin(soma,binary);
	for(i=0;i<strlen(binary);i++){	
		if(binary[i]=='1'){
			if(paridade!=0){
				paridade=0;
			}	
			else{
				paridade=1;
			}
		}
		
	}
	return paridade;
}


int L_Activate_Request(unsigned char mac, int switch_port, char *host_addr){

	//Verificar se my_mac já foi gerado. Se sim quer dizer que a funcao L_Activate_Request já foi inicializada*/
	if(my_mac!=0){
		printf("--Failed my_mac ja foi gerado\n");
		return 0;
	}

	//Inicializando os buffers de envio e recebimento

	buffer_env[0].frame = (char*) malloc(FRAME_SIZE);
	buffer_env[1].frame = (char*) malloc(FRAME_SIZE);
	buffer_recv[0].frame = (char*) malloc(FRAME_SIZE);
	buffer_recv[1].frame = (char*) malloc(FRAME_SIZE);

	buffer_env[0].empty=1;
	buffer_env[1].empty=1;
	buffer_recv[0].empty=1;
	buffer_recv[1].empty=1;

	my_mac=mac;

	return 1;
}

void L_Data_Request(unsigned char mac_dest, char *payload, int bytes_to_send){

	char buffer[BUFFER_SIZE];

	memset(&buffer, 0, sizeof(buffer));
	sprintf(buffer, "%d|%d|%s|%d", (int)my_mac,(int)mac_dest, payload,strlen(payload));
	sprintf(buffer, "%s|%d", buffer,generate_code_error(buffer));

	if(buffer_env[0].empty==1){
		buffer_env[0].frame=buffer;
		buffer_env[0].empty=0;
	}
	else{
		buffer_env[1].frame=buffer;
		buffer_env[1].empty=0;
	}
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
	//srand(time(NULL));
	//mac = (rand()%255);
}

void L_Deactivate_Request(void){
}

void l_Recebe_Byte(void) {
	
	int i=0;

	memset(&frame_temp, 0, FRAME_SIZE);

	while(P_Data_Indication()) {
		frame_temp[i]=P_Data_Receive();
		i++;
	}
	l_Valida_Quadro();
	puts(frame_temp);
}

void l_Valida_Quadro(void) {

}

void l_Transmite_Byte(void) {
	int i;
	if(!buffer_env[0].empty){
		for(i=0;i<strlen(buffer_env[0].frame);i++){
			P_Data_Request(buffer_env[0].frame[i]);
		}
		buffer_env[0].empty=1;
	}
	else if(!buffer_env[1].empty){
		for(i=0;i<strlen(buffer_env[0].frame);i++){
			P_Data_Request(buffer_env[0].frame[i]);
		}
		buffer_env[1].empty=1;
	}
	else{
		printf("--Failed Nao ha bytes a serem enviados\n");
	}
}
