#include "FileHandler.h"

void createOrOpenFile(char fileName[]) {
    FILE *filePointer;
    filePointer = fopen(fileName, "ab+");
    if(filePointer == NULL){
        printf("deu ruim");
        
    }
    fclose(filePointer);
}

FILE * openFile(char fileName[], char type[]) {
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

long writeStudentToFile(char fileName[], student_t student) {
    FILE *filePointer;
    filePointer = fopen(fileName, "ab+");
    if(filePointer == NULL){
        printf("deu ruim");
        
    }
    long rrn = ftell(filePointer);
    fwrite(&student, sizeof(student_t), 1, filePointer);
    fclose(filePointer);
    return rrn;
}
