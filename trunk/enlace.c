/*
 * Arquivo onde e feita a implementacao das funcoes da camada de enlace
 *
 * Componentes: Felipe Almeida Tavares
 *              Leandro Lima Monteiro Coelho
 *		Rafael de Oliveira Costa
 */

#include "comutador.h"
#include "enlace.h"
#include "fisica.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <arpa/inet.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h> 

char ipreal[15];


unsigned char my_mac=0;

//Buffers para armazenar os quadros a serem transmitidos e quadros recebidos

struct buffer_env{
	char frame[FRAME_SIZE];
	int empty;
	int position;
};

struct buffer_recv{
	char frame[FRAME_SIZE];
	int empty;
	int position;
};

//struct buffer_temp{
//	char frame[FRAME_SIZE];
//	int full;
//	int position;
//};

struct buffer_env buffer_env[2];
struct buffer_recv buffer_recv[2];
//struct buffer_temp buffer_temp;//Frame Temporario usado para l_Recebe_Bytes

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

void plug_host(int switch_port, char *host_addr) {



	int phy_sd; // descritor do socket

	struct sockaddr_in local_addr; // informacoes de endereco local
	struct sockaddr_in remote_addr; // informacoes de endereco remoto

	char buffer_send[FRAME_SIZE]; //buffer onde os bytes enviados serão armazenados

	// criando o socket
        if ((phy_sd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
           printf("--Erro na criacao do socket\n");
           exit(-1);
        }

	// Definindo informações do endereco local
	memset(&local_addr, 0, sizeof(local_addr));
	local_addr.sin_family = AF_INET;
	local_addr.sin_addr.s_addr = inet_addr(ipreal);
	local_addr.sin_port = htons(SWITCH_PORT);
	memset(local_addr.sin_zero, 0, sizeof(local_addr.sin_zero));

	// associando a porta a maquina local
        if (bind(phy_sd,(struct sockaddr *)&local_addr, sizeof(struct sockaddr)) < 0) {
           printf("--Exit com erro no bind \n");
           close(phy_sd);
           exit(-1);
        } 

	memset(&remote_addr, 0, sizeof(remote_addr));
	if (host_addr != NULL) {
		// Definindo informações do endereco remoto
		remote_addr.sin_family = AF_INET;
		remote_addr.sin_addr.s_addr = inet_addr(host_addr);
		remote_addr.sin_port = htons(SWITCH_PORT);
	}

	//frame especial
	sprintf(buffer_send, "%s|%d|%d", inet_ntoa(local_addr.sin_addr), switch_port, my_mac);

	if ((sendto(phy_sd, buffer_send, strlen(buffer_send), 0, (struct sockaddr*)&remote_addr, sizeof (struct sockaddr_in))) < 0) {
		printf("--Erro na transmissão\n");
		close(phy_sd);
	}
	else {
		printf("-- Dados transmitidos com sucesso.\n");
	   close(phy_sd);
	}

}


int L_Activate_Request(unsigned char mac, int switch_port, char *host_addr){

	//Verificar se my_mac já foi gerado. Se sim quer dizer que a funcao L_Activate_Request já foi inicializada*/
	if(my_mac!=0){
		printf("--Failed my_mac ja foi gerado\n");
		return 0;
	}

	my_mac=mac;

	plug_host(switch_port, host_addr);

	P_Activate_Request(switch_port, host_addr);

	//Inicializando os buffers de envio e recebimento
	memset(&buffer_env[0].frame, 0, FRAME_SIZE);
	memset(&buffer_env[1].frame, 0, FRAME_SIZE);
	memset(&buffer_recv[0].frame, 0, FRAME_SIZE);
	memset(&buffer_recv[1].frame, 0, FRAME_SIZE);

	buffer_env[0].empty=1;
	buffer_env[1].empty=1;
	buffer_recv[0].empty=1;
	buffer_recv[1].empty=1;

	buffer_env[0].position=0;
	buffer_env[1].position=0;
	buffer_recv[0].position=0;
	buffer_recv[1].position=0;

	//Inicializando o buffer temporario
	//memset(&buffer_temp.frame, 0, FRAME_SIZE);
	//buffer_temp.full=0;
	//buffer_temp.position=0;

	return 1;
}

void L_Data_Request(unsigned char mac_dest, char *payload, int bytes_to_send){

	char buffer[FRAME_SIZE];

	sprintf(buffer, "%d|%d|%s|%d", (int)my_mac,(int)mac_dest, payload,strlen(payload));
	sprintf(buffer, "%s|%d$", buffer,generate_code_error(buffer));

	printf("Camada de enlace pronta para enviar o frame: %s\n", buffer);

	if(buffer_env[0].empty==1){
		//buffer_env[0].frame=buffer;
		strcpy (buffer_env[0].frame,buffer);
		buffer_env[0].empty=0;
		buffer_env[0].position=0;
	}
	else{
		//buffer_env[1].frame=buffer;
		strcpy (buffer_env[1].frame,buffer);
		buffer_env[1].empty=0;
		buffer_env[0].position=0;
	}
}

int L_Data_Indication(){
	if(!buffer_recv[1].empty){
		return 1;
	}
	return 0;
}

int L_Data_Receive(unsigned char *mac_source, char *frame_recv, int max_frame){
	*mac_source = 24;
	frame_recv = "wololo!";

	return 0;
}

void L_MainLoop(){
	l_Transmite_Byte();
	l_Recebe_Byte();
}

void L_Set_Loss_Probability(float percent_lost_frame){
}

void L_Deactivate_Request(void){
}

void l_Recebe_Byte(void) {

/*
	buffer_recv[1] = Buffer para frame recebido e validado. Pode ser sobrescrito por outro frame recebido e validado
	buffer_recv[0] = Buffer para o recebimento dos bytes.
*/
		
	char ch_recv;

	if(my_mac==0){
		return;
	}
	else{
		if(P_Data_Indication()){
			ch_recv=P_Data_Receive();
			if(buffer_recv[0].empty){
				buffer_recv[0].frame[buffer_recv[0].position]=ch_recv;
				buffer_recv[0].position++;
				printf("-- Byte \'%c\'recebido com sucesso\n", ch_recv);
				if (ch_recv == '$') {
					buffer_recv[0].empty=0;
					l_Valida_Quadro();//obs se nao for valido fazer buffer_recv[0].empty=1;
					printf("-- Frame completamente recebido.\n");
					printf("-- Frame recebido na camada de enlace: %s\n", buffer_recv[0].frame);
				}
				
			}
		}
	}
}

void l_Valida_Quadro(void) {
	// Implementar validação!
	// soh vai para o buffer 1 se for valido!
	strcpy(buffer_recv[1].frame, buffer_recv[0].frame);
	buffer_recv[1].empty = 0;

	memset(&buffer_recv[0].frame, 0, sizeof(buffer_recv[0].frame));
	buffer_recv[0].empty = 1;
	buffer_recv[0].position=0;
}

void l_Transmite_Byte(void) {
	if(my_mac==0){
		return;
	}
	else{
		if(!buffer_env[0].empty){
			P_Data_Request(buffer_env[0].frame[buffer_env[0].position]);
			buffer_env[0].position++;

			if( buffer_env[0].position == strlen(buffer_env[0].frame) ){		
				buffer_env[0].empty=1;
				buffer_env[0].position=0;
				memset(&buffer_env[0], 0, sizeof(buffer_env[0].frame));
			}
		}
		else if(!buffer_env[1].empty){
			P_Data_Request(buffer_env[1].frame[buffer_env[1].position]);
			buffer_env[1].position++;

			if( buffer_env[1].position == strlen(buffer_env[1].frame) ){
				buffer_env[1].empty=1;
				buffer_env[0].position=0;
				memset(&buffer_env[0], 0, sizeof(buffer_env[0].frame));
			}
		}
	}
	return;		
}

/* ** funcao auxiliar ** */
void definirIPreal(char * ip) {
	strcpy(ipreal, ip);

}
