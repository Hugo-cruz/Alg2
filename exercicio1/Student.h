#ifndef STUDENT_H_
#define STUDENT_H_

#include <stdio.h>
#include <string.h>

typedef struct student_t
{
    int nUSP;   
    char NomeCompleto[50];    
    char Curso[50];
    float Nota;
} student_t;

student_t readStudentDataFromCSV();
void populateStudentFile();
void printStudentData(student_t);

#endif //STUDENT_H_