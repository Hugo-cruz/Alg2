#ifndef STUDENTSTREAMFILEHANDLER_H
#define STUDENTSTREAMFILEHANDLER_H
#include <stdio.h>
#include "Student.h"

#define TAM 10
#define STUDENT_FILE_NAME "student.txt"
#define NAME_SIZE


void createStudenfFile();
void readStudentFile();
void printStudentData(student_t);


#endif //STUDENTSTREAMFILEHANDLER_H