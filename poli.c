#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node
{
	int grade;
	int coefficient;

	struct node *next;
} *first[3], *last[3];

//--------------------------------------------------------------------------------------------------------------------//

void add_node(int i, int coeficient, int grad)
{
	if ( first[i] == NULL)
	{
		first[i] = malloc( sizeof( struct node) );

		first[i] -> grade = grad;
		first[i] -> coefficient = coeficient;
		first[i] -> next = NULL;

		last[i] = first[i];
	}

	else
	{
		struct node *p;

		p = malloc( sizeof (struct node) );

		last[i] -> next = p;

		p -> grade = grad;
		p -> coefficient = coeficient;
		p -> next = NULL;

		last[i] = p;
	}

	return;
}

//--------------------------------------------------------------------------------------------------------------------//

void show(int i)
{
	struct node *current;

	current = first[i];

	while( current)
	{
		printf("\n%d * X ^ %d", current -> coefficient, current -> grade);
		current = current -> next;
	}

	return;
}

//--------------------------------------------------------------------------------------------------------------------//

void add(int i, int j)
{
	struct node *current1, *current2;

	current1 = first[1];
	current2 = first[2];

	while(current1 || current2)
	{
		if(current1 -> grade > current2 -> grade)
		{
			add_node(3, current1 -> coefficient, current1 -> grade);
			current1 = current1 ->next;
		}

		if(current1 -> grade < current2 -> grade)
		{
			add_node(3, current2 -> coefficient, current2 -> grade);
			current2 = current2 -> next;
		}

		if(current1 -> grade == current2 -> grade)
		{
			add_node(3, current1 -> coefficient + current2 -> coefficient, current1 -> grade);
			current1 = current1 -> next;
			current2 = current2 -> next;
		}
	}

	return;
}

//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//

int main()
{
	int pol1, pol2, coef, i;

	printf("What is the degree of the first polynomial?\n");
	scanf("%d", &pol1);

	for(i = pol1 ; i >= 0; i--)
	{
		printf("What is the coefficient of X ^ %d? ", i);
		scanf("%d", &coef);

		if(coef != 0)
			add_node(1, coef, i);
	}

	printf("\nWhat is the degree of the second polynomial?\n");
	scanf("%d", &pol2);

	for(i = pol2 ; i >= 0; i--)
	{
		printf("What is the coefficient of X ^ %d? ", i);
		scanf("%d", &coef);

		if(coef != 0)
			add_node(2, coef, i);
	}

	printf("\nFirst polynomial");
	show(1);

	printf("\nSecond polynomial:");
	show(2);

	add(1,2);

	printf("\n\nThe sum is:");
	show(3);

	scanf("%*c");
	return 0;
}
