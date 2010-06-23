/*
 * Arquivo que contem as definicoes de estruturas de dados e das assinaturas das
 * funcoes publicas da camada de rede
 *
 * Componentes: Felipe Almeida Tavares
 *              Leandro Lima Monteiro Coelho
 *					 Rafael de Oliveira Costa
 */


/* Efetua as inicializacoes do nivel de rede (recebe o endereco IP do roteador de borda
 * da subrede e o endereco IP do proprio host) e inicializa o niveis de enlace (recebe o endereco MAC da maquina) 
 * e fisico (recebe a especificacao da porta que ser ́usada para a comunicacao e o endereco IP do comutador 
 * de enlace);
 * Faz as inicializacoes necessarias para as camadas fisica e de enlace e para a camada de rede;
 * Retorna 1 em caso de sucesso e 0 em caso de falha.
 */
int N_Activate_Request (char *, char *, unsigned char, int, char *);


/* Solicita a transmissao de um datagrama;
 * Recebe a identificacao do protocolo que esta ́solicitando o envio do datagrama, o endereco IP de destino, 
 * os dados a serem transmitidos e o numero de bytes
 * Usa o protocolo ARP para encontrar o MAC correspondente ao IP destino
 * (caso o datagrama seja destinado a um host em outra subrede, deve enviar para o roteador de borda)
 *
 */
void N Data Request (unsigned char, char *, char *, int);


/* Testa se ha um datagrama recebido no nivel de rede
 * Recebe como parametro a identificacao do protocolo da camada solicitante
 * Retorna 1 caso exista e 0 caso contrario.
 */
int N Data Indication (unsigned char);


/* Busca no nivel de rede os dados do ultimo datagrama recebido;
 * O primeiro parametro e a identificacao do protocolo que esta recebendo o datagrama
 * O segundo e terceiro parametros sao ponteiros para variaveis que irao conter, respectivamente, 
 * o endereco IP da maquina que enviou o datagrama e os dados do datagrama recebido;
 * O ultimo parametro e o tamanho maximo esperado para o campo de dados do datagrama;
 * Retorna o numero de bytes do campo de dados ou −1 no caso de falha 
 * (numero de bytes do datagrama maior que o tamanho maximo esperado).
 */
int N Data Receive (unsigned char, char *, char *, int);


/* 
 * Configura a taxa de perda de quadros da camada de enlace
 * Recebe o valor percentual de perda de quadros e chama a funcao L_Set_Loss_Probability.
 */
void N Set Loss Probability (float):


/* 
 * Finaliza o funcionamento dos niveis de rede, enlace e fisico.
 */
void N Deactivate Request(void);

