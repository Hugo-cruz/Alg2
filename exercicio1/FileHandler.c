#include "FileHandler.h"

void createBinaryStudentFile() {
    FILE *filePointer;
    filePointer = fopen(BINARYSTUDENTFILENAME, "wb");
    if(filePointer == NULL){
        printf("deu ruim");
        
    }
    fclose(filePointer);
    
}


void closeBinaryStudentFile(FILE* filePointer){
    fclose(filePointer);
}

void appendBinaryStudentFile(student_t student){
    FILE *filePointer;
    filePointer = fopen(BINARYSTUDENTFILENAME, "a+b");
    if(filePointer == NULL){
        printf("deu ruim");
    }
//     fprintf(filePointer,"%d",student.nUSP);
//     fprintf(filePointer,"%s",student.NomeCompleto);
//     fprintf(filePointer,"%s",student.Curso);
//     fprintf(filePointer,"%.2f",student.Nota);
//     fclose(filePointer);
    fwrite(&student,sizeof(student_t),1, filePointer);
    fclose(filePointer);
 }

long get10Position(FILE *filePointer){
    fseek(filePointer,-10*sizeof(student_t),SEEK_END);
    return ftell(filePointer);
}


void getLastTenStudents(){
    FILE *filePointer;
    filePointer = fopen(BINARYSTUDENTFILENAME, "rb");
    if(filePointer == NULL){
        printf("deu ruim");
    }else{
        //Coloca o pointeiro na posicao correta
        fseek(filePointer,((-10)*sizeof(student_t)),SEEK_END);
        struct student_t student;
        fread(&student, sizeof(student_t), 1, filePointer);
        printStudentData(student);
        while(fread(&student, sizeof(struct student_t), 1, filePointer))
        {
            printf("\n\n");
            printStudentData(student);
        }

    }

}