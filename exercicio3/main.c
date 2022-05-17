#include "btree.h"
#include "CRUD.h"
#include "Student.h"
#include "FileHandler.h"

#include <stdlib.h>


int main(void){

    createOrOpenFile(STUDENTDATABASEFILENAME);
    createOrOpenFile(INDEXFILENAME);

    char line[MAXLINESIZE];
    while(fgets(line,MAXLINESIZE,stdin)){
        parseLine(line);
    }
}