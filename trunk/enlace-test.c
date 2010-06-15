/*
 * Arquivo contendo uma aplicacao para teste das funcoes da camada de enlace
 *
 * Componentes: Felipe Almeida Tavares
 *              Leandro Lima Monteiro Coelho
 *		Rafael de Oliveira Costa
 */

#include "enlace.h"
#include "comutador.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

	char option;
	unsigned char mac;
	char *switch_addr;
	char *buffer;
	char *temp;
	int switch_port;
	int not_leave=0;

	printf("'a': L_Activate_Request\n");
	printf("'s': Sair\n");

	scanf("%c",&option);
	do{
		switch(option){
     		case 'a':      
				getchar();        
				printf("Digite o MAC\n");
				scanf("%c",&mac);
				
				printf("Digite a porta do comutador\n");
				scanf("%d",&switch_port);

				getchar();
				switch_addr  = (char*) malloc (15);
				buffer  = (char*) malloc (15);
				do{
					printf("Digite o IP do comutador\n");
					gets(switch_addr);
					strcpy (buffer,switch_addr);
					temp = strtok (buffer,".");
					while (temp != NULL)
					{
						if(atoi(temp)>255 || atoi(temp)<0){
							not_leave=1;
							printf("--Failed endereco invalido\n");
							break;
						}
		    			temp = strtok (NULL, ".");
						not_leave=0;
					}	
				}while(not_leave);
				free(buffer);

				if(!L_Activate_Request(mac, switch_port,switch_addr)){
				       printf("--Failed L_Activate_Request\n");
				       break;
				}

				printf("--Sucess L_Activate_Request\n");	
				printf("Selecione uma Função\n");
            break;

      	case 's':              
	      	exit(1);
		}
		scanf("%c",&option);
	}while(option!='s');

   return 0;
}
