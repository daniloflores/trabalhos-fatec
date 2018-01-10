/*
 * Projeto Formarq
 *
 * ADS 2ºsem 2017 - Noturno
 *  
 * Andressa 17100244 - Danilo 17100039 - Felipe Aleixo 17100674 - Ítalo 17100010
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "convert.h"

int main(int argc, char *argv[]) 
{
	char docent[200], docsai[200], chave[50];
	FILE *ent, *sai;

	//Tem pelo menos o nome do arquivo e a opcao
	if (argc >= 3)
	{
		strcpy (docent, argv[1]);
		
		if(argv[2][0] == 'C')
		{	
			//Opcao criptografia sem o quarto argumento		
			if (argc < 4)
			{
				printf("\nChave obrigatoria nesta operacao. \nChave:");
				gets(chave);			
			}
			else
			{
				strcpy (chave, argv[3]);	
			}
		}		
	}
	else
	{
		printf("\nO programa sera encerrado. Execute o programa pela linha de comando com as seguintes informacoes: <nome do arquivo> opcao (I, C, D u U) chave (somente para opcao I).");
		getchar();
        exit(1);
	}

	switch(argv[2][0])
	{
		case 'I':
			invert(docent, docsai, ent, sai);
			break;
		case 'C':
			cript(docent, chave);
			break;
		case 'D':
		case 'U':
			unixdos(docent, docsai, ent, sai, argv[2]);	
			break;
		default:
			printf("\nOpcao invalida. O programa sera encerrado.");
			getchar();
            exit(1);
	}
	
	getchar();
	return 0;
}
