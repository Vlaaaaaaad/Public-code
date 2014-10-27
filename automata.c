#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//--------------------------------------------------------------------------------------------------------------------//

struct state
{
	int id;

	int final;

	struct state *next[26];
}states[100], *initial, *current;

//--------------------------------------------------------------------------------------------------------------------//

void initialize()
{
	int letters, nr_states, id_initial, n, yes, i ,j, k;

	printf("\nHow many letters does the alphabet have? \n");
	scanf("%d", &letters);

	printf("\nHow many states? \n");
	scanf("%d", &nr_states);

	printf("\nWhat's the initial state id? \n");
	scanf("%d", &id_initial);

	initial = &states[id_initial];

	printf("\nHow many final states?\n");
	scanf("%d", &n);

	for(i = 1 ; i <= nr_states ; i++) // Just because I can't properly initialize an int in a struct
		states[i].final = 0;

	for(i = 1 ; i <= n ; i++)
	{
		printf("\nInsert the id of the final state number %d.\n", i);
		scanf("%d", &yes);

		states[yes].final = 1;

	}

	// reading the function
	for(i = 1 ; i <= nr_states ; i++)
		for(j = 1 ; j <= letters ; j++)
		{
			printf("\nFrom state %d, on the road with the letter %c we're going into state: ", i, j + 'a' - 1);
			scanf("%d", &k);

			states[i].next[j] = &states[k];
		}

	return;
}

//--------------------------------------------------------------------------------------------------------------------//

void check(char word[])
{
	int length, ct = 0;
	
	length = strlen(word);
	
	while(ct <= length)
	{
		if(ct == 0)
		{
			current = initial;
			ct++;
		}

		else
		{
			current = current -> next[ word[ct - 1] - 'a' + 1 ];
			ct++;
		}	
	}

	return;
}

//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//

int main()
{
	int answer;

	char word[100];

	initialize();

	do
	{
		printf("\n\nWhat is the word you would like to be checked?. \n");
		scanf("%s", word);

		check(word);

		if(current -> final == 1)
			printf("\n\nYes, the word is recognized.\n");
		else
			printf("\n\nNo, the word is not recognized.\n");

		printf("\n\nTo exit press 0.\nTo ckeck another word press any other number.\n");
		scanf("%d", &answer);

	}while(answer != 0);

	scanf("%*c");
	return 0;
}
