/* Author: Cole Barbes
 * Creation Date: 11/03/24
 * Last Edited: 11/03/24
 * Purpose: Implement a binary tree to traverse through
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

	return ptr;
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

// struct node **getleafs(struct node *root, struct node **nodelist, int *index)
// {

// 	if(root->l == NULL && root->r == NULL){
// 		nodelist[*index] = root->l;
// 		return nodelist;
// 	}else{
// 		getleafs(root->l, nodelist, (*index)++);
// 		getleafs(root->r, nodelist, (*index)++);
// 		return nodelist;
// 	}
// }

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

struct node *insertNode(struct node *node, struct node *newnode)
{
	if(node == NULL) {
		return NULL;
	}else if(node->l == NULL){
		node->l = newnode;
		return node;
	}else if(node->r == NULL){
		node->r = newnode;
		return node;
	}else{
		if(node->val < newnode->val){
			return insertNode(node->l, newnode);
		}else{
			return insertNode(node->r, newnode);
		}
	}
}



struct node* BTConstructionParallel(int num_nodes, int num_threads)
{
	struct node *head = NULL;

	head = CreateSubtree(0, log2(num_threads));
	int Success = 0;

	omp_set_num_threads(num_threads);
	#pragma omp parallel for 
	for(int i = 0; i<num_threads; i++){
		struct node *ptr = NULL;
		int treesize = log2(num_nodes) - log2(num_threads);
		ptr = CreateSubtree(0, treesize);

		printf("%d\n", BTTraverseCount(head));

		#pragma omp critical
		{
			head = insertNode(head, ptr);
		}
		
	}

	return head;
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
	

	// Recursively create left and right subtrees
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			nodeptr->l = CreateTree(nodeptr->l, num_nodes, depth + 1);
		}
		#pragma omp section
		{
			nodeptr->r = CreateTree(nodeptr->r, num_nodes, depth + 1);
		}
	}
	
    return nodeptr;
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



int main(int argc, char **argv)
{

	if(argc != 2){
		printf("Insufficient Arguments\n");
		exit(1);
	}
	srand(time(NULL));

	int num_nodes = atoi(argv[1]);

	struct node *ptr = CreateTree(ptr, num_nodes, 0);

	int result = BTTraverseCount(ptr);
	//print(ptr);	
	printf("There are %d nodes in the tree\n", result);

	delete(ptr);
	return 0;

}
