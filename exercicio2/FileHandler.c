#include "FileHandler.h"

void createFile(char fileName[]) {
    FILE *filePointer;
    filePointer = fopen(fileName, "wb");
    if(filePointer == NULL){
        printf("deu ruim");
        
    }
    fclose(filePointer);
}

FILE *  openFile(char fileName[], char type[]) {
    FILE *filePointer;
    filePointer = fopen(fileName, type);
    if(filePointer == NULL){
        printf("deu ruim");
        
    }
    return(filePointer);
}

void closeFile(FILE *filePointer){
    fclose(filePointer);
}