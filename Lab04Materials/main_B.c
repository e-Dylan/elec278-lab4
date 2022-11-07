// MAIN_B.C - ELEC278 Lab exercise 4 - Fall 2022
//
// *** DO NOT EDIT THIS CODE ***
//
// See instructions in the lab handout.  You will be adding code
// to avl.c.  This code is intended to verify that your code works.
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
#include <time.h>
#include "bintree.h"
#include "avl.h"
#include "bst.h"


void panic(char *msg, char *fname)
// Function to display error message on stderr and exit program.
// First parameter is error message; second is optional, and if present,
// is supplemental information.
{
	fprintf (stderr, "ERROR: %s %s\n",
			msg==NULL ? "Unknown!" : msg,
			fname==NULL ? "" : fname);
	fprintf (stderr, "       Program terminating\n");
	exit (-1);
}// panic()

	

int main(int argc, char *argv[])
{
	int		v1 = 1;
	char	*fname;			// name of input file
	FILE	*finn;			// used to input data file
	int		i, j, readcount;
	int		lastkeys[10], lastkeyindex;
	Tree	*t_avl;			// pointer to AVL tree descriptor
	Tree	*t_bst;			// pointer to BST tree descriptor
	int		gabby = 1;		// flag whether we should generate lots of output
	int		defaultdata;
	int		count;			// count number of insertions
	pNode	foundnode;
	clock_t	start, end, deltaBST, deltaAVL;

	fprintf (stderr, "Compare BST and AVL Trees.\n");
	// set up descriptor to be used for AVL tree
	t_avl = initTree(AVL);
	if (t_avl == NULL)	{
		panic ("Failed to initialize AVL tree descriptor.", NULL);
		}
	// set up descriptor to be used for BST tree
	t_bst = initTree(BST);
	if (t_bst == NULL)	{
		panic ("Failed to initialize BST tree descriptor.", NULL);
		}
	if (argc == 2)	{
		// Looks like user has specified an input file on command line. Assume
		// there is lots of data and output should be small.
		fname = argv [1];
		gabby = 0;
		defaultdata = 0;
	} else	{
		// use default input file
		fname = "avl_data_A.txt";
		defaultdata = 1;
		}
	fprintf (stderr, " -- Using input file: %s\n", fname);
	finn = fopen (fname, "r");
	if (finn == NULL)	{
		// something wrong - could not open file
		panic ( "Cannot open file:", fname);
		}
	// Insert each data value from file, and after inserting, output some
	// information about what the tree looks like. For the first part of
	// the lab, you just want to use the default input file.
	lastkeyindex = 0;
	for (count=0;;count++)	{
		// Read value from file
		readcount = fscanf (finn, "%d", &i);
		// Failure to read or negative number means end of list
		if ((readcount < 1) || (i < 0))	break;
		// Insert value into AVL tree (Note we're using a fake data value
		insertAVL(i, NULL, t_avl);
		if (gabby)	{
			printf("Inorder: ");
			inOrderT(t_avl->root);
			printf("\n-------\n");
		} else	{
			// This is the terse output when a large file is being read
			printf ("%7d: %11d\n", count, i);
			}

		// Your code to populate BST goes here
		//---<SNIP>---

		//---</SNIP>---
	
		// keep track of last keys inserted
		lastkeys [lastkeyindex] = i;
		if (++lastkeyindex > 9)	lastkeyindex = 0;
		}
	// Close file
	fclose (finn);

	// Note we have last key inserted. We are going to use this to test
	// lookup performance
	if (!defaultdata)	{
		// Your code to test BST goes here
		//---<SNIP>---

		//---</SNIP>---

		start = clock();
		for (i=0; i<1000000; i++)	{
			for (j=0; j<10; j++)	{
				foundnode = find (lastkeys[j], t_avl->root);
				if (foundnode == NULL)	{
					fprintf (stderr, "ERROR: AVL Could not find %d iteration %d\n",
							lastkeys[j], i);
					return -1;
					}//endif
				}//endfor
			}//endfor
		end = clock();
		printf("AVL Elapsed time: %.2f seconds (%d ticks)\n",
				(end - start) / (double)(CLOCKS_PER_SEC), (end-start));
		}//endif check timing

	return 0;
}//main()
