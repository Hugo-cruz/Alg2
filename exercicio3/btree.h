#ifndef BTREE_H_
#define BTREE_H_

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "Student.h"


#define PAGESIZE 4096
#define TREEHEADER PAGESIZE
#define MAXKEYS 204
#define ORDER 204

typedef struct node_t{
	int nodeSize;
	long int keyVector[ORDER-1];
	long int dataRrnVector[ORDER-1];
	long int childrenVector[ORDER];
} node_t;

typedef struct header_t {
	int nodesNumber;
	int order;
	long int rootNodeRRN;
} header_t;

typedef struct item_to_promote_t {
    int keyToPromote, rrnToPromote;
	long leftChildRRN, rigthChildRRN;
    bool hasValue;
} item_to_promote_t;

header_t * loadBTreeHeader();
void recordBTreeHeader(header_t*, FILE*);
node_t * createNewNode(header_t *);
void insertStudentOnTree(student_t);

//Cases insert
void caseEmptyRoot(header_t *, FILE*, student_t, long);
void caseRootIsLeafWithoutOveflow(node_t *, FILE*, int, long, header_t *);
void caseRootIsLeafWithOveflow(node_t *, FILE*, student_t, long, header_t *);
void moreThanOneLeaf(node_t *, FILE*, student_t, long, header_t *);

//helper on moreThanOneLeaf
item_to_promote_t insertOnTreeWithOverflowHandler(int, FILE*, int, long, header_t *);
item_to_promote_t insertOnLeafWithOveflow(node_t*, FILE*, int, long, header_t *);
void insertOnLeafWithoutOveflow(node_t*, FILE*, int, long, header_t *, int);
item_to_promote_t insertOnNotLeafWithoutOverflow(node_t*,int, FILE*, item_to_promote_t, header_t *);
item_to_promote_t insertOnNotLeafWithOverflow(node_t*,int, FILE*, item_to_promote_t, header_t *);

//Search
bool checkExistOnBtree(int);
long searchOnBtree(int);
student_t getStudentFromFile(long);

//Update
void updateOnFile(int,student_t);

//helpers
void printNode(node_t *);



#endif 