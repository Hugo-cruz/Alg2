#ifndef FILEHANDLER_H_
#define FILEHANDLER_H_

#include <stdio.h>
#include "Student.h"

#define TAM 2
#define BINARYSTUDENTFILENAME "student.dat"



void createBinaryStudentFile();
void readBinaryStudentFile();
void appendBinaryStudentFile(student_t);
void closeBinaryStudentFile(FILE*);

void getLastTenStudents();
long get10Position(FILE*);

#endif //FILEHANDLER_H_