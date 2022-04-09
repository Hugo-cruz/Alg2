#include "StudentStreamFileHandler.h"


void createStudentFile(){
    FILE *filepPointer;
    filepPointer = fopen(STUDENT_FILE_NAME,"w");
    student_t student;
    printf("Lendo dados \n\n");

    for(int i=0;i<TAM;i++){
        student = readStudentDataFromFile(filepPointer);
        writeStudentDataInFile(student, filepPointer);

    }

    fclose(filepPointer);
}

student_t readStudentDataFromFile(FILE *filePointer)
{
    student_t student;
    printf("Nome do estudante: \n");
    scanf("%s",student.name);
    printf("Idade \n");
    scanf("%d", &student.age);
    printf("Grade \n");
    scanf("%d", &student.grade);
    
    return student;
}

void writeStudentDataInFile(student_t student, FILE *filePointer)
{
    fprintf(filePointer, "%s", student.name);
    fprintf(filePointer, "%d", student.age);
    fprintf(filePointer, "%d", student.grade);

}

void readStudentFile(){
    FILE *filePointer;
    filePointer = fopen(STUDENT_FILE_NAME, "r");
    if(filePointer != NULL){
        student_t student;
        printf("Dados no arquivo\n");
        for(int i = 0;i< TAM;i++){
            student = readStudentDataFromFile(filePointer);
            printStudentData(student);
        }
    }
    

}

student_t readStudentDataFromFile(FILE *filePointer){
    student_t student;
    fscanf(filePointer,"%s",student.name);
    fscanf(filePointer,"%d",student.age);
    fscanf(filePointer,"%d",student.grade);
}

void printStudentData(student_t student)
{
    printf("Nome: %s\n",student.name);
    printf("Age: %d\n",student.age);
    printf("Grade: %d\n",student.grade);
}