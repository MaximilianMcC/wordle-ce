#include <stdio.h>
#include <ctype.h>
#include <tice.h>
#include <graphx.h>
#include <sys/timers.h>
#include <debug.h> //TODO: Remove this when done


// Game settings
#define MAX_TURNS 6
#define WORD_LENGTH 5

// Drawing dimensions
#define BOX_SIZE 25
#define PADDING 10
#define TEXT_OFFSET 5 //TODO: Use maths to make this real

// Colors
#define BACKGROUND 32
#define FOREGROUND 254 // 255 is transparent, so using 245
#define OUTLINE 74
#define CORRECT 67
#define WRONG_PLACE 229
#define NOT_IN_WORD 32


// Clamp a number between a lower and upper value
short clamp(short value, short min, short max)
{
	if (value > max) return max;
	if (value < min) return min;
	return value;
}

// Check for if a word contains a character
short letterInWord(char letter, char word[6])
{
	// Loop through every character in the word
	for (short i = 0; i < WORD_LENGTH; i++)
	{
		if (letter == word[i]) return true;
	}

	return false;
}



// Word
struct Word
{
	char input[6];
	short wrongPlace[5];
	short notInWord[5];
	short correct[5];
};



int main(void) {
	dbg_printf("[Wordle] Running\n");
	gfx_Begin();



	// Handle all of the words and stuff
	short turn = 0;
	short inputIndex = 0;
	struct Word inputs[MAX_TURNS];


	
	// Setup all of the structs
	// TODO: Find a better way to do this
	for (short i = 0; i < MAX_TURNS; i++)
	{
		inputs[i] = (struct Word) {
			.input = "\0",
			.wrongPlace = { false, false, false, false, false },
			.notInWord = { false, false, false, false, false },
			.correct = { false, false, false, false, false }
		};
	}
	


	// Get the word
	// TODO: Make this random
	char word[6] = "among";


	// Main loop
	while (true) {

		// Get keyboard input
		uint8_t key = os_GetCSC();
		if (key == sk_Clear) break;

		// Convert the key to a char
		char letter = '\0';
		switch (key)
		{
			case sk_Math:
				letter = 'a';
				break;

			case sk_Apps:
				letter = 'b';
				break;

			case sk_Prgm:
				letter = 'c';
				break;

			case sk_Recip:
				letter = 'd';
				break;

			case sk_Sin:
				letter = 'e';
				break;

			case sk_Cos:
				letter = 'f';
				break;

			case sk_Tan:
				letter = 'g';
				break;

			case sk_Power:
				letter = 'h';
				break;

			case sk_Square:
				letter = 'i';
				break;

			case sk_Comma:
				letter = 'j';
				break;

			case sk_LParen:
				letter = 'k';
				break;

			case sk_RParen:
				letter = 'l';
				break;

			case sk_Div:
				letter = 'm';
				break;

			case sk_Log:
				letter = 'n';
				break;

			case sk_7:
				letter = 'o';
				break;

			case sk_8:
				letter = 'p';
				break;

			case sk_9:
				letter = 'q';
				break;

			case sk_Mul:
				letter = 'r';
				break;

			case sk_Ln:
				letter = 's';
				break;

			case sk_4:
				letter = 't';
				break;
				
			case sk_5:
				letter = 'u';
				break;

			case sk_6:
				letter = 'v';
				break;

			case sk_Sub:
				letter = 'w';
				break;

			case sk_Store:
				letter = 'x';
				break;

			case sk_1:
				letter = 'y';
				break;

			case sk_2:
				letter = 'z';
				break;
		}

		// Add or remove a character from the current word
		if (letter != '\0' && inputIndex < WORD_LENGTH)
		{
			dbg_printf("[Wordle] Add letter (turn %d)\n", turn);
		
			// Add the new letter at the current index
			inputs[turn].input[inputIndex] = letter;

			// Increase the index for the next letter
			inputIndex = clamp((inputIndex + 1), 0, WORD_LENGTH);
		}
		else if (key == sk_Del && inputIndex >= 0)
		{
			dbg_printf("[Wordle] Remove letter (turn %d)\n", turn);

			// Decrease the index to get back to the previous letter
			inputIndex = clamp((inputIndex - 1), 0, WORD_LENGTH);

			// Make the letter at the new index nothing
			inputs[turn].input[inputIndex] = '\0';
		}

		// Submit the current guess 
		if (key == sk_Enter && inputIndex >= WORD_LENGTH)
		{
			// Check for if the game has ended
			if ((turn + 1) >= MAX_TURNS)
			{
				dbg_printf("[Wordle] Game finished.\n");
				break;
			}



			// Loop through each character in the word and check its status
			for (short i = 0; i < WORD_LENGTH; i++)
			{
				if (inputs[turn].input[i] == word[i]) inputs[turn].correct[i] = true;
				else if (letterInWord(inputs[turn].input[i], word)) inputs[turn].wrongPlace[i] = true;
				else inputs[turn].notInWord[i] = true;
			}
			


			// Increase the turn
			turn++;
			inputIndex= 0;
		}


		// Clear screen for drawing the next frame
		gfx_FillScreen(BACKGROUND);

		// Get dimensions and stuff
		// TODO: Hardcode because all calculators have the same size screen
		short x = 78; //? origin to start in the middle (i think)
		short y = PADDING;

		// Draw the boxes
		for (short i = 0; i < MAX_TURNS; i++)
		{
			for (short j = 0; j < WORD_LENGTH; j++)
			{

				// Get the box color
				gfx_SetColor(BACKGROUND);
				if (inputs[i].correct[j] == true) gfx_SetColor(CORRECT);
				else if (inputs[i].wrongPlace[j] == true) gfx_SetColor(WRONG_PLACE);
				else if (inputs[i].notInWord[j] == true) gfx_SetColor(NOT_IN_WORD);

				// Draw the box background for the current character
				gfx_FillRectangle(x, y, BOX_SIZE, BOX_SIZE);

				// Draw the box outline for the current character
				gfx_SetColor(OUTLINE);
				gfx_Rectangle(x, y, BOX_SIZE, BOX_SIZE);

				// Print the current character
				gfx_SetTextFGColor(254);
				gfx_SetTextScale(2, 2);
				gfx_SetTextXY((x + TEXT_OFFSET), (y + TEXT_OFFSET));
				gfx_PrintChar(toupper(inputs[i].input[j]));

				// Increase the x position for drawing the next box
				x += BOX_SIZE + PADDING;
			}

			// Increase the y position for drawing the next word
			y += BOX_SIZE + PADDING;

			// Reset the x stuff for the drawing the next word
			x = 78;
		}
		
		// Update the screen
		gfx_SwapDraw();
	}



	// End
	gfx_End();
	return 0;
}
