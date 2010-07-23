/*
 * Arquivo que contem as definicoes de estruturas de dados e das assinaturas das
 * funcoes publicas do roteador
 *
 * Componentes: Felipe Almeida Tavares
 *              Leandro Lima Monteiro Coelho
 *					 Rafael de Oliveira Costa
 */

#define ROUTER_BORDER_PORT	5000

#define BACKBONE_IP				"127.0.0.1"
#define BACKBONE_PORT 			8000

#define DATAGRAMA_SIZE 		1024

/* Efetua a inicializacao do roteador de borda
 * Retorna 1 em caso de sucesso e 0 em caso de falha
 */
int start_router(char *,int,char *,char *);

int link_to_backbone();

