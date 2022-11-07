// MAKERANDOM.C 
// Program to create big file of integers required for ELEC278 Lab 4.
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
#include	<time.h>

// Hold all numbers. Why, because after generating a bunch of random numbers,
// we will sort a few portions just to make the behavior of BST worse.
#define	NUMS_SZ	20000
int nums [NUMS_SZ];

int	seed = 734912886;		// just some arbitrary seed value. Using constant
							// seed gives same sequence.
int	fixed = 1;				// set to either 0 or 1, giving eiter a different
							// set of numbers each run, or the same set each
							// run.
int	gabby = 0;				// if gabby is 1, program spews a lot of debug
							// information.


void swap (int *a, int g, int h)
//
{
	int  t = a[g];
	if (gabby)
		fprintf (stderr, "Swapping elements at %d (%d) and at %d (%d)\n",
					g, a[g], h, a[h]);
	a[g] = a[h];
	a[h] = t;
}//swap()


int bubbleup (int *a, int min, int max)
// Bubbles largest element to higher index end of array.
// Returns number of swaps done to accomplish this.
{
	int swaps = 0;
	int	i;
	if (a == NULL)	return -1;
	if (max <= min)	return 0;
	if (gabby)
		printf ("Start another bubble up\n");
	for (i=min; i<max; i++)	{
		if (a[i] > a[i+1])	{
			// out of order - swap required
			swap (a, i, i+1);
			swaps++;
			}//endif out of order
		}//endfor
	return swaps;
}//bubble()


int bubblesort (int *a, int low, int high)
// Apply bubblesort to a portion of the array a, starting at index low and
// ending at index high
{
	int		swaps;				// number of swaps on one pass of bubbleup()
	int		maxindx;			// every bubbleup(), sort range gets smaller

	// check for mistakes
	if (	(a == NULL) ||
			(low < 0)	||
			(high < 0)	||
			(low > high)	)	{
		fprintf (stderr, "ERROR: Bubblesort - invalid parameters\n");
		return -1;
		}

	// Every time through loop, one more data item is placed correctly.
	for (maxindx=high; maxindx>low; maxindx--)	{
		swaps = bubbleup (a, low, maxindx);
		if (gabby)	{
			printf ("Swaps done: %d\n", swaps);
			}
		// if no swaps were done, we're finished
		if (swaps == 0)	break;
		}//endfor
	// Portion of array sorted
	return 0;
}//bubblesort()


#if 0

// This didn't generate a good distribution, IMHO

unsigned int rand32(void)
// Generate 32-bit unsigned random number using rand(). Note that in many
// C implementations, rand() generates a 15-bit - not 16-bit - random number.
{
	unsigned int	x;
	x = rand() & 0xff;
	x |= (rand() & 0xff) << 8;
	x |= (rand() & 0xff) << 16;
	x |= (rand() & 0xff) << 24;
	return x & 0x7fffffff;
}//rand32()

// Neither did this

unsigned int rand32(void)
// Generate 32-bit unsigned random number using rand(). Note that in many
// C implementations, rand() generates a 15-bit - not 16-bit - random number.
{
	unsigned int	x;
	x = rand() & 0x7fff;			// keep 15 bits
	x |= (rand() & 0x7fff) << 15;	// now have 30 bits
	x |= (rand() & 0x01) << 30;		// now have 31
	return x & 0x7fffffff;
}//rand32()
#endif 

// Still not perfect, but I will keep it

unsigned int rand32(void)
// Generate 32-bit unsigned random number using rand(). Note that in many
// C implementations, rand() generates a 15-bit - not 16-bit - random number.
{
	unsigned int	x = 0;
	x |= (rand() & 0x7fff) << 16;	// keep 15 bits - at top of number
	x |= (rand() & 0x7fff) << 1;	// now have 30 bits
	x |= (rand() & 0x01);			// now have 31
	return x & 0x7fffffff;
}//rand32()



int main (void)
{
	int		i;
	int		portion_to_sort, low, high;
	FILE	*fpowt;

	// Seed random number generator. Note that seed is either a constant so
	// same random sequence is generated or it is current time so sequence
	// of numbers will be different each run.
	printf ("FYI: Maximum value from rand() is: %d\n", RAND_MAX);

	srand (fixed ? seed : time(0));

	// generate random numbers
	for (i=0; i<NUMS_SZ; i++)	{
		nums [i] = (int)rand32();
		//if (nums[i] < 0)	nums[i] = abs(nums[i]);
		}

	// Now mess up the randomness
	portion_to_sort = NUMS_SZ / 10;
	high = NUMS_SZ - portion_to_sort;
	low = high - portion_to_sort;
	bubblesort (nums, low, high);

	// Now output all the numbers
	fpowt = fopen ("lab04data_B.txt", "w");
	if (fpowt == NULL)	{
		fprintf (stderr, "ERROR: Cannot open output file\n");
		return -1;
		}

	for (i=0; i<NUMS_SZ; i++)	{
		fprintf (fpowt, "%10d\n", nums [i]);
		printf ("%6d:  %10d\n", i, nums [i]);
		}
	// Have to write negative number as sentinel at end of list
	fprintf (fpowt, "%3d\n", -1);
	fclose (fpowt);

	return 0;
} //main()
