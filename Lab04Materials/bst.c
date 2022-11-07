// BST.C 
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


// Your code goes here - addition so that insert to a BST can be done by passing
// a pTree parameter, not a pNode parameter. (See AVL code for a suggestion.)
//---<SNIP>---

//---</SNIP>---

int insertBST(Key k, void *v, pNode root)
// Function inserts new node into tree, with key k and value pointed to
// by v. Parameter root points to root node of tree.  Note that this code
// rejects an attempt to insert a duplicate key.
{
	int result = BST_FAIL;

	//printf ("Insert %d into BST\n", k);
	// this if statement can only be true with first root (root of whole tree)
	if (root == NULL)	{
		Node *n = initNode(k,v);
		root = n;
		return BST_OK;
		}
	
	// already exists in tree ==> can't insert
	if (root->key == k)
		result = BST_FAIL;
	else if (k < root->key) {
		// key value less than key value in root node - try to insert into left
		// subtree, if it exists.
		if (root->leftChild != NULL)
			// there is a left subtree - insert it
			result = insertBST(k, v, root->leftChild);
		else {
			// new Node becomes the left subtree
			Node *n = initNode(k,v);
			root->leftChild = n;
			result = BST_OK;
			}
	} else if (k > root->key) {			// test actually redundant
		// key is greater than this nodes key value, so value goes into right
		// subtree, if it exists
		if (root->rightChild != NULL)
			// there is a right subtree - insert new node
			result = insertBST(k,v,root->rightChild);
		else {
			// no right subtree - new node becomes right subtree
			Node *n = initNode(k,v);
			root->rightChild = n;
			result = BST_OK;
			}
		}
	return result;	
}//insert()
