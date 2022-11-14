// BST.H
// Header file to be used with code for ELEC278 Lab 4.

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
#include "bintree.h"

#define BST_FAIL 0 // return value when function fails
#define BST_OK 1   // return value when function succeeds

// Prototypes for functions found in BST.C

// Create new node with key=k, value=v and insert it into tree
// Returns 1 upon success, 0 failure
void insertBST(Key k, void *v, Tree *t);
Node *insertNodeBST(Key k, void *v, Node *root);
