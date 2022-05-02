#include "CRUD.h"
#include "Student.h"



int readCurrentInput(char *currentInput, int lastDelimiterPosition, char line[], char delimiter[])
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
    }while((currentChar) && (currentChar != delimiter[0]));

    currentInput[currentInputIndex] = '\0';
    return ++lastDelimiterPosition;
}

void insert(student_t student){
    if(existOnIndex(student.nUSP) == true){
        printf("O Registro ja existe!\n");
        return;
    } 
    
    FILE *filePointerStudent = openFile(STUDENTDATABASEFILENAME, "ab");
    
    //posiciona o ponteiro no final do arquivo para calcular o RRN final
    fseek(filePointerStudent,0,SEEK_END);
    long lastRRN = ftell(filePointerStudent);
    //append no arquivo
    fwrite(&student,sizeof(student_t),1,filePointerStudent);

    //Cria o index para adicionar
    index_t actualIndex;
    actualIndex.nUSP = student.nUSP;
    actualIndex.RRN = lastRRN;
    //append no index
    insertOrderedIntoIndex(actualIndex);
    closeFile(filePointerStudent);
}



void search(int nUSP){
    index_t * index;
    readIndex(&index);
    int indexSize = getIndexSize();
    int inf = 0;
    int sup = indexSize-1;
    //Busca binaria
    while(inf<=sup){
        //float floatMetade = sup/inf;
        int metade = (sup+inf)/2;
        if(nUSP == index[metade].nUSP){
            printStudentData(getStudentData(index[metade].RRN));
            return;
        }
        if(nUSP < index[metade].nUSP){
            sup = metade-1;   
        }else{
            inf = metade+1;
        }
    }
    printf("Registro nao encontrado!\n");
    return;
}

bool existOnIndex(int nUSP){
    index_t * index;
    readIndex(&index);
    int indexSize = getIndexSize();
    int inf = 0;
    int sup = indexSize-1;
    //Busca binaria
    while(inf<=sup){
        int metade = (sup+inf)/2;
        if(nUSP == index[metade].nUSP){
            return true;
        }
        if(nUSP < index[metade].nUSP){
            sup = metade-1;   
        }else{
            inf = metade+1;
        }
    }
    return false;
}

void delete (int nUSP){
    int lastIndexOfIndex = getIndexSize();
    index_t * index;
    readIndex(&index);
    
    //Deleta o arquivo existente
    FILE *filePointer;
    filePointer = fopen(INDEXFILENAME, "w+b");
    if(filePointer == NULL){
        printf("deu ruim");
    }
    fclose(filePointer);
    filePointer = NULL;
    
    //Cria um novo arquivo pra append
    filePointer = fopen(INDEXFILENAME, "ab");
    if(filePointer == NULL){
        printf("deu ruim");
    }
    int i=0;
    
    do{
        if(index[i].nUSP != nUSP){
            fwrite(&index[i],sizeof(index_t),1, filePointer);
        }
        i++;
    }while(i<lastIndexOfIndex);


    fclose(filePointer);
    filePointer = NULL;

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
        int nota = atoi(currentInput);
        student.Nota = (float) (nota);

        insert(student);
    }
    if(strcmp(instruction,"search") == 0){
        char currentInput[MAXLINESIZE];
        lastDelimiterPosition = readCurrentInput(currentInput, lastDelimiterPosition,line,DELIMITERCSV);
        int nUSP = atoi(currentInput);
        search(nUSP);
    }
    if(strcmp(instruction,"delete") == 0){
        char currentInput[MAXLINESIZE];
        lastDelimiterPosition = readCurrentInput(currentInput, lastDelimiterPosition,line,DELIMITERCSV);
        int nUSP = atoi(currentInput);
        delete(nUSP);
    }
    if(strcmp(instruction,"exit") == 0){
        return;
    }
}