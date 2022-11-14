// LAB4_AVL.c - Lab 04 - Dylan, Smith
//
// Code for ELEC278 Lab 4.  Some code has already been implemented.
// You will develop your own code - look for the comments that say:
// "Your code goes here";
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

#include <stdio.h>
#include "bintree.h"
#include "avl.h"

void printTree(Node *root)
// Print representation of tree. We make an assumption, because tree nodes
// actually have pointer to data, not actual data.  So assume that it is a
// pointer to an integer.
{
	printf("{"); // Tree starts with an opening curly bracket
	// then value of root node
	printf("(%d,%d)", root->key, *(int *)root->value);
	// need to cast void pointer actual data type
	printf(","); // children come next

	// left child. If NULL it will just print two empty braces,
	// otherwise it prints whole left tree.
	if (root->leftChild)
	{
		printTree(root->leftChild);
	}
	else
		printf("{}");
	// separate left child from right child
	printf(",");
	// right child. If NULL it will just print two empty braces,
	// otherwise it prints whole right tree.
	if (root->rightChild)
	{
		printTree(root->rightChild);
	}
	else
		printf("{}");
	printf("}"); // Tree ends with closing curly bracket
} // printTree()

//=============================================================================
// ALTERNATE IMPLEMENTATION OF PRINTTREE - FOR YOUR REVIEW.
//    YOU MAY IGNORE THIS.

void printTree2(Node *root)
// Print representation of tree. We make an assumption, because tree nodes
// actually have pointer to data, not actual data.  So assume that it is a
// pointer to an integer.
{
	if (root == NULL)
	{
		// printing an empty tree
		printf("{}");
	}
	else
	{
		// printing non-empty tree
		printf("{"); // Tree starts with an opening curly bracket
		// then value of root node
		printf("(%ld,%d)", (long)root->key, *(int *)root->value);
		// need to cast void pointer actual data type
		printf(","); // children come next

		// left child.
		printTree(root->leftChild);
		// separate left child from right child
		printf(",");
		// right child.
		printTree(root->rightChild);
		printf("}"); // Tree ends with closing curly bracket
	}
} // printTree2()
//=============================================================================

int maxint(int a, int b) { return (a >= b) ? a : b; }

void insertAVL(Key k, void *v, Tree *t)
// Add new data item to tree.  Use two data components - key and actual data -
// to create new node and insert node in appropriate place.
{
	// Check for mistakes, including verification of tree type
	if ((t == NULL) || (t->tt != AVL))
		return;
	// printf("Insert %d into AVL\n", k);
	//  Check if tree empty - if so, insert first node
	if (t->root == NULL)
	{
		Node *n = initNode(k, v);
		n->height = 0;
		t->root = n;
	}
	else
	{
		t->root = insertNodeAVL(k, v, t->root);
	}
	return;
} // insert()

Node *rotateRight(Node *root)
// Rotate to right.  Returns new root pointer.
{
	printf("Rotate Right\n");

	Node *n1 = root->leftChild;
	Node *n2 = n1->rightChild;

	// rotate
	n1->rightChild = root;
	root->leftChild = n2;

	root->height = maxint(calcHeight(root->leftChild), calcHeight(root->rightChild)) + 1;
	n1->height = maxint(calcHeight(n1->leftChild), calcHeight(n1->rightChild)) + 1;

	// return the new root
	return n1;
} // rotateRight()

Node *rotateLeft(Node *root)
// Rotate to left.  Returns new root pointer.
{
	printf("Rotate Left\n");

	Node *n1 = root->rightChild;
	Node *n2 = n1->leftChild;

	// Perform rotation
	n1->leftChild = root;
	root->rightChild = n2;

	//  Update heights
	root->height = maxint(calcHeight(root->leftChild), calcHeight(root->rightChild)) + 1;
	n1->height = maxint(calcHeight(n1->leftChild), calcHeight(n1->rightChild)) + 1;

	// Return new root
	return n1;
} // rotateLeft()

int getBalanceFactor(Node *root)
// Get balance factor - difference between left height and right height
{
	if (root == NULL)
	{
		return 0;
	}
	int hr = -1, hl = -1; // Default values
	hl = calcHeight(root->leftChild);
	hr = calcHeight(root->rightChild);
	return hl - hr;
} // getBalanceFactor()

int calcHeight(Node *root)
// Calculate height of this node by adding 1 to maximum of left, right
// child height.
{
	if (root == NULL)
	{
		return -1;
	}
	else
	{

		int hrl = calcHeight(root->rightChild);
		int hll = calcHeight(root->leftChild);
		return maxint(hrl, hll) + 1;
	}
} // calcHeight();

Node *insertNodeAVL(Key k, void *v, Node *root)
// Build new node and insert into (non-empty) tree. Check if insertion has
// created imbalance and rebalance if necessary.
{
	if (root == NULL)
	{
		Node *n = initNode(k, v);
		n->height = 0;
		return n;
	}
	if (k < root->key)
	{
		root->leftChild = insertNodeAVL(k, v, root->leftChild);
		root->height = calcHeight(root);
	}
	else if (k > root->key)
	{
		root->rightChild = insertNodeAVL(k, v, root->rightChild);
		root->height = calcHeight(root);
	}

	// Check if rebalance is needed
	int bf = getBalanceFactor(root);

	// 4 possible cases:

	// left left
	if (bf > 1 && k < root->leftChild->key)
		return rotateRight(root);

	// right right
	if (bf < -1 && k > root->rightChild->key)
		return rotateLeft(root);

	// left right
	if (bf > 1 && k > root->leftChild->key)
	{
		root->leftChild = rotateLeft(root->leftChild);
		return rotateRight(root);
	}

	// right left
	if (bf < -1 && k < root->rightChild->key)
	{
		root->rightChild = rotateRight(root->rightChild);
		return rotateLeft(root);
	}

	// No rebalances needed, return unmodified root
	return root;

} // insertNode()

void inOrderT(Node *root)
// In order traversal of tree displaying contents
{
	if (root)
	{
		inOrderT(root->leftChild);
		printf("%d(h=%d,bf=%d) - ", root->key, root->height, getBalanceFactor(root));
		inOrderT(root->rightChild);
	}
} // inOrderT()

Node *findSmallestNode(Node *node)
{
	Node *current = node;
	// descend down left children since smallest value is always on left child.
	while (current->leftChild != NULL)
	{
		current = current->leftChild;
	}
	// return smallest key node.
	return current;
}

Node *delete (Node *root, Key key)
{
	if (root == NULL)
	{
		return root;
	}

	if (key < root->key)
	{
		root->leftChild = delete (root->leftChild, key);
	}
	else if (key > root->key)
	{
		root->rightChild = delete (root->rightChild, key);
	}
	else
	{
		// node has same key as root key, delete this one, end recursive cycle
		if (root->leftChild == NULL || root->rightChild == NULL)
		{
			Node *temp = root->leftChild ? root->leftChild : root->rightChild;

			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else
			{
				*root = *temp;
				free(temp);
			}
		}
		else
		{
			Node *temp = findSmallestNode(root->rightChild);

			root->key = temp->key;

			root->rightChild = delete (root->rightChild, temp->key);
		}
	}

	if (root == NULL)
	{
		return root;
	}

	root->height = 1 + maxint(calcHeight(root->leftChild),
							  calcHeight(root->rightChild));

	int balance = getBalanceFactor(root);

	// Left Left Case
	if (balance > 1 && getBalanceFactor(root->leftChild) >= 0)
		return rotateRight(root);

	// Left Right Case
	if (balance > 1 && getBalanceFactor(root->leftChild) < 0)
	{
		root->leftChild = rotateLeft(root->leftChild);
		return rotateRight(root);
	}

	// Right Right Case
	if (balance < -1 && getBalanceFactor(root->rightChild) <= 0)
		return rotateLeft(root);

	// Right Left Case
	if (balance < -1 && getBalanceFactor(root->rightChild) > 0)
	{
		root->rightChild = rotateRight(root->rightChild);
		return rotateLeft(root);
	}

	return root;
}