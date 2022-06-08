#include "btree.h"
#include "FileHandler.h"

//Function to debug the nodes
void printNode(node_t *node){

	printf("Keys\n");
	for(int i=0;i<ORDER-1;i++){
		printf("%ld | ",node->keyVector[i]);
	}
	printf("\nData\n");
	for(int i=0;i<ORDER-1;i++){
		printf("%ld | ",node->dataRrnVector[i]);
	}
	printf("\nChildren\n");
	for(int i=0;i<ORDER;i++){
		printf("%ld | ",node->childrenVector[i]);
	}
	printf("\n");
}

//Function to debug itens to promote in the overflow
void printItemToPromote(item_to_promote_t itemToPromote){
	printf("\nItem to promote\n");
	printf("has value %i\n",itemToPromote.hasValue);
	if (itemToPromote.hasValue)
	{
		printf("nusp : %d\n", itemToPromote.keyToPromote);
		printf("children %ld and %ld\n", itemToPromote.leftChildRRN, itemToPromote.rigthChildRRN);
	}
	

}

//function to load header on memory
header_t* loadBTreeHeader() {
	FILE *indexFile= fopen(INDEXFILENAME, "r+");
	header_t *header = (header_t *) malloc(sizeof(header_t));

	//Checking if file is empty
	fseek(indexFile, 0, SEEK_END);
	if (ftell(indexFile) == 0) {
		header->nodesNumber = 0;
		header->order = ORDER;
		header->rootNodeRRN = -1;
		fwrite(header, sizeof(header_t), 1, indexFile);
	}

	else {
		fseek(indexFile, 0, SEEK_SET);
		fread(header, sizeof(header_t), 1, indexFile);
	}
	
	fclose(indexFile);
	return header;
}

//function to record the header on file
void recordBTreeHeader(header_t *header, FILE *indexFile){
	//Writing header to index file
	fseek(indexFile, 0, SEEK_SET);
	fwrite(header, sizeof(header_t), 1, indexFile);
	
	return;
}	

//function to check if a student already exists on the btree
bool checkExistOnBtree(int nUSP){
	header_t *header = loadBTreeHeader();
	int nodePosition = header->rootNodeRRN;


	FILE * filePointer = openFile(INDEXFILENAME,"r+b");

	while(nodePosition != -1){
		node_t *iterativeNode = (node_t *) malloc(sizeof(node_t));
		fseek(filePointer, nodePosition, SEEK_SET);
		fread(iterativeNode, sizeof(node_t), 1, filePointer);

		//if its not a leaf
		if (iterativeNode->keyVector[0] > nUSP)
		{
			nodePosition = iterativeNode->childrenVector[0];
		}else
		{
			//its a leaf
			for(int i=header->order-2;i>=0;i--){
				if (iterativeNode->keyVector[i] == nUSP)
				{
					free(iterativeNode);
					fclose(filePointer);
					return true;
				}
				//iterate through vector to check the correct child to proceed				
				if(iterativeNode->keyVector[i] != -1 && (iterativeNode->keyVector[i] < nUSP)){
					nodePosition = iterativeNode->childrenVector[i+1];
					break;
				}
			}
		}
		free(iterativeNode);
	}
	fclose(filePointer);
	return false;
}	


void caseEmptyRoot(header_t *header,FILE *indexFile, student_t student, long rrn){
	node_t *rootNode = createNewNode(header);
	rootNode->nodeSize++;
	rootNode->dataRrnVector[0]=rrn;
	rootNode->keyVector[0]=student.nUSP;

	//Writing root node to index file
	fseek(indexFile, 0, SEEK_END);
	header->rootNodeRRN = ftell(indexFile);
	fwrite(rootNode, sizeof(node_t), 1, indexFile);
	//printNode(rootNode);

	free(rootNode);

	
}

void caseRootIsLeafWithoutOveflow(node_t *rootNode, FILE* filePointer, int nUSP, long rrn, header_t *header){
	
	int i=0;
	int tempNUSP = nUSP;
	int temp2NUSP;

	int tempData = rrn;
	int temp2Data;

	do{
		if(rootNode->keyVector[i]>tempNUSP){
			temp2NUSP = rootNode->keyVector[i];
			temp2Data = rootNode->dataRrnVector[i];

			rootNode->keyVector[i] = tempNUSP;
			rootNode->dataRrnVector[i] = tempData;

			tempNUSP = temp2NUSP;
			tempData = temp2Data;
		}
		i++;
	}while(i<(rootNode->nodeSize));
	rootNode->keyVector[i] = tempNUSP;
	rootNode->dataRrnVector[i] = tempData;
	rootNode->nodeSize++;

	fseek(filePointer, header->rootNodeRRN, SEEK_SET);
	fwrite(rootNode, sizeof(node_t), 1, filePointer);


}

void caseRootIsLeafWithOveflow(node_t *rootNode, FILE* filePointer, student_t student, long rrn, header_t *header){

	node_t *highChild = createNewNode(header);
	highChild->nodeSize = 0;
	int contadorHigh =0;

	node_t *lowChild = createNewNode(header);
	lowChild->nodeSize = 0;
	int contadorLow = 0;

	int tempNUSP = student.nUSP;
	int temp2NUSP;
	int tempData = rrn;
	int temp2Data;

	int i=0;
	
	
	int metade = (ORDER)/2;
	//Solução: insere ordenado e sobe a chave da metade (apos ordena-la) para a raiz
	//Ordenando os ponteiros
	do{
		if(rootNode->keyVector[i]>tempNUSP){
			temp2NUSP = rootNode->keyVector[i];
			temp2Data = rootNode->dataRrnVector[i];

			rootNode->keyVector[i] = tempNUSP;
			rootNode->dataRrnVector[i] = tempData;

			tempNUSP = temp2NUSP;
			tempData = temp2Data;
		}
		//Na metade inferior do vetor, joga para o lowChild e limpa a raiz
		if(i<metade){
			lowChild->keyVector[contadorLow] = rootNode->keyVector[i];
			lowChild->dataRrnVector[contadorLow] = rootNode->dataRrnVector[i];
			lowChild->nodeSize++;
			rootNode->keyVector[i] = -1;
			rootNode->dataRrnVector[i] = -1;
			contadorLow++;
		//Na metade superior, joga para o highChild
		}else if (i>metade)
		{
			highChild->keyVector[contadorHigh] = rootNode->keyVector[i];
			highChild->dataRrnVector[contadorHigh] = rootNode->dataRrnVector[i];
			highChild->nodeSize++;
			rootNode->keyVector[i] = -1;
			rootNode->dataRrnVector[i] = -1;
			contadorHigh++;
		//Se for o item da metade, sobe para a raiz
		}else if(i==metade){
			rootNode->keyVector[0] = rootNode->keyVector[i];
			rootNode->dataRrnVector[0] = rootNode->dataRrnVector[i];

			rootNode->keyVector[i] = -1;
			rootNode->dataRrnVector[i] = -1;
		}
		i++;
	}while(i<ORDER-1);
	highChild->keyVector[contadorHigh] = tempNUSP;
	highChild->dataRrnVector[contadorHigh] = tempData;
	highChild->nodeSize++;

	//após ofinal, a raiz terá apenas 1 elemento
	rootNode->nodeSize = 1;

	//insert new nodes on file
	fseek(filePointer, 0, SEEK_END);
	rootNode->childrenVector[0] = ftell(filePointer);
	fwrite(lowChild, sizeof(node_t), 1, filePointer);
	rootNode->childrenVector[1] = ftell(filePointer);
	fwrite(highChild, sizeof(node_t), 1, filePointer);
	fseek(filePointer, header->rootNodeRRN, SEEK_SET);
	fwrite(rootNode,sizeof(node_t),1,filePointer);

	// printf("\n\nroot\n");
	// printNode(rootNode);
	// printf("\nhigh\n");
	// printNode(highChild);
	// printf("\nlow\n");
	// printNode(lowChild);
	

	free(highChild);
	free(lowChild);
}

void insertOnLeafWithoutOveflow(node_t *iterativeNode, FILE* filePointer,int nUSP, long rrn, header_t *header, int nodePosition){
	int i=0;
	int tempNUSP = nUSP;
	int temp2NUSP;

	int tempData = rrn;
	int temp2Data;

	do{
		if(iterativeNode->keyVector[i]>tempNUSP){
			temp2NUSP = iterativeNode->keyVector[i];
			temp2Data = iterativeNode->dataRrnVector[i];

			iterativeNode->keyVector[i] = tempNUSP;
			iterativeNode->dataRrnVector[i] = tempData;

			tempNUSP = temp2NUSP;
			tempData = temp2Data;
		}
		i++;
	}while(i<(iterativeNode->nodeSize));
	iterativeNode->keyVector[i] = tempNUSP;
	iterativeNode->dataRrnVector[i] = tempData;
	iterativeNode->nodeSize++;


	fseek(filePointer, nodePosition, SEEK_SET);
	fwrite(iterativeNode, sizeof(node_t), 1, filePointer);
	
}

item_to_promote_t insertOnLeafWithOveflow(node_t *iterativeNode, FILE* filePointer,int nUSP, long rrn, header_t *header){


	node_t *highChild = createNewNode(header);
	highChild->nodeSize = 0;
	int contadorHigh =0;

	node_t *lowChild = createNewNode(header);
	lowChild->nodeSize = 0;
	int contadorLow = 0;

	int tempNUSP = nUSP;
	int temp2NUSP;
	int tempData = rrn;
	int temp2Data;
	
	int metade = (ORDER-1)/2;

	//utils to promote 
	item_to_promote_t itemToPromote;

	//printf("\ninserir nusp COM OVERFLOW %d\n",nUSP);
	//printf("node b4\n");
	//printNode(iterativeNode);

	//Solução: insere ordenado e sobe a chave da metade (apos ordena-la) para a raiz
	//Ordenando os ponteiros
	for(int i=0;i<ORDER-1;i++){
		if(iterativeNode->keyVector[i]>tempNUSP){
			temp2NUSP = iterativeNode->keyVector[i];
			temp2Data = iterativeNode->dataRrnVector[i];

			iterativeNode->keyVector[i] = tempNUSP;
			iterativeNode->dataRrnVector[i] = tempData;

			tempNUSP = temp2NUSP;
			tempData = temp2Data;
		}
		//Na metade inferior do vetor, joga para o lowChild e limpa a raiz
		if(i<metade){
			lowChild->keyVector[contadorLow] = iterativeNode->keyVector[i];
			lowChild->dataRrnVector[contadorLow] = iterativeNode->dataRrnVector[i];
			lowChild->nodeSize++;
			contadorLow++;
		//Na metade superior, joga para o highChild
		}else if (i>metade)
		{
			highChild->keyVector[contadorHigh] = iterativeNode->keyVector[i];
			highChild->dataRrnVector[contadorHigh] = iterativeNode->dataRrnVector[i];
			highChild->nodeSize++;
			contadorHigh++;
		//Se for o item da metade, sobe para a raiz
		}else if(i==metade){
			itemToPromote.keyToPromote = iterativeNode->keyVector[i];
			itemToPromote.rrnToPromote = iterativeNode->dataRrnVector[i];	
		}
	}

	highChild->keyVector[contadorHigh] = tempNUSP;
	highChild->dataRrnVector[contadorHigh] = tempData;
	highChild->nodeSize++;
	contadorHigh++;


	
	// printf("node after COM OVERFLOW\n");
	// printNode(iterativeNode);
	// printf("item to promot \n");
	


	//insert new nodes on file
	fseek(filePointer, 0, SEEK_END);
	itemToPromote.leftChildRRN = ftell(filePointer);
	fwrite(lowChild, sizeof(node_t), 1, filePointer);
	itemToPromote.rigthChildRRN = ftell(filePointer);
	fwrite(highChild, sizeof(node_t), 1, filePointer);
	
	
	
	//Estamos criando 2 nós e deixando de usar o nó antigo, por isso decrementamos
	header->nodesNumber--;
	// printf("Low \n");
	// printNode(lowChild);
	// printf("High \n");
	// printNode(highChild);
	free(highChild);
	free(lowChild);

	itemToPromote.hasValue = true;
	// printItemToPromote(itemToPromote);
	return itemToPromote;
}

item_to_promote_t insertOnNotLeafWithoutOverflow(node_t *iterativeNode, int nodePosition, FILE* filePointer,item_to_promote_t itemToPromote, header_t *header){

	int nUSP = itemToPromote.keyToPromote;
	int rrn = itemToPromote.rrnToPromote;

	int leftChildRRN = itemToPromote.leftChildRRN;
	int tempLeftChildRRN;
	int rigthChildRRN = itemToPromote.rigthChildRRN;
	int tempRigthChildRRN;

	int tempNUSP;
	int tempRRN;

	bool found = false;
	int lastPosition = 0;
	
	// printf("\ninserir nusp %d\n",nUSP);
	// printf("node b4\n");
	// printNode(iterativeNode);

	for (int i=0;i<ORDER-1;i++)
	{
		if (iterativeNode->keyVector[i]>nUSP)
		{

			tempNUSP = iterativeNode->keyVector[i];
			iterativeNode->keyVector[i] = nUSP;
			nUSP = tempNUSP;

			tempRRN = iterativeNode->dataRrnVector[i];
			iterativeNode->dataRrnVector[i] = rrn;
			rrn = tempRRN;

			tempLeftChildRRN = iterativeNode->childrenVector[i];
			tempRigthChildRRN = iterativeNode->childrenVector[i+1];

			iterativeNode->childrenVector[i] = leftChildRRN;
			iterativeNode->childrenVector[i+1] = rigthChildRRN;

			leftChildRRN = rigthChildRRN;
			rigthChildRRN = tempRigthChildRRN;			
			found = true;
		}
		if(iterativeNode->keyVector[i]!=-1)
		{
			lastPosition++;
		}
	}
	if (!found)
	{
		iterativeNode->keyVector[lastPosition] = nUSP;
		iterativeNode->dataRrnVector[lastPosition] = rrn;
		iterativeNode->childrenVector[lastPosition] = leftChildRRN;
		iterativeNode->childrenVector[lastPosition+1] = rigthChildRRN;

	}
	// printf("node after\n");
	// printNode(iterativeNode);
	
	fseek(filePointer, nodePosition, SEEK_SET);
	fwrite(iterativeNode, sizeof(node_t), 1, filePointer);

	itemToPromote.hasValue = false;
	return itemToPromote;

}

item_to_promote_t insertOnNotLeafWithOverflow(node_t *iterativeNode, int nodePosition, FILE* filePointer,item_to_promote_t itemToPromote, header_t *header){

	node_t *highChild = createNewNode(header);
	highChild->nodeSize = 0;
	int contadorHigh =0;

	node_t *lowChild = createNewNode(header);
	lowChild->nodeSize = 0;
	int contadorLow = 0;

	int helperVectornUSP[ORDER];
	int helperVectorRRN[ORDER];
	int helperVectorChildren[ORDER+1];


	int metade = (ORDER)/2;

	//Variável para caso já tenha achado no vetor

	int nUSP = itemToPromote.keyToPromote;
	int rrn = itemToPromote.rrnToPromote;

	int leftChildRRN = itemToPromote.leftChildRRN;
	int tempLeftChildRRN;
	int rigthChildRRN = itemToPromote.rigthChildRRN;
	int tempRigthChildRRN;

	int tempNUSP;
	int tempRRN;

	for (int i=0;i<ORDER-1;i++)
	{
		if (iterativeNode->keyVector[i]>nUSP)
		{
			tempNUSP = iterativeNode->keyVector[i];
			helperVectornUSP[i] = nUSP;
			nUSP = tempNUSP;

			tempRRN = iterativeNode->dataRrnVector[i];
			helperVectorRRN[i] = rrn;
			rrn = tempRRN;

			tempLeftChildRRN = iterativeNode->childrenVector[i];
			tempRigthChildRRN = iterativeNode->childrenVector[i+1];

			helperVectorChildren[i] = leftChildRRN;
			helperVectorChildren[i+1] = rigthChildRRN;

			leftChildRRN = rigthChildRRN;
			rigthChildRRN = tempRigthChildRRN;

		}else
		{
			helperVectornUSP[i] = iterativeNode->keyVector[i];
			helperVectorRRN[i] = iterativeNode->dataRrnVector[i];
			helperVectorChildren[i] = iterativeNode->childrenVector[i];
			
		}
	}
	

	for(int i=0;i<ORDER;i++){
		//Na metade inferior do vetor, joga para o lowChild e limpa a raiz
		if(i<metade){
			lowChild->keyVector[contadorLow] = helperVectornUSP[i];
			lowChild->dataRrnVector[contadorLow] = helperVectorRRN[i];
			lowChild->childrenVector[contadorLow] = helperVectorChildren[i];
			lowChild->childrenVector[contadorLow+1] = helperVectorChildren[i+1];
			lowChild->nodeSize++;
			contadorLow++;
		//Na metade superior, joga para o highChild
		}else if (i>metade)
		{
			highChild->keyVector[contadorHigh] = helperVectornUSP[i];
			highChild->dataRrnVector[contadorHigh] = helperVectorRRN[i];
			highChild->childrenVector[contadorHigh] = helperVectorChildren[i];
			highChild->childrenVector[contadorHigh+1] = helperVectorChildren[i+1];
			highChild->nodeSize++;
			contadorHigh++;
		//Se for o item da metade, sobe para a raiz
		}else if(i==metade){
			itemToPromote.keyToPromote = helperVectornUSP[i];
			itemToPromote.rrnToPromote = helperVectorRRN[i];	
		}

	}
	
	//insert new nodes on file
	fseek(filePointer, 0, SEEK_END);
	itemToPromote.leftChildRRN = ftell(filePointer);
	fwrite(lowChild, sizeof(node_t), 1, filePointer);
	itemToPromote.rigthChildRRN = ftell(filePointer);
	fwrite(highChild, sizeof(node_t), 1, filePointer);
	
	//update root on file
	// fseek(filePointer, header->rootNodeRRN, SEEK_SET);
	// fwrite(iterativeNode, sizeof(node_t), 1, filePointer);

	header->nodesNumber--;
	free(highChild);
	free(lowChild);

	itemToPromote.hasValue = true;
	return itemToPromote;
	
	
}	

item_to_promote_t insertOnTreeWithOverflowHandler(int nodePosition, FILE* filePointer, int nUSP, long rrn, header_t *header){
	item_to_promote_t itemToPromote;

	if (nodePosition == -1)
	{
		itemToPromote.hasValue = false;
		return itemToPromote;
	}
	
	
	node_t *iterativeNode = (node_t *) malloc(sizeof(node_t));
	fseek(filePointer, nodePosition, SEEK_SET);
	fread(iterativeNode, sizeof(node_t), 1, filePointer);


	//printf("init overflow handling nodePosition %d and nusp %d\n", nodePosition, nUSP);
	int nextChildrenPosition;
	
	//if its not a leaf
	if(iterativeNode->childrenVector[0] != -1){
		if (iterativeNode->keyVector[0] > nUSP)
		{
			nextChildrenPosition = iterativeNode->childrenVector[0];
		}else
		{
			for(int i=header->order-2;i>=0;i--){
				if(iterativeNode->keyVector[i] != -1 && (iterativeNode->keyVector[i] < nUSP)){
					nextChildrenPosition = iterativeNode->childrenVector[i+1];
					itemToPromote =  insertOnTreeWithOverflowHandler(nextChildrenPosition,filePointer,nUSP,rrn,header);
					break;
				}
			}

		}
		if (itemToPromote.hasValue)
		{
			// printf("pariu inserir fora da folha\n");
			//If theres no overflow
			if (iterativeNode->nodeSize<header->order-1)
			{
				// printf("Inserir fora na folha SEM overflow\n");
				itemToPromote = insertOnNotLeafWithoutOverflow(iterativeNode, nodePosition, filePointer,itemToPromote,header);
				return itemToPromote;
			}else
			{
				// printf("Inserir fora na folha COM overflow\n");
				itemToPromote = insertOnNotLeafWithOverflow(iterativeNode, nodePosition, filePointer,itemToPromote,header);
				// printf("Overflow\n");
				printItemToPromote(itemToPromote);
				return itemToPromote;
			}
			
			
		}else
		{
			return itemToPromote;
		}
		
	//If its a leaf
	}else{
		if (iterativeNode->nodeSize < header->order-1) {
			// printf("Inserindo num no folha sem overflow\n");
			insertOnLeafWithoutOveflow(iterativeNode,filePointer,nUSP,rrn,header,nodePosition);
			itemToPromote.hasValue = false;
			return itemToPromote;
		}else{
			// printf("Inserindo num no folha com overflow\n");
			item_to_promote_t itemToPromote = insertOnLeafWithOveflow(iterativeNode,filePointer, nUSP, rrn,header);
			// printItemToPromote(itemToPromote);
			return itemToPromote;
		}
		
	}

	free(iterativeNode);
	return itemToPromote;
	
}

void moreThanOneLeaf(node_t *rootNode, FILE* filePointer, student_t student, long rrn, header_t *header){

	int rootPosition = header->rootNodeRRN;

	node_t *iterativeNode = (node_t *) malloc(sizeof(node_t));

	item_to_promote_t itemToNewRoot = insertOnTreeWithOverflowHandler(rootPosition, filePointer, student.nUSP, rrn, header);

	if (itemToNewRoot.hasValue)
	{
		node_t *newRoot = createNewNode(header);
		newRoot->keyVector[0] = itemToNewRoot.keyToPromote;
		newRoot->dataRrnVector[0] = itemToNewRoot.rrnToPromote;
		newRoot->childrenVector[0] = itemToNewRoot.leftChildRRN;
		newRoot->childrenVector[1] = itemToNewRoot.rigthChildRRN;
		newRoot->nodeSize++;


		//insert new nodes on file
		fseek(filePointer, 0, SEEK_END);
		header->rootNodeRRN = ftell(filePointer);
		fwrite(newRoot, sizeof(node_t), 1, filePointer);

		//Writing header to index file
		fseek(filePointer, 0, SEEK_SET);
		fwrite(header, sizeof(header_t), 1, filePointer);
		free(newRoot);


	}
	


	free(iterativeNode);
	return;
}

void insertStudentOnTree(student_t student){
	if (!checkExistOnBtree(student.nUSP))
	{
		header_t *header = loadBTreeHeader();
		long rrn = writeStudentToFile(STUDENTDATABASEFILENAME,student);

		FILE * indexFile = openFile(INDEXFILENAME,"r+b");
		FILE * studentFile = openFile(STUDENTDATABASEFILENAME,"r+b");

		//Root is empty
		if(header->rootNodeRRN == -1)
		{
			//printf("Case empty root\n");
			caseEmptyRoot(header,indexFile,student,rrn);
			
		}else if(header->nodesNumber == 1){
			//Root is a leaf

			node_t *rootNode = (node_t *) malloc(sizeof(node_t));
			fseek(indexFile, header->rootNodeRRN, SEEK_SET);
			fread(rootNode, sizeof(node_t), 1, indexFile);
			
			//without overflow
			if (rootNode->nodeSize < header->order-1) {
				//printf("caseRootIsLeafWithoutOveflow \n");
				caseRootIsLeafWithoutOveflow(rootNode,indexFile,student.nUSP,rrn,header);
				
			//with overflow
			}else{
				//printf("caseRootIsLeafWithOveflow\n");
				caseRootIsLeafWithOveflow(rootNode,indexFile,student,rrn,header);
			}
			free(rootNode);
			//caseRootIsLeaf(header,indexFile,student,rrn);
		}else if(header->nodesNumber != 1){
			node_t *rootNode = (node_t *) malloc(sizeof(node_t));
			fseek(indexFile, header->rootNodeRRN, SEEK_SET);
			fread(rootNode, sizeof(node_t), 1, indexFile);
			
			//printf("moreThanOneLeaf\n");
			moreThanOneLeaf(rootNode,indexFile,student,rrn,header);

			free(rootNode);
		
		}	

		recordBTreeHeader(header, indexFile);
		free(header);
		fclose(studentFile);
		fclose(indexFile);
	}else{
		printf("O Registro ja existe!\n");
	}
	
	
	
	
}

node_t * createNewNode(header_t *header){
	
	int i;
	//Allocating memory for the node
	node_t *newNode = (node_t *) malloc(sizeof(node_t));
	header->nodesNumber++;
	newNode->nodeSize = 0;
	
	//Setting null values (-1) to all keys in brand new node
	for (i=0; i < (header->order-1); i++) {
		newNode->keyVector[i] = (long int) -1;
		newNode->dataRrnVector[i] = (long int) -1;
		newNode->childrenVector[i] = (long int) -1;
	}
	newNode->childrenVector[header->order-1] = (long int) -1;

	return newNode;
}	

long searchOnBtree(int nUSP){
	header_t *header = loadBTreeHeader();
	int nodePosition = header->rootNodeRRN;

	FILE * filePointer = openFile(INDEXFILENAME,"r+b");

	// node_t *rootNode = (node_t *) malloc(sizeof(node_t));
	// fseek(filePointer, nodePosition, SEEK_SET);
	// fread(rootNode, sizeof(node_t), 1, filePointer);
	
	// printf("procurando nusp %d\n", nUSP);
	// printf("começando pela raiz \n");
	// printNode(rootNode);
	student_t student;
	while(nodePosition != -1){
		node_t *iterativeNode = (node_t *) malloc(sizeof(node_t));
		fseek(filePointer, nodePosition, SEEK_SET);
		fread(iterativeNode, sizeof(node_t), 1, filePointer);

		//if its not a leaf
		//printf("procurando %d em \n", nUSP);
		//printNode(iterativeNode);
		if (iterativeNode->keyVector[0] > nUSP)
		{
			nodePosition = iterativeNode->childrenVector[0];
		}else
		{
			for(int i=header->order-2;i>=0;i--){
				if (iterativeNode->keyVector[i] == nUSP)
				{
					//printf("True\n");
					
					long rrn = iterativeNode->dataRrnVector[i];
					//printNode(iterativeNode);
					
					// printf("RRN na funcao %ld\n", rrn);
					// printf("RRN no vetor %ld\n", iterativeNode->dataRrnVector[i]);
					// printf("nUSP na funcao %ld\n", iterativeNode->keyVector[i]);
					fclose(filePointer);
					free(iterativeNode);
					return rrn;
					
				}				
				if(iterativeNode->keyVector[i] != -1 && (iterativeNode->keyVector[i] < nUSP)){
					nodePosition = iterativeNode->childrenVector[i+1];
					break;
				}
			}
		}
		//printf("next node %d\n", nodePosition);
		free(iterativeNode);
	}
	//printf("False\n");
	free(header);
	//free(rootNode);
	fclose(filePointer);
	return -1;
}

student_t getStudentFromFile(long rrn){
	FILE * filePointer = openFile(STUDENTDATABASEFILENAME,"r+b");
	
	student_t student;
	fseek(filePointer, rrn, SEEK_SET);
	fread(&student, sizeof(student_t), 1, filePointer);

	fclose(filePointer);
	return student;
}

void updateOnFile(int rrn, student_t modifiedStudent){
	FILE * filePointer = openFile(STUDENTDATABASEFILENAME,"r+b");
	
	fseek(filePointer, rrn, SEEK_SET);
	fwrite(&modifiedStudent, sizeof(student_t), 1, filePointer);

	fclose(filePointer);
}
