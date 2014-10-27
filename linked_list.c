#include <stdio.h>
#include <stdlib.h>

//-----------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------//

struct node
{
	int value;
	struct node *next;
} *first, *last;

//-----------------------------------------------------------------------------------------------------------------------------------//

void add_node(int x) // 5a) and 6c)
{
	if ( first == NULL)
	{
		first = malloc( sizeof( struct node) );

		first -> value = x;
		first -> next = NULL;
		last = first;
	}

		else
		{
			struct node *p;

			p = malloc( sizeof (struct node) );
			last -> next = p;
			p -> value = x;
			p -> next = NULL;
			last = p;
		}

}

//-----------------------------------------------------------------------------------------------------------------------------------//

void show() // 5b)
{
	struct node *current;

	current = first;

	while( current)
	{
		printf("%d ", current -> value);
		current = current -> next;
	}

}

//-----------------------------------------------------------------------------------------------------------------------------------//

int searchPos(int x) // 5c)
{
	int ct;
	struct node *current;
	
	ct = 0;
	current = first;

	while( current)
	{
		ct++;
		if (current -> value == x) return ct;
		current = current -> next;
	}
	
	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------------------//

void remove_node(int x) // 5d)
{

	struct node *current, *temp;

	int alfa;
	alfa = 0;
	
	current = first;

	if ( first -> value == x)
	{
		temp = first -> next;
		free(first);
		first = temp;
	}

	else
	{
		do
		{
			if( current -> next -> value == x)
			{
				temp = current -> next;
				current -> next = current -> next -> next;
				alfa = 1;
			}

			current = current ->  next;	

		} while (current != last && alfa == 0);

		free(temp);
	}
}

//-----------------------------------------------------------------------------------------------------------------------------------//

void remove_list() // e)
{
	struct node *temp;

	do
	{
		temp = first -> next;
		free(first);
		first = temp;
	}while(first != NULL);

}

//-----------------------------------------------------------------------------------------------------------------------------------//

void add_node_begin(int x) // 6a)
{

	if ( first == NULL)
	{
		first = malloc( sizeof( struct node) );

		first -> value = x;
		first -> next = NULL;
		last = first;
	}
	else
	{
		struct node *p;
		p = malloc( sizeof (struct node) );

		p -> value = x;
		p -> next = first;
		first = p;
	}
}

//-----------------------------------------------------------------------------------------------------------------------------------//

void add_node_inside(int x, int y) // 6b). Add a node of value y after a node of value x
{
	int done;
	struct node *current, *p;

	done = 0;
	current = first;

	while(current && done == 0)
	{
		if(current -> value == x)
		{
			p = malloc( sizeof (struct node) );
			p -> value = y;
			p -> next = current -> next;

			current -> next = p;
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------//
