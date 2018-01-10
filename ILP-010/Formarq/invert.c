#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void invert (char *entrada, char *saida, FILE *arquivoEntrada, FILE *arquivoSaida)
{
    char msgEntrada[250];
    strcpy(msgEntrada, "\nArquivo de entrada: ");
    strcat(msgEntrada, entrada);
    printf(msgEntrada);

    int i;
    for(i = strlen(entrada); i && entrada[i] != '.'; i--);

    if(entrada[i] == '.')
    {
        strcpy(saida, entrada);
        if((saida[i+1] == 'I' && saida[i+2] == 'N' && saida[i+3] == 'V') || (saida[i+1] == 'i' && saida[i+2] == 'n' && saida[i+3] == 'v'))
        {
            strcpy(saida + i, ".DNV");
        }
        else
        {
            strcpy(saida + i, ".INV");
        }
    }
    else
    {
        strcpy(saida, entrada);
        strcat(saida, ".INV");
    }

    arquivoEntrada = fopen(entrada,"r");
    if(arquivoEntrada == NULL)
    {
        printf("\nFileOpenException: input file not found");
        return;
    }

    arquivoSaida = fopen(saida,"w");
    if(arquivoSaida == NULL)
    {
        printf("\nFileOpenException: cannot open output file");
        return;
    }

    char msgSaida[250];
    strcat(msgSaida,"\nArquivo de saida: ");
    strcat(msgSaida, saida);
    printf(msgSaida);

    int ch;
    ch = fgetc(arquivoEntrada);
    while(ch != EOF)
    {
        fputc(~ch, arquivoSaida);
        ch = fgetc(arquivoEntrada);
    }
    fclose(arquivoEntrada);
    fclose(arquivoSaida);

    printf("\nArquivo convertido com sucesso!");
}

