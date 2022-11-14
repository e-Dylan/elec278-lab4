// BINTREE.H - ELEC278 Lab exercise 4
//
// This module contains code use in both a Binary Search Tree and an AVL tree.
// In both these data structures, we have tree nodes that contain a key, a
// pointer to node data associated with the key, left and right subtree
// pointers, and a height value. Height is not a necessary item for a BST
// but by including it, we can simplify the code in Lab 4.
//
//

#ifndef _BINTREE_H // Prevent multiple inclusion
#define _BINTREE_H

#define RTN_FAIL 0 // return value when function fails
#define RTN_OK 1   // return value when function succeeds

enum treetype
{
	BST,
	AVL
};

// Some typedefs just to make code slightly easier to read
typedef enum treetype TreeType; // way to identify correct tree type
typedef int Key;				// In another variation of the code, the key
								// might be something other than an integer.
typedef struct _node Node,		// actual _node definition follows.
	*pNode;						// (also define pointer to _node)
typedef struct _tree Tree,		// actual _tree definition follows.
	*pTree;						// (also define pointer to _tree)

// Node in tree has key and pointer to value associated with key.
// Also contains structural components - two pointers to left and
// right subtrees, and the node's height.
struct _node
{
	Key key;		  // key used to identify node
	void *value;	  // data pointer
	pNode leftChild;  // pointer to left subtree
	pNode rightChild; // pointer to right subtree
	int height;		  // height of this node (see definition)
};

// Tree description is basically pointer to top node in tree. In other
// implementations, it might make sense to store more information
// in the Tree data structure, but for our purposes, this is good
// enough.
struct _tree
{
	pNode root;
	TreeType tt;
};

// Prototypes for functions that are generic to either a BST or an AVL
// tree. Where the two tree types differ is in their insert and delete
// routines.

// Create new node with key = k and value = v
pNode initNode(Key k, void *v);

// Create new tree with no nodes
pTree initTree(TreeType trtype);

// Find node with key k in tree. Returns pointer to Node if found;
// Returns NULL if not found
pNode find(Key k, Node *root);

#endif // _BINTREE_H
