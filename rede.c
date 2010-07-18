/*
 * Arquivo onde e feita a implementacao das funcoes da camada de rede
 *
 * Componentes: Felipe Almeida Tavares
 *              Leandro Lima Monteiro Coelho
 *					 Rafael de Oliveira Costa
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rede.h"

#include "enlace.h"
#include "fisica.h"



char *ip_roteadorsubrede;
char *meu_ip;

/* Efetua as inicializacoes do nivel de rede (recebe o endereco IP do roteador de borda
 * da subrede e o endereco IP do proprio host) e inicializa o niveis de enlace (recebe o endereco MAC da maquina) 
 * e fisico (recebe a especificacao da porta que ser ́usada para a comunicacao e o endereco IP do comutador 
 * de enlace);
 * Faz as inicializacoes necessarias para as camadas fisica e de enlace e para a camada de rede;
 * Retorna 1 em caso de sucesso e 0 em caso de falha.
 */
// parametros: ip do roteador de borda, ip do host, mac do host, porta do comutador, ip do comutador
int N_Activate_Request (char *ip_roteadorborda, char *ip_host, unsigned char mac_host, int porta_comutador, char *ip_comutador) {

	float percent_lost_frame;
	
	ip_roteadorsubrede = ip_roteadorborda;
	meu_ip = ip_host;
	
	if (!L_Activate_Request(mac_host, porta_comutador, ip_comutador)) {
		return 0;	
	}

	// Temporario
	//Inicializa o valor da variavel taxa_perda_quadros
	printf("Porcentagem de Frames Perdidos ? (valor entre 0 e 100)\n");
	scanf("%f",&percent_lost_frame);
	N_Set_Loss_Probability(percent_lost_frame);

	return 1;
}


/* Solicita a transmissao de um datagrama;
 * Recebe a identificacao do protocolo que esta solicitando o envio do datagrama, o endereco IP de destino, 
 * os dados a serem transmitidos e o numero de bytes
 * Usa o protocolo ARP para encontrar o MAC correspondente ao IP destino
 * (caso o datagrama seja destinado a um host em outra subrede, deve enviar para o roteador de borda)
 *
 */
//parametros: identificacao do protocolo, ip_destino, dados, numero de bytes
void N_Data_Request (unsigned char protocolo, char *ip_dest, char *dados, int num_bytes) {

}


/* Testa se ha um datagrama recebido no nivel de rede
 * Recebe como parametro a identificacao do protocolo da camada solicitante
 * Retorna 1 caso exista e 0 caso contrario.
 */
int N_Data_Indication (unsigned char protocolo) {

	return 0;
}


/* Busca no nivel de rede os dados do ultimo datagrama recebido;
 * O primeiro parametro e a identificacao do protocolo que esta recebendo o datagrama
 * O segundo e terceiro parametros sao ponteiros para variaveis que irao conter, respectivamente, 
 * o endereco IP da maquina que enviou o datagrama e os dados do datagrama recebido;
 * O ultimo parametro e o tamanho maximo esperado para o campo de dados do datagrama;
 * Retorna o numero de bytes do campo de dados ou −1 no caso de falha 
 * (numero de bytes do datagrama maior que o tamanho maximo esperado).
 */
// parametros: protocolo, ip fonte (ponteiro), dados (ponteiro), tamanho maximo esperado
int N_Data_Receive (unsigned char protocolo, char *ip_fonte, char *dados, int tam_maximo) {

	return 0;
}


/* 
 * Configura a taxa de perda de quadros da camada de enlace
 * Recebe o valor percentual de perda de quadros e chama a funcao L_Set_Loss_Probability.
 */
void N_Set_Loss_Probability (float percent_lost_frame) {

	//L_Set_Loss_Probability(percent_lost_frame/100);

}


/* 
 * Finaliza o funcionamento dos niveis de rede, enlace e fisico.
 */
void N_Deactivate_Request(void) {

	//N_Deactivate_Request();

}
