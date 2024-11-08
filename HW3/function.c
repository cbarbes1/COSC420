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


struct node *CreateNode()
{
    struct node *node = (struct node *)malloc(sizeof(struct node));
    node->val = (double)rand() / RAND_MAX;
    node->l = NULL;
    node->r = NULL;
    return node;
}

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

// traverse the tree
int BTTraverseCountl(struct node *nodeptr)
{
	if(nodeptr != NULL){
		int count = BTTraverseCountl(nodeptr->l);
		count = count + BTTraverseCountl(nodeptr->r);
		if(nodeptr->val < 0.5){
			count = count + 1;
		}

		return count;
	}else {
		return 0;
	}
}

int main(){
    int count = (2000- 7)/8;
    struct node *head = CreateNode();
    for(int i = 0; i < 8; i++){
        struct node *ptr = CreateNode();
        insert(&head, &ptr);
    }

    #pragma omp parallel for
    for(int k = 0; k < 8; k++){
        struct node *localHead = CreateNode();
        for(int i = 0; i < count-1; i++){
            struct node *ptr = CreateNode();
            insert(&localHead, &ptr);
        }

        #pragma omp critical
        {
            insert(&head, &localHead);
        }
    }

    int num_nodes = BTTraverseCountl(head);

    printf("Here is the size of the tree  with value less than 0.5 %d \n", num_nodes);



    delete(head);
}