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
#define CORRECT 71
#define WRONG_PLACE 229
#define NOT_IN_WORD 117


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
	for (size_t i = 0; i < 5; i++)
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
	struct Word inputs[MAX_TURNS];

	

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


		// Clear screen for drawing next frame
		gfx_FillScreen(BACKGROUND);


		// Get dimensions and stuff
		// TODO: Hardcode because all calculators have the same size screen
		short x = 86; //? origin to start in the middle (i think)
		short y = PADDING;

		// Draw the boxes
		for (short i = 0; i < MAX_TURNS; i++)
		{

			// Get the word/input at the current index
			struct Word currentWord = inputs[turn];

			for (short j = 0; j < WORD_LENGTH; j++)
			{

				// Draw the box background for the current character
				gfx_SetColor(BACKGROUND);
				gfx_FillRectangle(x, y, BOX_SIZE, BOX_SIZE);

				// Draw the box outline for the current character
				gfx_SetColor(FOREGROUND);
				gfx_Rectangle(x, y, BOX_SIZE, BOX_SIZE);
				

				// Print the current character
				gfx_SetTextFGColor(254);
				gfx_SetTextScale(2, 2);
				gfx_SetTextXY((x + TEXT_OFFSET), (y + TEXT_OFFSET));
				// gfx_PrintChar(toupper(currentWord.input[j]));
				gfx_PrintChar("A");

				dbg_printf("drawing box at %d, %d\n", x, y);


				// Increase the x position for drawing the next box
				x += BOX_SIZE + PADDING;
			}

			// Increase the y position for drawing the next word
			y += BOX_SIZE + PADDING;

			// Reset the x stuff for the drawing the next word
			x = 86;
		}
		

		// Update screen
		gfx_SwapDraw();
	}

	// End
	gfx_End();
	return 0;
}
