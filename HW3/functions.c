/* Author: Cole Barbes
* Purpose: binary tree functions
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>


// node structure
struct node {
	float val;
	struct node* l;
	struct node* r;
};


// create the node
struct node *CreateNode()
{
    struct node *node = (struct node *)malloc(sizeof(struct node));
    node->val = (double)rand() / RAND_MAX;
    node->l = NULL;
    node->r = NULL;
    return node;
}


// insert the value
struct node *insertVal(struct node *nodePtr, float value) {    // Insert the node.
    if(nodePtr != NULL){
        if(nodePtr->val < value){
            nodePtr = insertVal(nodePtr->l, value);
        }else{
            nodePtr = insertVal(nodePtr->r, value);
        }
    }else{
        struct node *node = (struct node *)malloc(sizeof(struct node));
        node->val = value;
        node->l = NULL;
        node->r = NULL;
        return node;
    }
}

// insert a node
void insert(struct node **nodePtr, struct node **newNode) {
	if (*nodePtr == NULL){
		*nodePtr = *newNode;     
    }             // Insert the node.
	else if ((*newNode)->val < (*nodePtr)->val){
		insert(&(*nodePtr)->r, newNode);     // Search the left branch
    }
	else{
		insert(&(*nodePtr)->r, newNode);    // Search the right branch
    }
}

// delete the tree
void delete(struct node *nodeptr)
{
	if(nodeptr != NULL){
		// save left and right nodes before clearing the memory
		delete(nodeptr->l);
		delete(nodeptr->r);
		
		free(nodeptr);
		
	}
}

// print the tree with a count variable to avoid too deep of a print
void print(struct node *nodeptr){
	if(nodeptr != NULL){
		printf("%f ", nodeptr->val);
		print(nodeptr->l);
		print(nodeptr->r);
	}
}


// traverse the tree
int BTTraverseCount(struct node *nodeptr)
{
	if(nodeptr != NULL){
		int count = BTTraverseCount(nodeptr->l);
		count = count + BTTraverseCount(nodeptr->r);
		count = count + 1;
		return count;
	}else {
		return 0;
	}
}

//serial Functions
// traverse the tree
int BTTraverseCountl(struct node *nodeptr)
{

    if(nodeptr == NULL){
        return 0;
    }
    int count = 0, count1 = 0, count2 = 0;
    count1 = BTTraverseCountl(nodeptr->l);
    count2 =  BTTraverseCountl(nodeptr->r);
    if(nodeptr->val < 0.5){
        count = 1;
    }
    return count+count1+count2;
}

// Recursive function to create a binary tree
struct node *CreateTree(struct node *nodeptr, int num_nodes, int depth) {
    if (depth >= ((int)log2(num_nodes))) {
        return nodeptr;
    }

    // Allocate and initialize the node
    nodeptr = (struct node *)malloc(sizeof(struct node));
    if (nodeptr == NULL) {
        perror("Failed to allocate node");
        exit(1);
    }
    nodeptr->val = (double)rand() / RAND_MAX;
    nodeptr->l = NULL;
    nodeptr->r = NULL;
	

	nodeptr->l = CreateTree(nodeptr->l, num_nodes, depth + 1);
	nodeptr->r = CreateTree(nodeptr->r, num_nodes, depth + 1);
	
    return nodeptr;
}
