#include "Student.h"
#include "FileHandler.h"


void printStudentData(student_t student){
    printf("-------------------------------\n");
    printf("USP number: %d\n",student.nUSP);
    printf("Name: %s\n",student.Nome);
    printf("Surname: %s\n",student.Sobrenome);
    printf("Course: %s\n",student.Curso);
    printf("Test grade: %.2f\n",student.Nota);
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