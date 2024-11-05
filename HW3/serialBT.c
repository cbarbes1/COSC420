/* Author: Cole Barbes
 * Creation Date: 11/03/24
 * Last Edited: 11/03/24
 * Purpose: Implement a binary tree to traverse through
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// node structure
struct node {
	float val;
	struct node* l;
	struct node* r;
};

// insert value into the tree iteratively
struct node* BTInsert(struct node *head, float value)
{

	// if head is null
	if(head == NULL){
		head = (struct node *)malloc(sizeof(struct node));
		head->val = value;
		head->l = NULL;
		head->r = NULL;

		return head;
	}
	
	// save head into ptr var
	struct node *ptr = head;
	struct node *prev = NULL;

	// loop through until the ptr is null
	while(ptr != NULL){
		prev = ptr;

		// check if need to traverse left or right
		if(ptr->val > value){
			ptr = ptr->l;
		}else{
			ptr = ptr->r;
		}

	}

	// put the value in the place
	ptr = (struct node *)malloc(sizeof(struct node));
	ptr->val = value;
	ptr->l = NULL;
	ptr->r = NULL;


	// use the previous pointer to set the node into the tree
	if(prev->val > value){
		prev->l = ptr;
	}else{
		prev->r = ptr;
	}
	
	return ptr;
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

// construct the tree
struct node* BTConstruction(int num_nodes)
{
	struct node *head = NULL;
	struct node *ptr = NULL;
	for(int i = 0; i<num_nodes; i++){
		if(head == NULL){
			head = BTInsert(head, (float)rand()/RAND_MAX);
		}else{
			ptr = BTInsert(head, (float)rand()/RAND_MAX);
		}
	}
	return head;
}

// traverse the tree
int BTTraverse(struct node *nodeptr)
{
	if(nodeptr != NULL){
		int count = BTTraverse(nodeptr->l);
		count = count + BTTraverse(nodeptr->r);

		if(nodeptr->val < 0.5){
			count = count +1;
		}

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

	struct node *ptr = BTConstruction(num_nodes);

	int result = BTTraverse(ptr);
	
	printf("There are %d nodes in the tree less than 0.5\n", result);
	print(ptr);

	delete(ptr);
	return 0;

}
