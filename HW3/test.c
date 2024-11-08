#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;

// Function to create a new node
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Recursive function to build the binary tree
Node* buildTree(int depth) {
    if (depth <= 0) {
        return NULL;
    }

    Node* node = createNode(depth);

    // Parallel creation of left and right subtrees
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            node->left = buildTree(depth - 1);
        }
        
        #pragma omp section
        {
            node->right = buildTree(depth - 1);
        }
    }

    return node;
}

// Function to print the tree (in-order traversal for demonstration)
void printTree(Node* root) {
    if (root == NULL) {
        return;
    }
    printTree(root->left);
    printf("%d ", root->value);
    printTree(root->right);
}

int main() {
    int depth = 4; // Depth of the tree
    Node* root;

    #pragma omp parallel
    {
        #pragma omp single
        {
            root = buildTree(depth);
        }
    }

    printf("In-order traversal of the binary tree:\n");
    printTree(root);
    printf("\n");

    return 0;
}
