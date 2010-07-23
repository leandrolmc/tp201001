/*
 * Arquivo que contem as definicoes de estruturas de dados e das assinaturas das
 * funcoes publicas da camada fisica
 *
 * Componentes: Felipe Almeida Tavares
 *              Leandro Lima Monteiro Coelho
 *		Rafael de Oliveira Costa
 */

/* Efetua as inicializacoes necessarias da camada fisica, recebe a especiﬁcacao
 * da porta que sera usada para a comunicacao e do endereco da maquina 
 * remota, retorna 1 em caso de sucesso e 0 em caso de falha
 */
int P_Activate_Request(int, char *);

// Solicita a transmissao de 1 byte e recebe o byte a ser transmitido
void P_Data_Request(char);

/* Testa se ha um byte recebido na camada fisica, 
 * retorna 1 caso exista um byte recebido na camada fisica
 */
int P_Data_Indication(void);

// Busca na camada fisica o ultimo byte recebido e retorna o byte recebido
char P_Data_Receive(void);

// Encerra o canal de comunicacao estabelecido
void P_Deactivate_Request(void);

void fisica_definirIPreal(char * ip);
