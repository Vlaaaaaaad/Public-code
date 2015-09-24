#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//--------------------------------------------------------------------------------------------------------------------//

struct node
{
	int value;
	struct node *next;
} *first, *last;

//--------------------------------------------------------------------------------------------------------------------//

void push(int x)
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

//--------------------------------------------------------------------------------------------------------------------//

int pop()
{
	int x;

	struct node *temp;

	x = first -> value;

	temp = first -> next;

	free(first);

	first = temp;

	return x;
}

//--------------------------------------------------------------------------------------------------------------------//

int peek()
{
	return first->value;
}

//--------------------------------------------------------------------------------------------------------------------//

bool empty()
{
	if(first == NULL)
		return true;
	else
		return false;
}

//--------------------------------------------------------------------------------------------------------------------//

int search(int x)
{
	int ct;
	struct node *current;

	ct = 0;
	current = first;

	while( current)
	{
		ct++;
		if (current -> value == x)
			return ct;
		current = current -> next;
	}

	return -1;
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

}

//--------------------------------------------------------------------------------------------------------------------//

void menu()
{
	printf("\n1. Push");
	printf("\n2. Pop");
	printf("\n3. Peek");
	printf("\n4. Empty?");
	printf("\n5. Search");
	printf("\n6. Show");
	printf("\n\n0. Exit\n");
}

//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//

int main()
{
	int raspuns, x, opt;

	do
	{
		menu();

		scanf("%d", &opt);

		switch(opt)
		{
			case 1:
			{
				printf("\n \n Insert the number you would like to add to the queue. \n");
				scanf("%d", &x);
				push(x);
				break;
			};

			case 2:
			{
				printf("Pop: %d.", pop());
				break;
			};

			case 3:
			{
				printf("Peek: %d.", peek());
				break;
			};

			case 4:
			{
				if(empty() == true)
					printf("\n The queue is empty.");
				else
					printf("\n The queue is not empty.");
				break;
			};

			case 5:
			{
				printf("\n Insert the element you would like to search for.\n");
				scanf("%d", &x);

				printf("%d", search(x));
				break;
			};

			case 6:
			{
				show();
				break;
			};
		};

	}while( opt != 0);

	scanf("%*c");
	return 0;
}
