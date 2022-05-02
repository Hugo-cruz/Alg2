#include "IndexHandler.h"


int getIndexSize(){
    
    FILE *filePointer;
    filePointer = fopen(INDEXFILENAME, "rb");
    if(filePointer == NULL){
        printf("deu ruim");
    }

    fseek(filePointer, 0L, SEEK_END);
    long end_position = ftell(filePointer);
    int numElements = (int) end_position/sizeof(index_t);
    fclose(filePointer);
    filePointer = NULL;

    return numElements;
}


//index_t * readIndex(){
void readIndex(index_t **index){
    
    FILE *filePointer;
    filePointer = fopen(INDEXFILENAME, "rb");
    if(filePointer == NULL){
        printf("deu ruim");
    }

    fseek(filePointer, 0, SEEK_END);
    long end_position = ftell(filePointer);
    int numElements = end_position/sizeof(index_t);

    *index = malloc(numElements * sizeof(index_t));
    index_t indexItem;

    fseek(filePointer, 0, SEEK_SET);
    int i=0;
    while(fread(&indexItem, sizeof(index_t), 1, filePointer))
    {
        (*index)[i].nUSP = indexItem.nUSP;
        (*index)[i].RRN = indexItem.RRN;
        i++;
    }
    

    fclose(filePointer);
    filePointer = NULL;

    //return index;
}

void insertOrderedIntoIndex(index_t indexItem){

    index_t * index;
    readIndex(&index);
    index_t tempItem;
    tempItem.nUSP = indexItem.nUSP;
    tempItem.RRN = indexItem.RRN;
    
    index_t tempItem2;
    
    int indexSize = getIndexSize();
    index_t * temp = (index_t*) realloc(index, (indexSize+1)*sizeof(index_t));
    if (temp != NULL){
        index = temp;
    }else{
        printf("ih carai\n");
    }
    //Variavel pra percorrer a lista
    int i = 0;
    if(indexSize == 0){
        index[i].nUSP = tempItem.nUSP;
        index[i].RRN = tempItem.RRN;
    }else{
        //Lógica semelhante ao insertionsort
        //Checa se o valor é menor, se for, faz um swap
        //do valor a ser inserido com o valor da posicao
        
        do{
            if(index[i].nUSP > tempItem.nUSP){
                tempItem2.nUSP = index[i].nUSP;
                tempItem2.RRN = index[i].RRN;

                index[i].nUSP = tempItem.nUSP;
                index[i].RRN = tempItem.RRN;

                tempItem.nUSP = tempItem2.nUSP;
                tempItem.RRN = tempItem2.RRN;
            }
            i++;
        }while(i<indexSize);
        //Por fim, faz um realloc para inserir o ultimo valor
        
        index[i].nUSP = tempItem.nUSP;
        index[i].RRN = tempItem.RRN;
    }  

    writeIndex(index,i);
    free(index);

}


void writeIndex(index_t * index, int lastIndexOfIndex){
    //Deleta o arquvo existente
    FILE *filePointer;
    filePointer = fopen(INDEXFILENAME, "w+b");
    if(filePointer == NULL){
        printf("deu ruim");
    }
    fclose(filePointer);
    filePointer = NULL;
    
    //Cria um novo para append
    filePointer = fopen(INDEXFILENAME, "ab");
    if(filePointer == NULL){
        printf("deu ruim");
    }
    int i=0;
    do{ 
        fwrite(&index[i],sizeof(index_t),1, filePointer);
        i++;
    }while(i<lastIndexOfIndex+1);

    fclose(filePointer);
    filePointer = NULL;
}

