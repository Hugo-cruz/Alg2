#include "Student.h"
#include "CsvHandler.h"
#include "FileHandler.h"


void printStudentData(student_t student){
    printf("nUSP: %d\n",student.nUSP);
    printf("Nome: %s\n",student.NomeCompleto);
    printf("Curso: %s\n",student.Curso);
    printf("Nota: %.2f",student.Nota);

}

void populateStudentFile(FILE *filePointer){
    
    char line[MAXLINESIZE];
    while(fgets(line,MAXLINESIZE,stdin)){
        //printf("%s\n",line);
        student_t Student = parseLine(line);
        appendBinaryStudentFile(Student);
    }    
    

}
