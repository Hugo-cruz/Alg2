#include "Student.h"
#include "FileHandler.h"


void printStudentData(student_t student){
    printf("-------------------------------\n");
    printf("nUSP: %d\n",student.nUSP);
    printf("Nome: %s\n",student.Nome);
    printf("Sobrenome: %s\n",student.Sobrenome);
    printf("Curso: %s\n",student.Curso);
    printf("Nota: %.2f\n",student.Nota);
    printf("-------------------------------\n");
}

student_t getStudentData(int RRN){
    FILE *filePointer = openFile(STUDENTDATABASEFILENAME, "rb");
    fseek(filePointer,RRN,SEEK_SET);
    student_t student;
    fread(&student, sizeof(student_t), 1, filePointer);
    fclose(filePointer);
    return student;
}