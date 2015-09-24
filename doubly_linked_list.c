#include <stdio.h>
#include <stdlib.h>

//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//

struct node
{
	int value;
	struct node *prev;
	struct node *next;

} *first, *last;

//--------------------------------------------------------------------------------------------------------------------//

void add_beginning(int x)
{
	if(first == NULL)
	{
		first = malloc( sizeof (struct node) );

		first -> value = x;

		first -> prev = NULL;
		first -> next = NULL;
		last = first;
	}

	else
	{
		struct node *p;

		p = malloc( sizeof (struct node) );

		first -> prev = p;

		p -> value = x;
		p -> prev = NULL;
		p -> next = first;

		first = p;
	}

	return;
}

//--------------------------------------------------------------------------------------------------------------------//

void add_end(int x)
{
	if(first == NULL)
	{
		first = malloc( sizeof (struct node) );

		first -> value = x;

		first -> prev = NULL;
		first -> next = NULL;
		last = first;
	}

	else
	{
		struct node *p;

		p = malloc( sizeof (struct node) );

		last -> next = p;

		p -> value =x;
		p -> prev = last;
		p -> next = NULL;

		last = p;
	}

	return;
}

//--------------------------------------------------------------------------------------------------------------------//

void add_inside(int x, int y) // inserts x after y
{
	int done;
	struct node *current, *p;

	done = 0;
	current = first;

	while(current && done == 0)
	{
		if(current -> value == y)
		{
			p = malloc( sizeof (struct node) );

			p -> value = x;
			p -> prev = current;
			p -> next = current -> next;

			current -> next -> prev = p;

			current -> next = p;

			done = 1;
		}

		current = current -> next;
	}

	return;
}

//--------------------------------------------------------------------------------------------------------------------//

void show()
{
	struct node *current;

	current = first;

	while( current)
	{
		printf("%d ", current -> value);
		current = current -> next;
	}

	return;
}

//--------------------------------------------------------------------------------------------------------------------//

void show_reverse()
{
	struct node *current;

	current = last;

	while( current)
	{
		printf("%d ", current -> value);
		current = current -> prev;
	}

	return;
}

//--------------------------------------------------------------------------------------------------------------------//

void delete_id(int id)
{
	struct node *current, *temp;

	int done, ct;
	done = 0;
	ct = 1;

	current = first;

	if(id == 1)
	{
		// we delete the first node

		temp = first -> next;

		temp -> prev = NULL;

		free(first);

		first = temp;
	}

	else
	{
		do
		{
			ct++;
			current = current -> next;

			if(ct == id)
			{
				// we delete the current node
				current -> prev -> next = current -> next;
				current -> next -> prev = current -> prev;

				free(current);

				done = 1;
			}

		}while(current != last && done == 0);
	}

	return;
}

//--------------------------------------------------------------------------------------------------------------------//

void delete_value(int x)
{
	struct node *current, *temp;

	int done;
	done = 0;

	current = first;

	if ( first -> value == x)
	{
		first -> next -> prev = NULL;
		temp = first -> next;

		free(first);

		first = temp;
	}

	else
	{
		do
		{
			current = current -> next;

			if(current -> value == x)
			{
				// we delete the current node
				current -> prev -> next = current -> next;
				current -> next -> prev = current -> prev;

				free(current);

				done = 1;
			}

		} while (current != last && done == 0);
	}

	return;
}

//--------------------------------------------------------------------------------------------------------------------//

void menu()
{
	printf("\n1. Insert an element at the beginning.");
	printf("\n2. Insert an element at the end.");
	printf("\n3. Insert an element inside( after a value).");
	printf("\n4. Show the list.");
	printf("\n5. Show the list in reverse.");
	printf("\n6. Delete an element from a certain position.");
	printf("\n7. Delete an element of a certain value.");
	printf("\n\n0. Exit.");

	return;
}

//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//

int main()
{
	int opt, x, y;

	do
	{
		menu();

		scanf("%d", &opt);

		switch(opt)
		{
			case 1:
			{
				printf("\n\nInsert the value you would like to be added at the beginning of the list.\n");
				scanf("%d", &x);

				add_beginning(x);
				break;
			};

			case 2:
			{
				printf("\n\nInsert the value you would like to be added at the end of the list.\n");
				scanf("%d", &x);

				add_end(x);
				break;
			};

			case 3:
			{
				printf("\n\nInster the value after you want ot insert a new element.\n");
				scanf("%d", &y);
				printf("\n\nInsert the value you would like to be added.\n");
				scanf("%d", &x);

				add_inside(x, y);
				break;
			};

			case 4:
			{
				show();
				break;
			};

			case 5:
			{
				show_reverse();
				break;
			};

			case 6:
			{
				printf("\n\nInsert the position of the element you would like to delete.\n");
				scanf("%d", &x);

				delete_id(x);
				break;
			};

			case 7:
			{
				printf("\n\nInsert the value of the element you would like to be deleted.\n");
				scanf("%d", &x);

				delete_value(x);
				break;
			};

		};

	}while( opt != 0);

	printf("\nYou left the menu. Press any key to exit.");

	scanf("%*c");
	return 0;
}
