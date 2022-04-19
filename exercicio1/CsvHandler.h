#ifndef CSVHANDLER_H_
#define CSVHANDLER_H_

#include <stdio.h>
#include "Student.h"

#define MAXLINESIZE 100
#define DELIMITERCHAR ','


void readEntryLine();
student_t parseLine(char[]);

#endif

