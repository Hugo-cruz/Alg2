#ifndef STUDENT_H_
#define STUDENT_H_

#include <stdio.h>
#include <string.h>
#include <stdbool.h>


#include "FileHandler.h"
#include "Student.h"

typedef struct student_t
{
    int nUSP;   
    char Nome[50];
    char Sobrenome[50];
    char Curso[50];
    float Nota;
} student_t;

void printStudentData(student_t);
student_t getStudentData(int);

#endif //STUDENT_H_