// MAIN.C - ELEC278 Lab exercise 4 - Fall 2022
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
#include "bintree.h"
#include "avl.h"


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
	int		i, readcount;
	Tree	*t_avl;				// pointer to AVL tree descriptor
	int		gabby = 1;		// flag whether we should generate lots of output
	int		count;			// count number of insertions

	fprintf (stderr, "AVL Tree.\n");
	// set up descriptor to be used for AVL tree
	t_avl = initTree(AVL);
	if (t_avl == NULL)	{
		panic ("Failed to initialize AVL tree descriptor.", NULL);
		}
	if (argc == 2)	{
		// Looks like user has specified an input file on command line. Assume
		// there is lots of data and output should be small.
		fname = argv [1];
		gabby = 0;
	} else	{
		// use default input file
		fname = "avl_data_A.txt";
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
	for (count=0;;count++)	{
		// Read value from file
		readcount = fscanf (finn, "%d", &i);
		// Failure to read or negative number means end of list
		if ((readcount < 1) || (i < 0))	break;
		// Insert value into tree (Note we're using a fake data value
		insertAVL(i, NULL, t_avl);
		if (gabby)	{
			printf("Inorder: ");
			inOrderT(t_avl->root);
			printf("\n-------\n");
		} else	{
			// This is the terse output when a large file is being read
			printf ("%7d: %11d\n", count, i);
			}
			
		}
	// Close file
	fclose (finn);

	// Any additional processing?
	return 0;
}//main()
