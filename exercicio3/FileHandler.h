#ifndef FILEHANDLER_H_
#define FILEHANDLER_H_

#include <stdio.h>
#include <stdlib.h>

#include "btree.h"
#include "Student.h"

#define TAM 2
#define STUDENTDATABASEFILENAME "student.dat"
#define INDEXFILENAME "index.dat"
#define MAXLINESIZE 100



void createFile(char []);
FILE* openFile(char [], char[]);
void createOrOpenFile(char []);
void closeFile(FILE*);


long writeStudentToFile(char[],student_t);
void writeIndexToFile(header_t,char[]);



#endif 