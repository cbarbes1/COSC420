/////////////////////////////////////////////////////////////////////////////////////////////
//          Author: C++ameron Vinson, Cole Barbes, Sunny Malloy, Spencer Presley           //
//                                 Creation Date: 10/29/2024                               //
//                                  Last Update: 11/05/2024                                //
//                                                                                         //
//                If you are not Cameron, Cole, Sunny, Spencer or Dr. Jing,                //
//                         close this file and directory immediately!                      //
//                Do not copy and paste this code.  Do your HW on your own.                //
//                                                                                         //
//               Description: Implementation file for Binary Tree functions                //
//                                                                                         //
//                                   User Interface: None                                  //
//                                                                                         //
//                                        Notes: None                                      //
/////////////////////////////////////////////////////////////////////////////////////////////

#include "BT.h"

/********************************************************************
*                                                                   *
* Description: BTConstructions constructs the Binary Tree.          *
* The root is initialized to NULL.                                  *
*                                                                   *
* Parameters:                                                       *
* *Btree - Binary Tree to call this function on.                    *
*                                                                   *
* Return: None                                                      *
*                                                                   *
********************************************************************/
void BTConstructions(Tree *Btree) {
    Btree->root = NULL;
}

/********************************************************************
*                                                                   *
* Description: insert accepts a TreeNode pointer and a pointer to a *
* node.                                                             *
* The function inserts the node into the tree pointed to by         *
* the TreeNode pointer. This function is called recursively.        *
*                                                                   *
* Parameters:                                                       *
* **nodePtr - current node in the tree.                             *
* **newNode - new node to be added into the tree.                   *
*                                                                   *
* Return: None                                                      *
*                                                                   *
********************************************************************/
void insert(TreeNode **nodePtr, TreeNode **newNode) {
    if (*nodePtr == NULL)
        *nodePtr = *newNode;                  // Insert the node.
    else if ((*newNode)->val.id < (*nodePtr)->val.id)
        insert(&(*nodePtr)->l, newNode);     // Search the left branch
    else
        insert(&(*nodePtr)->r, newNode);    // Search the right branch
}

/********************************************************************
*                                                                   *
* Description: insertNode creates a new node to hold num as its     *
* value, and passes it to the insert function.                      *
*                                                                   *
* Parameters:                                                       *
* *Btree - Binary Tree to call this function on.                    *
* num - value to insert.                                            *
*                                                                   *
* Return: None                                                      *
*                                                                   *
********************************************************************/
void insertNode(Tree *Btree, Data num) {
	TreeNode *newNode = NULL;	// Pointer to a new node.

	// Create a new node and store num in it.
	newNode = (TreeNode*)malloc(sizeof(TreeNode));
	newNode->val = num;
	newNode->l = newNode->r = NULL;

	// Insert the node.
	insert(&Btree->root, &newNode);
}

/********************************************************************
*                                                                   *
* Description: destroySubTree is called by BTFree. It deletes all   *
* nodes in the tree.                                                *
*                                                                   *
* Parameters:                                                       *
* *nodePtr - current node in the tree.                              *
*                                                                   *
* Return: None                                                      *
*                                                                   *
********************************************************************/
void destroySubTree(TreeNode *nodePtr) {
	if (nodePtr) {
		if (nodePtr->l)
			destroySubTree(nodePtr->l);
		if (nodePtr->r)
			destroySubTree(nodePtr->r);
		free(nodePtr);
	}
}

/********************************************************************
*                                                                   *
* Description: searchNode determines if a value is present in       *
* the tree. If so, the function returns 1.                          *
* Otherwise, it returns 0.                                          *
*                                                                   *
* Parameters:                                                       *
* *Btree - Binary Tree to call this function on.                    *
* num - value to search for.                                        *
*                                                                   *
* Return: 1 is true and 0 is false.                                 *
*                                                                   *
********************************************************************/
int searchNode(Tree *Btree, Data num) {
	TreeNode *nodePtr = Btree->root;

	while (nodePtr) {
		if (nodePtr->val.id == num.id)
			return 1;
		else if (num.id < nodePtr->val.id)
			nodePtr = nodePtr->l;
		else
			nodePtr = nodePtr->r;
	}
	return 0;
}

/********************************************************************
*                                                                   *
* Description: delete calls deleteNode to delete the node whos      *
* value member is the same as num.                                  *
*                                                                   *
* Parameters:                                                       *
* *Btree - Binary Tree to call this function on.                    *
* num - value to delete.                                            *
*                                                                   *
* Return: None                                                      *
*                                                                   *
********************************************************************/
void delete(Tree *Btree, Data num) {
	deleteNode(num, &Btree->root);
}

/********************************************************************
*                                                                   *
* Description: deleteNode deletes the node whose value member is    *
* the same as num.                                                  *
*                                                                   *
* Parameters:                                                       *
* num - value to delete.                                            *
* **nodePtr - current node in the tree.                             *
*                                                                   *
* Return: None                                                      *
*                                                                   *
********************************************************************/
void deleteNode(Data num, TreeNode **nodePtr) {
	if (*nodePtr == NULL) {
		return;
	}
	
	if (num.id < (*nodePtr)->val.id)
		deleteNode(num, &(*nodePtr)->l);
	else if (num.id > (*nodePtr)->val.id)
		deleteNode(num, &(*nodePtr)->r);
	else
		makeDeletion(nodePtr);
}

/********************************************************************
*                                                                   *
* Description: makeDeletion takes a reference to a pointer to the   *
* node that is to be deleted. The node is removed and the           *
* branches of the tree below the node are reattached.               *
*                                                                   *
* Parameters:                                                       *
* **nodePtr - current node in the tree.                             *
*                                                                   *
* Return: None                                                      *
*                                                                   *
********************************************************************/
void makeDeletion(TreeNode **nodePtr) {
	// Define a temporary pointer to use in reattaching
	// the left subtree.
	TreeNode *temp = NULL;

	if (*nodePtr == NULL) {
		printf("Cannot delete empty node.\n");
        return;
    }
	else if ((*nodePtr)->r == NULL) {
		temp = *nodePtr;
		*nodePtr = (*nodePtr)->l;   // Reattach the left child
	} else if ((*nodePtr)->l == NULL) {
		temp = *nodePtr;
		*nodePtr = (*nodePtr)->r;  // Reattach the right child
	}
	// If the node has two children.
	else {
		// Move one node the right.
		temp = (*nodePtr)->r;
		// Go to the end left node.
		while (temp->l)
			temp = temp->l;
		// Reattach the left subtree.
		temp->l = (*nodePtr)->l;
		temp = *nodePtr;
		// Reattach the right subtree.
		*nodePtr = (*nodePtr)->r;
	}
    free(temp);
}

/********************************************************************
*                                                                   *
* Description: The displayInOrder function displays the values      *
* in the subtree pointed to by nodePtr, via inorder traversal.      *
*                                                                   *
* Parameters:                                                       *
* *nodePtr - current node in the tree.                              *
*                                                                   *
* Return: None                                                      *
*                                                                   *
********************************************************************/
void displayInOrder(TreeNode *nodePtr) {
	if (nodePtr) {
		displayInOrder(nodePtr->l);
		printf("%d\n", nodePtr->val.id);
		displayInOrder(nodePtr->r);
	}
}

/********************************************************************
*                                                                   *
* Description: InOrder calls displayInOrder.                        *
*                                                                   *
* Parameters:                                                       *
* *Btree - Binary Tree to call this function on.                    *
*                                                                   *
* Return: None                                                      *
*                                                                   *
********************************************************************/
void InOrder(Tree *Btree) {
    displayInOrder(Btree->root);
}

/********************************************************************
*                                                                   *
* Description: The displayPreOrder function displays the values     *
* in the subtree pointed to by nodePtr, via preorder traversal.     *
*                                                                   *
* Parameters:                                                       *
* *nodePtr - current node in the tree.                              *
*                                                                   *
* Return: None                                                      *
*                                                                   *
********************************************************************/
void displayPreOrder(TreeNode *nodePtr) {
	if (nodePtr) {
		printf("%d\n", nodePtr->val.id);
		displayPreOrder(nodePtr->l);
		displayPreOrder(nodePtr->r);
	}
}

/********************************************************************
*                                                                   *
* Description: PreOrder calls displayPreOrder.                      *
*                                                                   *
* Parameters:                                                       *
* *Btree - Binary Tree to call this function on.                    *
*                                                                   *
* Return: None                                                      *
*                                                                   *
********************************************************************/
void PreOrder(Tree *Btree) {
    displayPreOrder(Btree->root);
}

/********************************************************************
*                                                                   *
* Description: The displayPostOrder function displays the values    *
* in the subtree pointed to by nodePtr, via postorder traversal.    *
*                                                                   *
* Parameters:                                                       *
* *nodePtr - current node in the tree.                              *
*                                                                   *
* Return: None                                                      *
*                                                                   *
********************************************************************/
void displayPostOrder(TreeNode *nodePtr) {
	if (nodePtr) {
		displayPostOrder(nodePtr->l);
		displayPostOrder(nodePtr->r);
		printf("%d\n", nodePtr->val.id);
	}
}

/********************************************************************
*                                                                   *
* Description: PostOrder calls displayPostOrder.                    *
*                                                                   *
* Parameters:                                                       *
* *Btree - Binary Tree to call this function on.                    *
*                                                                   *
* Return: None                                                      *
*                                                                   *
********************************************************************/
void PostOrder(Tree *Btree) {
    displayPostOrder(Btree->root);
}

/********************************************************************
*                                                                   *
* Description: Simple helper function to do the indentations for    * 
* the tree printing algorithm.                                      *
*                                                                   *
* Parameters:                                                       *
* num - number of spaces to print out for the indentations.         *
*                                                                   *
* Return: None                                                      *
*                                                                   *
********************************************************************/
void IndentBlock(int num) {
	for (int i = 0; i < num; i++)
		printf(" ");
}

/********************************************************************
*                                                                   *
* Description: This function recursively prints the tree contents   *
* to the console using a reverse inorder traversal with indenting.  *
*                                                                   *
* Parameters:                                                       *
* *nodePtr - current node in the tree.                              *
* Indent - number of spaces between each level.                     *
* Level - current level in the tree.  Root is starting level.       *
*                                                                   *
* Return: None                                                      *
*                                                                   *
********************************************************************/
void PrintTree(TreeNode *nodePtr, int Indent, int Level) {
	if (nodePtr != NULL) {
		PrintTree(nodePtr->r, Indent, Level + 1);
		IndentBlock(Indent * Level);
		printf("%d\n", nodePtr->val.id);
		PrintTree(nodePtr->l, Indent, Level + 1);
	}
}

/********************************************************************
*                                                                   *
* Description: This function initiates the recursive printing       *
* function to print the contents of the tree in tree form sideways  *
* with the root at the far left.                                    *
*                                                                   *
* Parameters:                                                       *
* *Btree - Binary Tree to call this function on.                    *
* Indent - number of spaces between each level.                     *
* Level - Starting level for root.                                  *
*                                                                   *
* Return: None                                                      *
*                                                                   *
********************************************************************/
void print(Tree *Btree, int Indent, int Level) { // tree, 4, 0
	if (Btree != NULL)
		PrintTree(Btree->root, Indent, Level);
}

/********************************************************************
*                                                                   *
* Description: BTFree destructs the Binary Tree.                    *
* The malloc memory is freed up when this is called.                *
* It calls destroySubTree on the root to delete every node in the   *
* binary tree in order to free the memory.                          *
*                                                                   *
* Parameters:                                                       *
* *Btree - Binary Tree to call this function on.                    *
*                                                                   *
* Return: None                                                      *
*                                                                   *
********************************************************************/
void BTFree(Tree *Btree) {
    destroySubTree(Btree->root);
    Btree->root = NULL;
}

/********************************************************************
*                                                                   *
* Description: Finds the height of the tree starting at the root.   *
*                                                                   *
* Parameters:                                                       *
* *Btree - Binary Tree to call this function on.                    *
*                                                                   *
* Return: None                                                      *
*                                                                   *
********************************************************************/
int height(Tree *Btree) {
	return heightHelper(Btree->root);
}

/********************************************************************
*                                                                   *
* Description: Finds the height of the tree starting at the pointer *
* nodePtr.                                                          *
*                                                                   *
* Parameters:                                                       *
* *nodePtr - current node in the tree.                              *
*                                                                   *
* Return: None                                                      *
*                                                                   *
********************************************************************/
int heightHelper(TreeNode *nodePtr) {
	if (!nodePtr) {
		return 0;
	}
	
	int L = heightHelper(nodePtr->l);
	int R = heightHelper(nodePtr->r);

	if (L > R) {
		return L + 1;
	}
	return R + 1;
}

/********************************************************************
*                                                                   *
* Description: Counts the number of nodes in a binary tree starting *
* at the root.                                                      *
*                                                                   *
* Parameters:                                                       *
* *Btree - Binary Tree to call this function on.                    *
*                                                                   *
* Return: None                                                      *
*                                                                   *
********************************************************************/
int count(Tree *Btree) {
	return CountNodes(Btree->root);
}

/********************************************************************
*                                                                   *
* Description: Recursively counts the number of nodes in a binary   *
* tree starting at the pointer nodePtr.                             *
*                                                                   *
* Parameters:                                                       *
* *nodePtr - current node in the tree.                              *
*                                                                   *
* Return: None                                                      *
*                                                                   *
********************************************************************/
int CountNodes(TreeNode *nodePtr) {
	if (!nodePtr) {
		return 0;
	}

	int L = CountNodes(nodePtr->l);
	int R = CountNodes(nodePtr->r);

	return L + R + 1;
}

/********************************************************************
*                                                                   *
* Description: Does a right rotation about nodePtr.                 *
*                                                                   *
* Parameters:                                                       *
* **nodePtr - current node in the tree.                             *
*                                                                   *
* Return: None                                                      *
*                                                                   *
********************************************************************/
void RightRotation(TreeNode **nodePtr) {
	TreeNode *L = (*nodePtr)->l;
	TreeNode *temp = L->r;
	L->r = *nodePtr;
	(*nodePtr)->l = temp;
	*nodePtr = L;
}

/********************************************************************
*                                                                   *
* Description: Does a left rotation about nodePtr.                  *
*                                                                   *
* Parameters:                                                       *
* **nodePtr - current node in the tree.                             *
*                                                                   *
* Return: None                                                      *
*                                                                   *
********************************************************************/
void LeftRotation(TreeNode **nodePtr) {
	TreeNode *R = (*nodePtr)->r;
	TreeNode *temp = R->l;
	R->l = *nodePtr;
	(*nodePtr)->r = temp;
	*nodePtr = R;
}

/********************************************************************
*                                                                   *
* Description: Recursively reforms the tree into a "backbone".      *
* That is, a linked list to the right child where the values will   *
* be ordered.                                                       *
*                                                                   *
* Parameters:                                                       *
* **nodePtr - current node in the tree.                             *
*                                                                   *
* Return: None                                                      *
*                                                                   *
********************************************************************/
void CreateBackboneRec(TreeNode **nodePtr) {
	while ((*nodePtr)->l) {
		RightRotation(nodePtr);
	}

	if ((*nodePtr)->r)
		CreateBackboneRec(&(*nodePtr)->r);
}

/********************************************************************
*                                                                   *
* Description: Recursive version of an iterative that rotates left  *
* at each right child, stop number of times, assuming count is      *
* initially called at 1.                                            *
*                                                                   *
* Parameters:                                                       *
* **nodePtr - current node in the tree.                             *
*                                                                   *
* Return: None                                                      *
*                                                                   *
********************************************************************/
void CreateBalanceRec(TreeNode **nodePtr, int count, int stop) {
	if (count > stop) {
		return;
	}

	LeftRotation(nodePtr);
	CreateBalanceRec(&(*nodePtr)->r, count + 1, stop);
}

/********************************************************************
*                                                                   *
* Description: DSW (Colin Day, Quentin F. Stout, and                *
* Bette L. Warren) tree balancing algorithm                         *
* the first creates a backbone of the tree, then using              *
* left rotations forms a perfectly balanced tree.                   *
*                                                                   *
* Parameters:                                                       *
* **nodePtr - current node in the tree.                             *
*                                                                   *
* Return: None                                                      *
*                                                                   *
********************************************************************/
void balance(Tree *Btree) {
	if (!Btree->root)
		return;

	CreateBackboneRec(&Btree->root);

	int n = CountNodes(Btree->root);
	// 0.5 trick to round.
	int m = (int)(pow(2, floor(log(n + 1) / log(2))) - 1 + 0.5);

	if (Btree->root->r) {
		CreateBalanceRec(&Btree->root, 1, n - m);
		while (m > 1) {
			m = m / 2;
			CreateBalanceRec(&Btree->root, 1, m);
		}
	}
}
