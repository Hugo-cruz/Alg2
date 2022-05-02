#ifndef FILEHANDLER_H_
#define FILEHANDLER_H_

#include <stdio.h>
#include <stdlib.h>
#include "Student.h"

#define TAM 2
#define STUDENTDATABASEFILENAME "student.dat"
#define INDEXFILENAME "index.dat"
#define MAXLINESIZE 100



void createFile(char []);
FILE* openFile(char [], char[]);
void closeFile(FILE*);



#endif //FILEHANDLER_H_