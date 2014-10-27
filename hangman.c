#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

//--------------------------------------------------------------------------------------------------------------------//

struct i_have_no_idea_for_a_name
{
	char letter;
	int visibility;

}word[30];

//--------------------------------------------------------------------------------------------------------------------//

void menu()
{	
	// How do you say hangman in Romanian? Answer:
	printf("\n\n");
	printf("\n #####                                                                                            ");
	printf("\n#     # #####    ##   #    # ###### #    # #####    ##   #####  ####    ##   #####  ######   ##   ");
	printf("\n#       #    #  #  #  ##   #     #  #    # #    #  #  #    #   #    #  #  #  #    # #       #  #  ");
	printf("\n #####  #    # #    # # #  #    #   #    # #    # #    #   #   #    # #    # #    # #####  #    # ");
	printf("\n      # #####  ###### #  # #   #    #    # #####  ######   #   #    # ###### #####  #      ###### ");
	printf("\n#     # #      #    # #   ##  #     #    # #   #  #    #   #   #    # #    # #   #  #      #    # ");
	printf("\n #####  #      #    # #    # ######  ####  #    # #    #   #    ####  #    # #    # ###### #    # ");
	printf("\n\n\n\n\n");

	printf("Press any key to begin. \n");
	scanf("%*c");

	return;
}

//--------------------------------------------------------------------------------------------------------------------//

int getWord() // searches for files that contain the available fields, chooses the word and adds it to the structure
{
	int i, ct, random, id, n;

	char address[100], secret_word[30];
	char field[10][90]; // maximum of 10 different fields

	FILE *f[10];
	FILE *fi;

	i = 0;
	ct = 0;

	printf("\nThe secret word can be chosen from the following fields: ");

	do
	{
		i++;

		if( i >= 2)
			fclose(f[i - 1 ]);

		n = sprintf(address, "/path/spanzuratoarea%d.txt", i);

		f[i] = fopen(address, "r");

		if(f[i] != NULL)
		{
			fscanf(f[i], "%s", &field[i]);
			printf("\n%d. %s", i, field[i]);
		}

	}while( f[i] != NULL);

	printf("\nInsert the field number you would like the secret word to be a part of. \n");
	scanf("%d", &id); // in id we have the field id

	n = sprintf(address, "/path/spanzuratoarea%d.txt", id);

	fi = fopen(address, "r");

	srand(time(NULL));
	random = rand() % 10; // 10 words in the file ( 0 - 9 )

	fscanf(fi, "%*s"); // we ignore the first line that contains the field name

	while( ct != random)
	{
		fscanf(fi, "%s", secret_word);
		ct++;
	}

	fclose(fi);

	// sending the word to the structure

	for(i = 0 ; i <= strlen(secret_word) - 1 ; i++)
	{
		word[i].letter = secret_word[i];
		word[i].visibility = 0;
	}

	return strlen(secret_word);
}

//--------------------------------------------------------------------------------------------------------------------//

void showLetter(char litera, int length) // mark the guessed letters as visible
{
	int i;

	for( i = 0 ; i <= length ; i++)
	{
		if( word[i].letter == litera)
			word[i].visibility = 1;
	}

	return;
}

//--------------------------------------------------------------------------------------------------------------------//

void clear() // portable function that clears the screen
{
	int i;

	for(i = 0 ; i <= 25 ; i++)
		printf("\n");

	return;
}

//--------------------------------------------------------------------------------------------------------------------//

void showWord(int length)
{
	int i;

	for( i = 0 ; i <= length ; i++)
	{
		if(word[i].visibility == 1)
			printf("%c", word[i].letter);
		else
			printf("_");
	}

	return;
}

//--------------------------------------------------------------------------------------------------------------------//

void dude(int step)
{
	switch(step)
	{
		case 1: 
		{
			printf("\n  +---+ ");
			printf("\n  |   | ");
			printf("\n      | ");
			printf("\n      | ");
			printf("\n      | ");
			printf("\n      | ");
			printf("\n======== ");
			break;
		};

		case 2: 
		{
			printf("\n  +---+ ");
			printf("\n  |   | ");
			printf("\n  O   | ");
			printf("\n      | ");
			printf("\n      | ");
			printf("\n      | ");
			printf("\n======== ");
			break;
		};

		case 3: 
		{
			printf("\n  +---+ ");
			printf("\n  |   | ");
			printf("\n  O   | ");
			printf("\n  |   | ");
			printf("\n      | ");
			printf("\n      | ");
			printf("\n======== ");
			break;

		};

		case 4: 
		{
			printf("\n  +---+ ");
			printf("\n  |   | ");
			printf("\n  O   | ");
			printf("\n /|   | ");
			printf("\n      | ");
			printf("\n      | ");
			printf("\n======== ");
			break;
		};

		case 5: 
		{
			printf("\n  +---+ ");
			printf("\n  |   | ");
			printf("\n  O   | ");
			printf("\n /|\\  | ");
			printf("\n      | ");
			printf("\n      | ");
			printf("\n======== ");
			break;
		};

		case 6: 
		{
			printf("\n  +---+ ");
			printf("\n  |   | ");
			printf("\n  O   | ");
			printf("\n /|\\  | ");
			printf("\n /    | ");
			printf("\n      | ");
			printf("\n======== ");
			break;
		};

		case 7: 
		{
			printf("\n  +---+ ");
			printf("\n  |   | ");
			printf("\n  O   | ");
			printf("\n /|\\  | ");
			printf("\n / \\  | ");
			printf("\n      | ");
			printf("\n======== ");
			break;
		};
	}

	return;
}

//--------------------------------------------------------------------------------------------------------------------//

bool done(int length) // checks if the game is over
{
	int i;

	for( i = 0 ; i <= length ; i++)
		if(word[i].visibility == 0)
			return false;
	return true;
}

//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//

int main()
{
	int bingo, step, length, i;
	char guess;

	step = 1;

	menu();

	length = getWord() - 1;

	showLetter(word[0].letter, length);
	showLetter(word[length].letter, length);

	do
	{
		bingo = 0;

		clear();
		printf("\n");

		dude(step);
		printf("\n\n");

		showWord(length);

		printf("\n\nInsert letter \n\n");
		scanf(" %c", &guess);

		for(i = 0 ; i <= length && bingo == 0; i++)
			if( word[i].letter == guess)
			{
				showLetter(guess, length);
				bingo = 1;
			}

		if(bingo == 0)
		{
			printf("\n\nThe letter %c is not part of the word :( \n", guess);
			step++;
		}

	}while(step <= 7 && !done(length) );

	if( step <= 7 && done(length))
	{
		clear();
		printf("\n░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░");
		printf("\n░░░░░░░░░░░░░░░░░█▀▀▀█░░░░░░░░░░");
		printf("\n░░░░░░░░░░░░░░░░█▀░░░█░░░░░░░░░░");
		printf("\n░░░░░░░░░░░░░░░█▀░░░░█░░░░░░░░░░");
		printf("\n░░░░░░░░░░░░░░█▀░░░░░█░░░░░░░░░░");
		printf("\n░░░░░░░░░░░░░█▀░░░░░░█░░░░░░░░░░");
		printf("\n▄▄▄▄▄▄▄▄░░░▄█▀░░░░░░░▀▀▀▀▀▀█▄░░░");
		printf("\n░░░░░░██▄▄█▀░░░░░░░░░░░░░░░░█░░░");
		printf("\n▄▄▄▄▄▄██░░░░░░░░░░░░░░░░░░░░█░░░");
		printf("\n████████░░░░░░░░░░░░░░░░░░░░█░░░");
		printf("\n████████░░░░░░░░░░░░░░░░░░░░█░░░");
		printf("\n████████░░░░░░░░░░░░░░░░░░░░█░░░");
		printf("\n████████░░░░░░░░░░░░░░░░░░░░█░░░");
		printf("\n████████▄▄▄▄▄░░░░░░░░░░░░░░░█░░░");
		printf("\n████████░░░░░▀█▄▄▄▄▄▄▄▄▄▄▄▄▀░░░░");
		printf("\n░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░");
	}
	else
	{
		clear();
		printf("\n███████▄▄███████████▄ ");
		printf("\n▓▓▓▓▓▓█░░░░░░░░░░░░░░█");
		printf("\n▓▓▓▓▓▓█░░░░░░░░░░░░░░█");
		printf("\n▓▓▓▓▓▓█░░░░░░░░░░░░░░█");
		printf("\n▓▓▓▓▓▓█░░░░░░░░░░░░░░█");
		printf("\n▓▓▓▓▓▓█░░░░░░░░░░░░░░█");
		printf("\n▓▓▓▓▓▓███░░░░░░░░░░░░█");
		printf("\n██████▀░█░░░░░██████▀░");
		printf("\n░░░░░░░░░█░░░░█░░░░░░░");
		printf("\n░░░░░░░░░░█░░░█░░░░░░░");
		printf("\n░░░░░░░░░░░█░░█░░░░░░░");
		printf("\n░░░░░░░░░░░█░░█░░░░░░░");
		printf("\n░░░░░░░░░░░░▀▀░░░░░░░░");

		printf("\n\nThe word was ");

		for( i = 0 ; i <= length ; i++)
			printf("%c", word[i].letter);
		printf(". ");
	}

	printf("\n\nGame over! \n");

	printf("\nPress any key to exit.\n\n");
	scanf("%*c");
	return 0;
}
