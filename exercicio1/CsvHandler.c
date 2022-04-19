#include "CsvHandler.h"
#include <stdlib.h>



int readCurrentInput(char *currentInput, int lastDelimiterPosition, char line[])
{
    char currentChar;
    int currentInputIndex;
    currentInputIndex = 0;
    do
    {
        currentChar = line[lastDelimiterPosition];
        currentInput[currentInputIndex++] = currentChar;
        lastDelimiterPosition++;
        currentChar = line[lastDelimiterPosition];
    }while((currentChar) && (currentChar != DELIMITERCHAR));

    currentInput[currentInputIndex] = '\0';
    return ++lastDelimiterPosition;
}

student_t parseLine(char line[]){
    
    
    int lastDelimiterPosition = 0;
    student_t student;

    char currentInput[MAXLINESIZE];
    lastDelimiterPosition = readCurrentInput(currentInput, lastDelimiterPosition,line);
    student.nUSP = atoi(currentInput);
    lastDelimiterPosition = readCurrentInput(currentInput, lastDelimiterPosition,line);
    strcpy(student.NomeCompleto, currentInput);
    lastDelimiterPosition = readCurrentInput(currentInput, lastDelimiterPosition,line);
    strcpy(student.Curso, currentInput);
    lastDelimiterPosition = readCurrentInput(currentInput, lastDelimiterPosition,line);
    int nota = atoi(currentInput);
    student.Nota = (float) (nota);
    return student;

}