/*
 * convert.c
 *
 *  Created on: Dec 2, 2017
 *      Author: Dan
 */
#include <stdio.h>
#include <string.h>


void unixdos (char *docent, char *docsai, FILE *ent, FILE *sai, char *arg){
	int i, ch;

	strcpy(docsai,docent);
	//Copia do nome do arquivo de entrada para o de saida

	for (i=strlen(docsai)-1; i && docsai[i]!='.'; i--);
	if (docsai[i] =='.'){
		if (arg[0]=='D')
			strcpy(docsai+i,".DOS");
		else if (arg[0]=='U')
			strcpy(docsai+i,".UNX");
	}
	else{
		if (arg[0]=='D')
			strcat(docsai,".DOS");
		else if (arg[0]=='U')
			strcat(docsai+i,".UNX");
	}
	//Substituicao da extensao no nome do arquivo de saida

	ent = fopen(docent, "rb");
	sai = fopen(docsai, "wb");
	//Abre arquivos para leitura e escrita no modo BINARIO

	if (ent==NULL){
		printf("\nErro ao abrir arquivos");
		exit(0);
	}
	//Checa o sucesso da abertura do arquivo de entrada

	while(1){

		ch = fgetc(ent); //Le o próximo byte

		if (ch == EOF) //Se chegou EOF, sai do laço
			break;

		if (arg[0]=='D' && ch==10){ //No modo "D" salva byte 13 antes do 10
			fputc(13, sai);
			fputc(ch, sai);
		}
		//else if (arg[0]=='U' && ch==13) //No modo "U" nao copia o byte 13 (modifiquei abaixo)
		else if (ch==13) //Nunca salva o byte 13. Isso evita erros em conversao inesperada DOS->DOS
			continue;
		else
			fputc(ch, sai); //Qualquer outro byte eh copiado sem modificacoes
	}

	fclose(ent);
	fclose(sai);
	
	printf("\nArquivo convertido com sucesso!\nArquivo entrada: %s\nArquivo saida: %s\n", docent, docsai);
	
	//Fecha os arquivos

}
