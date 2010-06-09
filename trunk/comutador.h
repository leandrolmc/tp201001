/*
 * Arquivo que contem as definicoes de estruturas de dados e das assinaturas das
 * funcoes publicas do comutador
 *
 * Componentes: Felipe Almeida Tavares
 *              Leandro Lima Monteiro Coelho
 *		Rafael de Oliveira Costa
 */


/* Efetua a inicializacao do comutador 
 * Retorna 1 em caso de sucesso e 0 em caso de falha
 */
int start_switch();

/* Efetua as operacoes necessarias ao plugar um host no comutador 
 * Retorna 1 em caso de sucesso e 0 em caso de falha
 */
int plug_host(unsigned char mac, int my_port, char *my_addr,int switch_port,char *switch_addr);

/* Gera uma porta aleatoria para o comutador de acordo com o numero de enlaces do comutador
 * verifica se essa porta já esta sendo usada e caso afirmativo escolhe outra 
 * Retorna a porta do comutador em caso de sucesso e 0 em caso de falha
 */
int generate_switch_port();
