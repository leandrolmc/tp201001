/*
 * Arquivo que contem as definicoes de estruturas de dados e das assinaturas das
 * funcoes publicas da camada de enlace
 *
 * Componentes: Felipe Almeida Tavares
 *              Leandro Lima Monteiro Coelho
 *		Rafael de Oliveira Costa
 */

/*
 ***************************************
 *** Estruturas de dados e constantes***
 ***************************************
 */

/*
 * Quadro de enlace: 
 *    endereco de destino, 
 *    endereco fonte, 
 *    tamanho dos dados, 
 *    dados, 
 *    codigo de erro (escolher metodo para deteccao de erro).
 * 
 * FRAME:          MACORIGEM|MACDESTINO|TAMANHODOSDADOS|DADOS|CODIGOERRO|
 *
 * FRAME ESPECIAL: MACORIGEM|000|PORTA|ENDERECOHOST|000|
 */

/*
 * Buffers para armazenar os quadros a serem transmitidos e quadros recebidos.
 */

/*
 * Endereco broadcast (usar o valor 255) definido em enlace.c
 */

/*
 * Definir tamanho maximo de dados de um quadro.
 *
 */

#define FRAME_SIZE 1536

//////////////////////////////////////////

#define PAYLOAD_SIZE 128	

/* Efetua as inicializacoes do nivel de enlace (recebe o endereco local da maquina) e inicializa o nivel  
 * fisico (recebe a especificacao da porta que sera usada para a comunicacao e o endereco IP do comutador de enlace)
 * Faz o bind para a porta escolhida e faz as inicializacoes necessarias para a camada de enlace
 * Retorna 1 em caso de sucesso e 0 em caso de falha
 */
int L_Activate_Request(unsigned char, int, char *);

/* Solicita a transmissao de um quadro
 * Recebe o endereco MAC de destino, os dados a serem transmitidos e o numero de bytes
 */                        
void L_Data_Request(unsigned char, char *, int);

/* Testa se ha um quadro recebido no nivel de enlace
 * Retorna 1 caso exista e 0 caso contrario
 */
int L_Data_Indication(void);

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
int L_Data_Receive(unsigned char *, char *, int);

/* Executa um ciclo de tarefas da camada de enlace e retorna
 * Deve transmitir um byte para o nivel fısico, caso a estacao
 * possua um quadro para transmitir
 * Deve verificar se ha ́um byte para receber no nivel fisico e,
 * caso exista, receber esse byte
 */
void L_MainLoop(void);

/* Configura a taxa de perda de quadros da camada de enlace
 * Recebe o valor percentual de perda de quadros
 */
void L_Set_Loss_Probability(float);

// Finaliza o funcionamento do nivel de enlace e do nivel fısico
void L_Deactivate_Request(void);

/* Recebe um byte e armazena no buffer da camada de enlace,
 * quando o ultimo byte de um quadro e recebido ele deve ser validado
 */
void l_Recebe_Byte(void); 

/* Valida um quadro recebido, apenas mantem um quadro no buffer de recepcao se for
 * destinado a maquina local ou broadcast, e passar na
 * checagem de erro (usar probabilidade randomica de erro para
 * “forcar” a ocorrencia de erros)
 */
void l_Valida_Quadro(void); 

// Transmite um byte do quadro e checa se terminou a transmissao do quadro                            
void l_Transmite_Byte(void);

