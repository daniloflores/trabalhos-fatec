#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* leArquivo(char* nomeArquivo);
int escreverArquivo(char* texto, char* nomeArquivo);
char* getTextoCripto(char* texto, char* chave);
void comecaCripto(char* nomeArquivoEntrada, char* chave);

char* leArquivo(char* nomeArquivo){
    FILE* arquivo = fopen(nomeArquivo, "r");
    
    if (arquivo == NULL){
       printf("\nArquivo não encontrado.\n");
       getchar();
       exit(1);
    }

    char *textoArquivo = malloc(50000);
    char charAtual;
    int index = 0;
    while(( charAtual = fgetc(arquivo)) != EOF){
        textoArquivo[index++] = charAtual;
    }

    fclose(arquivo);
    
    return textoArquivo;
}

int escreverArquivo(char* texto, char* nomeArquivo){

    FILE* arquivoSaida = fopen(nomeArquivo, "w");
    
    if(arquivoSaida == NULL) return 1;
    
    fputs(texto, arquivoSaida);

	fclose(arquivoSaida);
	
	return 0;
	
}

void cript(char* nomeArquivoEntrada, char* chave){

    int tamanhoNome = strlen(nomeArquivoEntrada);
    char* nomeArquivoSemExt = malloc(sizeof(char) * (tamanhoNome - 4));

    int i;
    for(i = 0; i < tamanhoNome; i++){
        char charAtual = nomeArquivoEntrada[i];
        if (charAtual == '.') break;
        nomeArquivoSemExt[i] = charAtual;
    }

    char extensao[4] = {toupper(nomeArquivoEntrada[i+1]), toupper(nomeArquivoEntrada[i+2]), toupper(nomeArquivoEntrada[i+3])};

    char* nomeArquivoSaida = malloc(sizeof(char) * (tamanhoNome));
    if( (strcmp(extensao, "CRP") == 0)){
        nomeArquivoSaida = strcat(nomeArquivoSemExt, ".drp");
    } else {
        nomeArquivoSaida = strcat(nomeArquivoSemExt, ".crp");
    }

    char* entrada = leArquivo(nomeArquivoEntrada);
    char* entradaCriptografada = getTextoCripto(entrada, chave);

    escreverArquivo(entradaCriptografada, nomeArquivoSaida);
    
    printf("\nArquivo convertido com sucesso!\nChave utilizada: %s\nArquivo entrada: %s\nArquivo saida: %s\n", chave, nomeArquivoEntrada, nomeArquivoSaida);

}

char* getTextoCripto(char* texto, char* chave){

	int tamanhoTexto = strlen(texto);
    char *textoCript = malloc (sizeof (char) * tamanhoTexto);
    
    int indexChave = 0;
    int i = 0;
    for(; i < tamanhoTexto; i++, indexChave++){

		if (indexChave > strlen(chave) - 1) indexChave = 0;
        unsigned char atualCharChave = chave[indexChave];
        unsigned char atualCharTexto = texto[i];
        
        char criptografado = atualCharTexto ^ atualCharChave;
		
        textoCript[i] = criptografado;
        
    }

    textoCript[i++] = '\0';

    return textoCript;
}
