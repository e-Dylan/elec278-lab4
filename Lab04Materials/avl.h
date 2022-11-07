// AVL.H - ELEC278 Lab 4
//


#include <stdlib.h>
#include <stdio.h>


// Prototypes for functions found in AVL.C

// Create new node with key=k, value=v and insert it into tree. Returns 1 on
// success, 0 on failure
pNode insertNodeAVL(Key k, void *v, pNode root);

// Create new node with key=k, value=v and insert it into tree 
// Returns 1 upon success 0 otherwise 
void insertAVL (Key k, void *v, Tree *t);

// Print text representation of tree
void printTree (Node* root);
void printTree2 (Node* root);	// alternate to printTree()

// Traverse tree inorder, printing information as it proceeds
void inOrderT(Node* root);

// Returns Maximum of two numbers 
int maxint (int a, int b);

// Find parent of node n where n->key = k; returns NULL if not found
pNode findParent(Key k, pNode root);


// ***** FUNCTIONS YOU IMPLEMENT AS PART OF LAB ******

// Return the height of the tree (height of the root)
//int height(Node *root);

// Helper function for findParent
Node* findParentHelper(Key k, Node* root);

// Rotate to right - return new root pointer
Node	*rotateRight(Node* root);

// Rotate to left - return new root pointer
Node	*rotateLeft(Node* root);

// Get balance factor for node - difference between left and right
// subtree heights
int		getBalanceFactor(Node* root);

// Calculate height of node, from the heights of left and right subtrees.
int		calcHeight(Node* root);
