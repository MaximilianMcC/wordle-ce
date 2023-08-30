// This is just a test to see if I can actually make a wordle clone
// I will be making the actual calculator version later.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WORD_COUNT 5

// Booleans
#define true 1
#define false 0

// Check for if a word contains a character
int letterInWord(char letter, char word[6])
{
	// Loop through every character in the word
	for (size_t i = 0; i < 5; i++)
	{
		if (letter == word[i]) return true;
	}

	return false;
}

//! debug thing to print array
void printArray(int array[])
{
	printf("%d, %d, %d, %d, %d\n", array[0], array[1], array[2], array[3], array[4], array[5]);
}
void printArray(char array[])
{
	printf("%c, %c, %c, %c, %c\n", array[0], array[1], array[2], array[3], array[4], array[5]);
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
		int wrongPlace[5] = { false, false, false, false, false };
		int notInWord[5] = { false, false, false, false, false };
		int correct[5] = { false, false, false, false, false };

		// Loop through each character in the word
		for (size_t i = 0; i < 5; i++)
		{
			// Check for if the current letter is in the correct position
			if (input[i] == word[i]) correct[i] = true;
			else if (letterInWord(input[i], word)) wrongPlace[i] = true;
			else notInWord[i] = true;
		}

		printArray(word);
		printArray(input);
		printArray(wrongPlace);
		printArray(notInWord);
		printArray(correct);

		// Check for if they win
		if (correct[0] && correct[1] && correct[2] && correct[3] && correct[5])
		{
			printf("win");
			break;
		}
	}
	


	
	return 0;
}