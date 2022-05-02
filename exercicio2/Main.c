#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FileHandler.h"
#include "CRUD.h"
#include "IndexHandler.h"



int main(){

    createFile(STUDENTDATABASEFILENAME);
    createFile(INDEXFILENAME);

    char line[MAXLINESIZE];
    while(fgets(line,MAXLINESIZE,stdin)){
        parseLine(line);
    }

    
}



