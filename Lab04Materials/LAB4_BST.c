// LAB4_BST.c - Lab 04 - Dylan, Smith
//
// Code for ELEC278 Lab 4. Bare bones BST code used to do time comparisons.
// You may recognize this as a cut from the Lab 03 solution.

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

#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

void insertBST(Key k, void *v, Tree *t)
// Function inserts new node into tree, with key k and value pointed to
// by v. Parameter root points to root node of tree.  Note that this code
// rejects an attempt to insert a duplicate key.
{

	// Check for mistakes, including verification of tree type
	if ((t == NULL) || (t->tt != BST))
		return;

	if (t->root == NULL)
	{
		Node *n = initNode(k, v);
		n->height = 0;
		t->root = n;
	}
	else
	{
		t->root = insertNodeBST(k, v, t->root);
		// return;
	}
	return;
} // insert()

Node *insertNodeBST(Key k, void *v, Node *root)
{
	// printf ("Insert %d into BST\n", k);
	//  this if statement can only be true with first root (root of whole tree)
	if (root == NULL)
	{
		Node *n = initNode(k, v);
		root = n;
		return n;
	}

	// already exists in tree ==> can't insert
	if (root->key == k)
		return root;

	else if (k < root->key)
	{
		root->leftChild = insertNodeBST(k, v, root->leftChild);
	}
	else if (k > root->key)
	{
		root->rightChild = insertNodeBST(k, v, root->rightChild);
	}
	return root;
}
