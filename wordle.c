// This is just a test to see if I can actually make a wordle clone
// I will be making the actual calculator version later.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Colors
#define NORMAL "\x1b[m"
#define GREEN "\x1b[32m"
#define CYAN "\x1b[36m"
#define YELLOW "\x1b[33m"

#define WORD_COUNT 5
#define LENGTH 5

// Booleans
#define true 1
#define false 0

// Check for if a word contains a character
int letterInWord(char letter, char word[6])
{
	// Loop through every character in the word
	for (size_t i = 0; i < LENGTH; i++)
	{
		if (letter == word[i]) return true;
	}

	return false;
}

int main() {

	// Set the random seed as the current time
	srand(time(NULL));

	// Words
	char wordCount[WORD_COUNT][6] = {
		"camus",
		"speed",
		"array",
		"polio",
		"stray"
	};
	
	// Get a random index from the array
	int index = rand() % WORD_COUNT;
	char word[6];
	strcpy(word, wordCount[index]);
	printf("debug '%s'", word);

	// 6 turns
	for (size_t i = 0; i < 6; i++)
	{
		// Get word input
		char input[6];
		printf("\n> ");
		scanf("%s", input);

		// True represents the state of the current index of the main word array
		int wrongPlace[LENGTH] = { false, false, false, false, false };
		int notInWord[LENGTH] = { false, false, false, false, false };
		int correct[LENGTH] = { false, false, false, false, false };

		// Loop through each character in the word
		for (size_t j = 0; j < LENGTH; j++)
		{
			// Check for if the current letter is in the correct position
			if (input[j] == word[j]) correct[j] = true;
			else if (letterInWord(input[j], word)) wrongPlace[j] = true;
			else notInWord[j] = true;
		}

		// Print the result for their input
		for (size_t j = 0; j < LENGTH; j++)
		{
			// Check for what the output thingy is
			if (correct[j] == true) printf("%s%c%s", GREEN, input[j], NORMAL);
			if (wrongPlace[j] == true) printf("%s%c%s", YELLOW, input[j], NORMAL);
			if (notInWord[j] == true) printf("%s%c%s", CYAN, input[j], NORMAL);
		}

		// Check for if they win
		if (correct[0] && correct[1] && correct[2] && correct[3] && correct[4])
		{
			printf("\nwin");
			break;
		}
	}
	


	
	return 0;
}