#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Registro
{
    int nUSP;   
    char NomeCompleto[50];    
    char Curso[50];
    float Nota;
};

long getFileSize(FILE *arquivo){
    fseek(arquivo, 0, SEEK_END);
    long fileSize = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);
    return fileSize;
}

void printStudent(struct Registro input){
    printf("nUSP: %d\n",input.nUSP);
    printf("Nome: %s\n",input.NomeCompleto);
    printf("Curso: %s\n",input.Curso);
    printf("Nota: %.2f",input.Nota);
}


void case1(char * nome_arquivo){
    FILE *arquivo;
    arquivo = fopen(nome_arquivo,"rb");
    struct Registro input;
    if(arquivo == NULL){
        printf("deu ruim");

    }else{
        fseek(arquivo, 0, SEEK_SET);
        fread(&input, sizeof(struct Registro), 1, arquivo);
        printStudent(input);
        while(fread(&input, sizeof(struct Registro), 1, arquivo))
        {
            printf("\n\n");
            printStudent(input);
        }
    // close file
    fclose (arquivo);
    }
}

void case2(char * nome_arquivo){
    FILE *arquivo;
    arquivo = fopen(nome_arquivo,"rb");
    struct Registro input;
    if(arquivo == NULL){
        printf("deu ruim");
    }else{

        long fileSize = getFileSize(arquivo);
        fseek(arquivo,0,SEEK_SET);
        fread(&input, sizeof(struct Registro), 1, arquivo);
        printStudent(input);
        while(ftell(arquivo) < fileSize/2)
        {
            fread(&input, sizeof(struct Registro), 1, arquivo);
            printf("\n\n");
            printStudent(input);
        }
 
    // close file
    fclose (arquivo);
    }
}

void case3(char * nome_arquivo){
    FILE *arquivo;
    arquivo = fopen(nome_arquivo,"rb");

    struct Registro input;

    if(arquivo == NULL){
        printf("deu ruim");

    }else{

        long fileSize = getFileSize(arquivo);
        fseek(arquivo,fileSize/2,SEEK_SET);
        fread(&input, sizeof(struct Registro), 1, arquivo);
        printStudent(input);
        while(fread(&input, sizeof(struct Registro), 1, arquivo))
        {
            printf("\n\n");
            printStudent(input);
        }
 
    // close file
    fclose (arquivo);
    }
}

void case4(char * nome_arquivo){
    FILE *arquivo;
    arquivo = fopen(nome_arquivo,"rb");

    char inicio[20];
    char fim[20];
    fgets(inicio,20,stdin);
    fgets(fim,20,stdin);

    struct Registro input;

    if(arquivo == NULL){
        printf("deu ruim");

    }else{
        fseek(arquivo,(atoi(inicio)-1)*sizeof(struct Registro),SEEK_SET);
        fread(&input, sizeof(struct Registro), 1, arquivo);
        printStudent(input);
        while(ftell(arquivo) < atoi(fim)*sizeof(struct Registro))
        {
            fread(&input, sizeof(struct Registro), 1, arquivo);
            printf("\n\n");
            printStudent(input);
        }
 
    // close file
    fclose (arquivo);
    }
}

void case5(char * nome_arquivo){
    FILE *arquivo;
    arquivo = fopen(nome_arquivo,"rb");

    char posicao[20];
    fgets(posicao,20,stdin);

    struct Registro input;

    if(arquivo == NULL){
        printf("deu ruim");

    }else{
        fseek(arquivo,(atoi(posicao)-1)*sizeof(struct Registro),SEEK_SET);
        fread(&input, sizeof(struct Registro), 1, arquivo);
        printStudent(input);
 
    // close file
    fclose (arquivo);
    }
}

int main(){

    char nome_arquivo[20];
    char operacao[20];
    fgets(nome_arquivo,20,stdin);
    fgets(operacao,20,stdin);
    int operation = atoi(operacao);
    nome_arquivo[strcspn(nome_arquivo, "\n")] = 0;
    switch(operation){
        case 1:
            case1(nome_arquivo);
            break;
        case 2:
            case2(nome_arquivo);
            break;
        case 3:
            case3(nome_arquivo);
            break;
        case 4:
            case4(nome_arquivo);
            break;
        case 5:
            case5(nome_arquivo);
            break;
        default:
            break;

    }
}


