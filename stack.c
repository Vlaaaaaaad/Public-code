// Tema 4, problema 1
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
	struct node *current, *temp;
	int x;
	
	current = first;
	
	x = last -> value;

	while(current -> next -> next)
	{
		current = current -> next;
	}

	current -> next = NULL;
	
	free(last);
	
	last = current;

	return x;
}

//--------------------------------------------------------------------------------------------------------------------//

int peek()
{
	return(last -> value);
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
	int x, opt;

	do
	{
		menu();

		scanf("%d", &opt);

		switch(opt)
		{
			case 1: 
			{ 
				printf("\n \n Insert the number you would like to be added to the stack. \n"); 
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
					printf("\n The stack is empty.");
				else
					printf("\n The stack is not empty.");
				break;
			};
			
			case 5:
			{
				printf("\n Insert the number you would like to search.\n");
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
