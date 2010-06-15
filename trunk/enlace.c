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

unsigned char broadcast=255; //endereco de broadcast
unsigned char my_mac=0; //endereco MAC do host que executar o software de enlace

// buffers de entrada e de saida da camada de enlace
struct buffer_enlace buf_in; 
struct buffer_enlace buf_out; 

int frames_buffered = 0;

/* Efetua as inicializacoes do nivel de enlace (recebe o endereco local da maquina) e inicializa o nivel  
 * fisico (recebe a especificacao da porta que sera usada para a comunicacao e o endereco IP do comutador de enlace)
 * Faz o bind para a porta escolhida e faz as inicializacoes necessarias para a camada de enlace
 * Retorna 1 em caso de sucesso e 0 em caso de falha
 */
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

/* Solicita a transmissao de um quadro
 * Recebe o endereco MAC de destino, os dados a serem transmitidos e o numero de bytes
 */      
void L_Data_Request(unsigned char mac_dest, char *payload, int bytes_to_send){

	char *buffer;

	//Formando os Frames para serem transmitidos
	if(mac_dest!=0){
		//Frame normal: MACORIGEM|MACDESTINO|DADOS|TAMANHODOSDADOS|CODIGOERRO$
		//TODO fazer codigo de erro
		sprintf(buffer, "%d|%c|%s|%d|0$",my_mac, mac_dest, payload,strlen(payload));
	}
	else{
		//Frame especial:  MACORIGEM|000|ENDERECOHOST|PORTA|000$
		sprintf(buffer, "%d|%c|%s|%d|0",my_mac, mac_dest, payload,SWITCH_PORT);
	}	

/*	Teste para ver que as informações estão chegando corretas:*/
/*	int mac;*/
/*	mac=(int)mac_dest;*/
/*	printf("mac: %d\n",mac);*/
/*	printf("payload: %s\n",payload);*/
/*	printf("bytes enviados: %d\n",bytes_to_send);*/

}

/* Testa se ha um quadro recebido no nivel de enlace
 * Retorna 1 caso exista e 0 caso contrario
 */
int L_Data_Indication(){
	if (buf_in.qtd_disponivel > 0 ) return 1;
	return 0;
}

/* Busca no nivel de enlace os dados do ultimo quadro recebido
 * Recebe ponteiros para variaveis que irao conter
 * respectivamente, o endereco da estacao que enviou o quadro 
 * e os dados do quadro recebido
 * O ultimo parametro e o tamanho maximo esperado para o 
 * campo de dados do quadro
 * Retorna o numero de bytes do campo de dados ou −1 no caso
 * de falha (numero de bytes do quadro maior que o tamanho 
 * maximo esperado)
 */     
int L_Data_Receive(unsigned char *mac_source, char *frame_recv, int max_frame){
return 0;

}

/* Executa um ciclo de tarefas da camada de enlace e retorna
 * Deve transmitir um byte para o nivel fısico, caso a estacao
 * possua um quadro para transmitir
 * Deve verificar se ha ́um byte para receber no nivel fisico e,
 * caso exista, receber esse byte
 */
void L_MainLoop(){
}

/* Configura a taxa de perda de quadros da camada de enlace
 * Recebe o valor percentual de perda de quadros
 */
void L_Set_Loss_Probability(float percent_lost_frame){
}

// Finaliza o funcionamento do nivel de enlace e do nivel fısico
void L_Deactivate_Request(void){
}

/* Recebe um byte e armazena no buffer da camada de enlace,
 * quando o ultimo byte de um quadro e recebido ele deve ser validado
 */
void l_Recebe_Byte(void) {
	if (P_Data_Indication()) {
		char c = P_Data_Receive();
		buf_in.pos_atual = buf_in.pos_atual + 1;
		if (c == '$') {
			buf_in.buf[buf_in.pos_atual] = '\0';		
			return;
		} 
		buf_in.buf[buf_in.pos_atual] = c;
		// Vamos ter que ir pegando byte a byte ate montar o quadro ate chegar a $ (final do quadro)
		// concatenação de string
	}
}

/* Valida um quadro recebido, apenas mantem um quadro no buffer de recepcao se for
 * destinado a maquina local ou broadcast, e passar na
 * checagem de erro (usar probabilidade randomica de erro para
 * “forcar” a ocorrencia de erros)
 */
void l_Valida_Quadro(void) {
}

// Transmite um byte do quadro e checa se terminou a transmissao do quadro 
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
