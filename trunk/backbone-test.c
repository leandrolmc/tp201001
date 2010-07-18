/*
 * Arquivo contendo uma aplicacao para teste das funcoes do backbone
 *
 * Componentes: Felipe Almeida Tavares
 *              Leandro Lima Monteiro Coelho
 *					 Rafael de Oliveira Costa
 */

#include "backbone.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 ****************************************
 ***        Funcoes Auxiliares        ***
 ****************************************
 */
int getch()
{
    int r;
    unsigned char c;

    if ((r = read(0, &c, sizeof(c))) < 0) {
        return r;
    } else {
        return c;
    }
}

void read_addr(char* msg,char *net_addr){

	char *buffer;
	char *temp;
	int not_leave=0;

	buffer    = (char*) malloc (20 * sizeof(char));
	do{
		printf("Digite %s\n",msg);
		fgets(net_addr, 17, stdin);
		net_addr[strlen(net_addr)-1] = '\0'; //remover o \n consumido
		strcpy (buffer,net_addr);
		temp = strtok (buffer,".");
		while (temp != NULL)
		{
			if(atoi(temp)>255 || atoi(temp)<0){
				not_leave=1;
				printf("--Failed %s\n",msg);
				break;
			}
 			temp = strtok (NULL, ".");
			not_leave=0;
		}	
	}while(not_leave);
	free(buffer);
}

void exibir_menu() {
	printf("Selecione uma Função do backbone\n");
	printf("'a': Adicionar rota estatica ao backbone\n");
	printf("'r': Remover  rota estatica do backbone\n");
	printf("'l': Listar a tabela de redirecionamento do backbone\n");
	printf("'i': Iniciar funcionamento do backbone\n");
	printf("'q': Sair\n");
}

void menu(char option){

	int  interface; //variavel utilizada para representar a interface onde a rota estara sendo definida
	char *net_addr; //variavel utilizada para armazenar o endereço de rede da subrede
	char *mask_addr; //variavel utilizada para armazenar a mascara da subrede
	char *buffer;
	char *temp;
	int not_leave=0;

	switch(option){
  		case 'a':      
	
			printf("Digite a interface destino da rota\n");
			scanf("%d",&interface);
			getchar(); // a proxima entrada eh por fgets
			
			net_addr  = (char*) malloc (20 * sizeof(char));
			read_addr("endereco de rede",net_addr);

			mask_addr  = (char*) malloc (20 * sizeof(char));
			read_addr("mascara de subrede",mask_addr);

			if(!route_add(interface,net_addr,mask_addr)){
				printf("--Failed table_redirect is full\n");
			}	
			
			exibir_menu();
			break;

  		case 'r':      
			getchar();
			printf("Para remover uma rota informe endereço de rede e mascara de subrede\n");

			net_addr  = (char*) malloc (20 * sizeof(char));
			read_addr("endereco de rede",net_addr);

			mask_addr  = (char*) malloc (20 * sizeof(char));
			read_addr("mascara de subrede",mask_addr);
		
			if(!route_del(net_addr,mask_addr)){
				printf("--Failed route not found\n");
			}

			exibir_menu();
			break;

		case 'l':
			getchar();
			printf("--Tabela de Redirecionamento:\n");
			printf("---NET_ADDRESS     -|- MASK_ADDRESS    -|- INTERFACE---\n");
			list_table();
			exibir_menu();
			break;

		case 'i':
			getchar();
			printf("--Iniciando backbone...\n");
			if(!start_backbone()){
				printf("--Failed start_backbone\n");
			}	

		case 't':            
			getchar();
			interface=1;
			net_addr  = (char*) malloc (20 * sizeof(char));
			read_addr("Digite IP",net_addr);
			if(!route_add(interface,net_addr,net_addr)){
				printf("--Failed table_redirect is full\n");
			}	
			break;
	
		case 'q':            
			getchar();
			exit(1);
	
		default:
			getchar();
			printf("--Failed Opcao Invalida\n");
			exibir_menu();
			break;
	}
}



int main(){

	exibir_menu();
	while(1){
		menu(getch());
	}

   return 0;
}
