#include "CRUD.h"
#include "Student.h"



int readCurrentInput(char *currentInput, int lastDelimiterPosition, char line[], char delimiter[])
{
    char currentChar;
    int currentInputIndex;
    currentInputIndex = 0;
    //char delimiterString[] = DELIMITERSTRING;
    do
    {
        currentChar = line[lastDelimiterPosition];
        if(currentChar != '"'){
            currentInput[currentInputIndex] = currentChar;
            currentInputIndex++;
        }
        
        lastDelimiterPosition++;
        currentChar = line[lastDelimiterPosition];
    }while((currentChar) && (currentChar != delimiter[0]));

    currentInput[currentInputIndex] = '\0';
    return ++lastDelimiterPosition;
}

void insert(student_t student){
    insertStudentOnTree(student);
    return;
}

void search(int nUSP){
    if (checkExistOnBtree(nUSP))
    {
        printf("achou\n");
    }else
    {
        printf("n achou\n");
    }
    
    
    
    return;
}

void parseLine(char line[]){
    int lastDelimiterPosition = 0;
    char instruction[MAXLINESIZE];
    lastDelimiterPosition = readCurrentInput(instruction, lastDelimiterPosition,line,DELIMITERINSTRUCTION);

    if(strcmp(instruction,"insert") == 0){
        char currentInput[MAXLINESIZE];
        student_t student;
        lastDelimiterPosition = readCurrentInput(currentInput, lastDelimiterPosition,line,DELIMITERCSV);
        student.nUSP = atoi(currentInput);
        lastDelimiterPosition = readCurrentInput(currentInput, lastDelimiterPosition,line,DELIMITERCSV);
        strcpy(student.Nome, currentInput);
        lastDelimiterPosition = readCurrentInput(currentInput, lastDelimiterPosition,line,DELIMITERCSV);
        strcpy(student.Sobrenome, currentInput);
        lastDelimiterPosition = readCurrentInput(currentInput, lastDelimiterPosition,line,DELIMITERCSV);
        strcpy(student.Curso, currentInput);
        lastDelimiterPosition = readCurrentInput(currentInput, lastDelimiterPosition,line,DELIMITERCSV);
        float nota = atof(currentInput);
        student.Nota = (nota);

        insert(student);
    }
    if(strcmp(instruction,"search") == 0){
        char currentInput[MAXLINESIZE];
        lastDelimiterPosition = readCurrentInput(currentInput, lastDelimiterPosition,line,DELIMITERCSV);
        int nUSP = atoi(currentInput);
        search(nUSP);
    }
    if(strcmp(instruction,"exit") == 0){
        return;
    }
}