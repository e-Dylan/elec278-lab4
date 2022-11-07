// BINTREE.C - ELEC278 Lab exercise 4
//
// This module contains code use in both a Binary Search Tree and an AVL tree.
// In both these data structures, we have tree nodes that contain a key, a
// pointer to node data associated with the key, left and right subtree
// pointers, and a height value. Height is not a necessary item for a BST
// but by including it, we can simplify the code in Lab 4.
//
//

/* --README--------------------------------------------------------------------
Source code used for teaching purposes in course:
ELEC278, Queen's University, Kingston, Fall semester 2022.
This code is provided without warranty of any kind. It is the responsibility
of the user to determine the correctness and the usefulness of this code for
any purpose.

All rights reserved. This code is intended for students registered in the
course and the semester listed above.

See LICENCE.MD for restrictions on the use of this code.
---------------------------------------------------------------------------- */


#include	<stdio.h>
#include	<stdlib.h>
#include	"bintree.h"


// Functions that are generic to either a BST or an AVL tree. Where two
// tree types differ is in their insert and delete functions.
// routines.


pNode initNode (Key k, void *v)
// Allocate memory for new node and initialize fields.
// Returns pointer to node created, or NULL if no memory.
{
	pNode n = (pNode) malloc(sizeof(Node));
	if (n != NULL)	{
		n->key = k;
		n->value = v;
		n->leftChild = NULL;
		n->rightChild = NULL;
		n->height = -1;
		}
	return n;
}//initNode()


pTree initTree (TreeType trtype)
// Allocate memory for a tree descriptor. As noted in the header file, a tree
// descriptor could be much more elaborate, but this is sufficient for our
// purposes.
// Function allocates memory for Tree structure, then initializes root pointer
// to NULL. Pointer returned from this function is used to identify tree in 
// subsequent tree operations.
{
	pTree t = (pTree) malloc(sizeof(Tree));
	if (t != NULL)	{
		t->root = NULL;
		t->tt = trtype;		// record tree type
		}
	return t;
}//initTree()


pNode find (Key k, pNode root)
// Function locates node with key value equal to parameter k. Parameter root
// holds pointer to root node of tree. Function returns immediately if either
// root pointer is null, or node that root points to has key value being 
// looked for.  If neither of those conditions is true, then the
// function calls itself with pointer to root of either left or right
// subtree.
{
#if 0
	printf ("FIND CALLED\n");
	if (root != NULL)	{
		printf ("Checking %d while looking for %d\n", root->key, k);
	} else	{
		printf ("Root is NULL\n");
		}
#endif
	// termination conditions - either true, search is ended
	if ((root == NULL) || (root->key == k))	return root;
	// search continues.  Since this is a search tree, we know that
	// every key in the right subtree is bigger than the key in the tree's
	// root, and every key in the left subtree is smaller than the key in
	// the tree's root.  That allows us to choose the appropriate subtree
	// to search.
	if (k > root->key)
		// Key value sought is larger than current node key, so search right
		// subtree
		return find(k,root->rightChild);
	else
		// Key value sought is smaller than current node key (equal case
		// was handled as termination condition in first line), so
		// search left subtree
		return find(k,root->leftChild);	
#if 0
	// slightly obscure way of doing if-then-else above. It is left to the
	// reader to decide which is the better code
	return find (k, (k > root->key) ? root->rightChild : root->leftChild);
#endif
}// find()
