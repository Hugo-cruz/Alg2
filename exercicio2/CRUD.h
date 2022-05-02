#ifndef CRUD_H_
#define CRUD_H_

#include <stdio.h>
#include <stdlib.h>
#include "Student.h"
#include "FileHandler.h"
#include "IndexHandler.h"

#define DELIMITERINSTRUCTION " "
#define DELIMITERCSV ","
#define MAXLINESIZE 100

void parseLine(char[]);
int readCurrentInput(char *, int , char [], char[]);

void insert(student_t);
void search(int);
void delete(int);

#endif