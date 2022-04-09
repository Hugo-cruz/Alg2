#ifndef STUDENT_H
#define STUDENT_H
#include <stdio.h>

#define NAME_SIZE

typedef struct _student_t {
    char name[NAME_SIZE];
    int age;
    int grade;
} student_t;

void writeStudentDataInFile(student_t, FILE*);
student_t readStudentDataFromFile(FILE*);

#endif //STUDENT_H