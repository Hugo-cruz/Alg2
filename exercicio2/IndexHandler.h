#ifndef INDEXHANDLER_H_
#define INDEXHANDLER_H_

#include <stdio.h>
#include "FileHandler.h"


typedef struct index_t
{
    int nUSP;   
    int RRN;
} index_t;


//index_t * readIndex();
void readIndex(index_t **);
void writeIndex(index_t *, int);
void insertOrderedIntoIndex(index_t);
int getIndexSize();
bool existOnIndex(int);


#endif