/* Author: Cole Barbes
 * Creation Date: 11/03/24
 * Last Edited: 11/03/24
 * Purpose: Implement a binary tree to traverse through
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// node structure
struct node {
	float val;
	struct node* l;
	struct node* r;
};

// insert value into the tree iteratively
void BTInsert(struct node **head, float value) {

	static long int num_nodes = 0; 
    // If head is null, create the root node
    if (*head == NULL) {
        *head = (struct node *)malloc(sizeof(struct node));
        (*head)->val = value;
        (*head)->l = NULL;
        (*head)->r = NULL;
		num_nodes++;
    }else{

		// Queue for level-order traversal
		struct node **queue = (struct node **)malloc(num_nodes * sizeof(struct node *));
		int front = 0, back = 0;
		queue[back++] = *head;
		int done = 0;

		while (front < back && done != 1) {
			struct node *ptr = queue[front++];
			// Check left child
			if (ptr->l == NULL) {
				ptr->l = (struct node *)malloc(sizeof(struct node));
				ptr->l->val = value;
				ptr->l->l = NULL;
				ptr->l->r = NULL;
				num_nodes++;
				done = 1;
			}else if (ptr->r == NULL) {
				ptr->r = (struct node *)malloc(sizeof(struct node));
				ptr->r->val = value;
				ptr->r->l = NULL;
				ptr->r->r = NULL;
				num_nodes++;
				done = 1;
			} else {
				queue[back++] = ptr->l;
				queue[back++] = ptr->r;
			}
			
		}

		// Free the queue
		free(queue);
	}
}


struct node *CreateSubtreeRec(struct node *ptr, int depth, int max_depth)
{
	if(depth == max_depth){
		return NULL;
	}

	depth++;
	if(ptr == NULL){

		ptr = (struct node *)malloc(sizeof(struct node));
		ptr->val = (double)rand() / RAND_MAX;
		ptr->l = NULL;
		ptr->r = NULL;
	

		if(ptr->l == NULL){
			ptr->l = CreateSubtreeRec(ptr->l, depth, max_depth);
		}
		if(ptr->r == NULL){
			ptr->r = CreateSubtreeRec(ptr->r, depth, max_depth);
		}
	}
	return ptr;
}

struct node *CreateSubtree(int depth, int max_depth)
{
	struct node *ptr = NULL;
	ptr = CreateSubtreeRec(ptr, depth, max_depth);

	ptr = CreateSubtreeRec(ptr, depth, max_depth);
}

// delete the tree
void delete(struct node *nodeptr)
{
	if(nodeptr != NULL){
		// save left and right nodes before clearing the memory
		struct node *templ = nodeptr->l;
		struct node *tempr = nodeptr->r;
		free(nodeptr);
		delete(templ);
		delete(tempr);
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

/*
struct node* BTConstructionParallel(int num_nodes, int num_threads)
{
	struct node *head = NULL;
	for(int i = 0; i < log2(num_threads); i++){
		InsertRec(&head, (double)rand() / RAND_MAX);
	}
}

// construct the tree
struct node* BTConstruction(int num_nodes)
{
	struct node *head = NULL;
	struct node *ptr = NULL;
	for(int i = 0; i<num_nodes; i++){
		BTInsert(&head, (float)rand()/RAND_MAX);
	}
	return head;
}
*/
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

int main(int argc, char **argv)
{

	if(argc != 2){
		printf("Insufficient Arguments\n");
		exit(1);
	}
	srand(time(NULL));

	int num_nodes = atoi(argv[1]);

	struct node *ptr = CreateSubtree(0, log2(num_nodes));

	int result = BTTraverseCount(ptr);
	//print(ptr);	
	printf("There are %d nodes in the tree\n", result);

	delete(ptr);
	return 0;

}
