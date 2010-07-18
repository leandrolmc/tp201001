/*
 * Arquivo que contem as definicoes de estruturas de dados e das assinaturas das
 * funcoes publicas do backbone
 *
 * Componentes: Felipe Almeida Tavares
 *              Leandro Lima Monteiro Coelho
 *					 Rafael de Oliveira Costa
 */


#define TABLE_LENGTH 	16
#define BACKBONE_PORT 			5000
#define BUFFER_SIZE				1024


/* Efetua a inicializacao do backbone
 * Retorna 1 em caso de sucesso e 0 em caso de falha
 */
int start_switch();

void init();

/* Adiciona uma rota na tabela de redirecionamento do backbone
 * Retorna 1 em caso de sucesso e 0 em caso de falha
 */
int route_add(int, char *,char *);

/* Remove uma rota na tabela de redirecionamento do backbone
 * Retorna 1 em caso de sucesso e 0 em caso de falha
 */
int route_del(char *,char *);

// Exibe uma lista com todas as entradas da tabela de redirecionamento que estão ocupadas
void list_table();
