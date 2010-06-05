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

int main(){
	
	unsigned char mac;

	//Gerando um endereco MAC
	srand ( time(NULL) );
	mac = rand() % 255);

	if(!L_Activate_Request(mac, 5000,"127.0.0.1")){
		printf("--Failed L_Activate_Request\n");
	}

   return 0;
}
