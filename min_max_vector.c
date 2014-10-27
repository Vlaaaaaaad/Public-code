/**************************************************************************
/ 15. You have a vector with n elements. 
/		Find out the minimum and the maximum value from the vector.
/
***************************************************************************/

/*
I've implemented a recursive function that splits the vector in two until it gets a pair of numbers
	(or just one number for the odd case) and compares them.

After all the splits you have just two elements. Kind of like the leaf level in a tree.
	On the leaf level we have 1 comparison for every n /2 final nodes = n / 2
	On every other non-final level which is also not the first level, we do 2 comparisons = n - 2
										Total = ( n / 2 ) + n - 2
*/

// -------------------------------------------------------------------------------------------------------------------//

#include <stdio.h>
#include <stdlib.h>

// -------------------------------------------------------------------------------------------------------------------//

void minMax (int* v, int i, int j, int* min, int* max) 
{
	int l_min, l_max, r_min, r_max, middle; // l_min = left_minim and r_min = right_minim

	if( i == j) // if we only have 1 number, that number is bot the min and the max
	{
		*min = v[i];
		*max = v[j];
	}
	else
		// if we have two elements we compare them
		if( j == i + 1 )
		{
			if ( v[i] > v[j] )
			{
				*min = v[j];
				*max = v[i];
			}
			else
			{
				*min = v[i];
				*max = v[j];
			}
		}
		// if we have more than 2 elements we split the vector in half
		else
		{
			middle = (i + j) / 2;
			
			minMax(v, i, middle, &l_min, &l_max); // function for the left half
			minMax(v, middle + 1, j, &r_min, &r_max); // function for the right half
			
			// we compare the left min with the right min
			if(l_min < r_min)
				*min = l_min;
			else
				*min = r_min;
			
			// we compare the left max with the right max
			if(l_max > r_max)
				*max = l_max;
			else
				*max = r_max;
		}
}

// -------------------------------------------------------------------------------------------------------------------//
// -------------------------------------------------------------------------------------------------------------------//
// -------------------------------------------------------------------------------------------------------------------//

int main()
{
	int i, n, min, max;
	int v[100];

	printf("Insert the length of the vector. \n");
	scanf("%d", &n);

	for( i = 0 ; i <= n - 1; i++)
	{
		printf("\nv[%d]=", i);
		scanf("%d", &v[i]);
	}

	minMax(v, 0, n - 1, &min, &max);
	printf ("\nThe global minimum is : %d and the global maximum is: %d\n", min, max);

	scanf("%*c");
	return 0;
}
