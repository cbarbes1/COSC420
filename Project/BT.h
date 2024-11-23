/////////////////////////////////////////////////////////////////////////////////////////////
//          Author: C++ameron Vinson, Cole Barbes, Sunny Malloy, Spencer Presley           //
//                                 Creation Date: 11/18/2024                               //
//                                  Last Update: 11/18/2024                                //
//                                                                                         //
//                If you are not Cameron, Cole, Sunny, Spencer or Dr. Jing,                //
//                         close this file and directory immediately!                      //
//                Do not copy and paste this code.  Do your HW on your own.                //
//                                                                                         //
//                   Description: Header file for Binary Tree functions                    //
//                                                                                         //
//                                   User Interface: None                                  //
//                                                                                         //
//                                        Notes: None                                      //
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef BT_H
#define BT_H

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct data {
    int id;
    char *model;
    int year_make;
    char *color;
    int price;
    char *dealer;
} Data;

typedef struct node {
    Data val;
    struct node* l;
    struct node* r;
} TreeNode;

typedef struct tree {
	TreeNode *root;


} Tree;

void BTConstructions(Tree *Btree);

void BTFree(Tree*Btree);

// Helper Functions
void insert(TreeNode **nodePtr, TreeNode **newNode);

void destroySubTree(TreeNode *nodePtr);

void makeDeletion(TreeNode **nodePtr);

void deleteNode(Data num, TreeNode **nodePtr);

void displayInOrder(TreeNode *nodePtr);

void displayPreOrder(TreeNode *nodePtr);

void displayPostOrder(TreeNode *nodePtr);

void IndentBlock(int num);

void PrintTree(TreeNode *t, int Indent, int Level);

// Binary tree operations
void insertNode(Tree *Btree, Data num);

int searchNode(Tree *Btree, Data num);

void delete(Tree *Btree, Data num);

void InOrder(Tree *Btree);

void PreOrder(Tree *Btree);

void PostOrder(Tree *Btree);

void print(Tree *Btree, int Indent, int Level);

void LeftRotation(TreeNode **nodePtr);

void RightRotation(TreeNode **nodePtr);

void CreateBackboneRec(TreeNode **nodePtr);

int CountNodes(TreeNode *nodePtr);

void CreateBalanceRec(TreeNode **nodePtr, int count, int stop);

int heightHelper(TreeNode *nodePtr);

void balance(Tree *Btree);

int count(Tree *Btree);

int height(Tree *Btree);

#endif
