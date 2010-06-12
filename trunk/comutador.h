/*
 * Arquivo que contem as definicoes de estruturas de dados e das assinaturas das
 * funcoes publicas do comutador
 *
 * Componentes: Felipe Almeida Tavares
 *              Leandro Lima Monteiro Coelho
 *		Rafael de Oliveira Costa
 */


#define BUFFER_SIZE	128
#define NUMBER_OF_PORTS 32

//A porta do comutador deve ser padrao e todos os hosts devem ter conhecimento disso.
#define SWITCH_PORT 	5000


/* Efetua a inicializacao do comutador 
 * Retorna 1 em caso de sucesso e 0 em caso de falha
 */
int start_switch();

/* Efetua as operacoes necessarias ao plugar um host no comutador 
 * Retorna 1 em caso de sucesso e 0 em caso de falha
 */
int plug_host(unsigned char ,int , char * ,int ,char *);

/* Efetua as operacoes necessarias ao desplugar um host no comutador 
 * Retorna 1 em caso de sucesso e 0 em caso de falha
 */
int unplug_host(unsigned char);

/* Gera uma porta aleatoria para o comutador de acordo com o numero de enlaces do comutador
 * verifica se essa porta já esta sendo usada e caso afirmativo escolhe outra 
 * Retorna a porta do comutador em caso de sucesso e 0 em caso de falha
 */
int generate_switch_port();
