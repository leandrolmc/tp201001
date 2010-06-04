/*
 * Arquivo onde e feita a implementacao das funcoes do comutador
 *
 * Componentes: Felipe Almeida Tavares
 *              Leandro Lima Monteiro Coelho
 *		Rafael de Oliveira Costa
 */

int phy_sd; // descritor do socket
struct sockaddr_in local_addr; // informacoes de endereco local

//Estrutura que representa a tabela de emulacao das conexoes fisicas com o comutador
struct table_phy {
};

//Estrutura que representa a tabela de funcionamento normal do comutador
struct table_switch {
};

int start_switch(){

	//A porta do comutador deve ser padrao e todos os hosts devem ter conhecimento disso.
	port=5000
        
	//O endereco do comutador deve ser padrao e todos os hosts devem ter conhecimento disso.
	addr="192.168.0.1"	

	// criando o socket
        if ((phy_sd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
           printf("--Erro na criacao do socket\n");
           return 0;
        }

	// Definindo informações do endereco local
	memset(&local_addr, 0, sizeof(local_addr));
	local_addr.sin_family = AF_INET;
	local_addr.sin_addr.s_addr = inet_addr(addr);
	local_addr.sin_port = htons(port);

	// associando a porta a maquina local
        if (bind(phy_sd,(struct sockaddr *)&local_addr, sizeof(struct sockaddr)) < 0) {
           printf("--Exit com erro no bind \n");
           close(phy_sd);
           return 0;
        } 

	//Devo inicializar as tabelas do comutador

        return 1;
}

int plug_host(){

	return 1;
}

 //Abaixo estao informacoes tiradas da lista de tp com as respostas da Silvana

 /* 1)Como fazer com que esse endereço 255 seja para todos os hosts conectados ao comutador 
  *   quando este não possui nenhuma entrada na tabela?
  *
  * Voce deverá manter duas tabelas distintas: uma responsavel pela emulacao das conexoes fisicas 
  * entre hosts e o comutador; e outra responsavel pela operacao normal de um comutador de enlace 
  * (da forma como vimos na aula). 
  *
  * A primeira tabela é preenchida quando os hosts chamam a funcao L_Activate_Request e contactam o comutador 
  * pela primeira vez (use um formato de mensagem diferenciado para essa primeira comunicaçao). 
  * A partir daí a emulacao estará pronta (como se voce tivesse plugado fisicamente um host a uma porta de entrada 
  * do comutador). Para cada host plugado ao comutador, deverá ser guardado na tabela de emulacao o IP desse host 
  * e a porta para a qual ele fez o bind para que o comutador tenha as informacoes necessarias para redirecionar 
  * os pacotes destinados a esse host no futuro. Cada entrada na tabela passará a funcionar como a identificaçao 
  * de uma porta ativa do comutador.
  *
  * A segunda tabela deverá ser preenchida seguindo a operacao normal de um comutador de enlace. Uma mensagem broadcast 
  * do comutador só atingirá os hosts que já tiverem chamado L_Activate_Request (i.e, já tiverem uma entrada na tabela 
  * de emulacao).
  * 
  */


  /* 2) Como a tabela de comutação deve ser implementada neste trabalho de forma que um host destino que tenha entrada 
   *    na tabela não force o comutador a redirecionar broadcast, ou seja, para o endereço 255?
   *
   *    A tabela de comutaçao será preenchida a medida que os hosts trocarem pacotes entre si (como vimos na aula). 
   *    Se um host  chamou  L_Activate_Request  (está na tabela de emulacao) mas ainda nao enviou nenhum frame, a tabela
   *    de comutacao ainda nao terá a entrada desse host, e, portanto, um frame destinado a ele sera redirecionado 
   *    em broadcast pelo comutador.
   */

  /*  Os hosts deverao informar seu IP e porta no primeiro contato com o comutador para preenchimento da tab. de emulacao.
   *  Apenas os hosts que fizerem esse primeiro contato estarao ativos para broadcast
   */ 


