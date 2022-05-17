#ifndef STUDENT_H_
#define STUDENT_H_

#include <stdio.h>
#include <string.h>
#include <stdbool.h>


#include "Student.h"

#define STRING_TAM 40


typedef struct
{
    int nUSP;   
    char Nome[STRING_TAM];
    char Sobrenome[STRING_TAM];
    char Curso[STRING_TAM];
    float Nota;
} student_t;

void printStudentData(student_t);
student_t getStudentData(int);

#endif 