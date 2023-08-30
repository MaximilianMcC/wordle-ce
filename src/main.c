#include <stdio.h>
#include <ctype.h>
#include <tice.h>
#include <graphx.h>
#include <sys/timers.h>
#include <debug.h> //TODO: Remove this when done

int main(void) {

	gfx_Begin();

	dbg_printf("Running\n");

	char input[6] = ""; //? makes it all null terminators: "\0\0\0\0\0\0"
	short letterIndex = 0;

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

		// Add the letter to the index
		if (letter != '\0' && letterIndex < 5)
		{
			input[letterIndex] = letter;
			letterIndex++;
		}
		


		// Clear screen for drawing next frame
		gfx_FillScreen(255);

		// TODO: Draw a title of some sorts
		// TODO: Instructions and information

		// Draw the 6x5 boxes for the words to go into
		// TODO: Make everything in the middle
		short x = 0, y = 0;
		short drawLetterIndex = 0;

		for (short i = 0; i < 6; i++)
		{
			y += 30;
			for (short j = 0; j < 5; j++)
			{
				// Draw the box
				gfx_Rectangle(x, y, 25, 25);

				// Draw the current letter
				gfx_SetTextXY((x + 8), (y + 8));
				gfx_PrintChar(toupper(input[drawLetterIndex]));

				// Increase the x position, and move to the next character
				x += 30;
				drawLetterIndex++;
			}

			// Reset for a new word
			x = 0;
			drawLetterIndex = 0;
		}


		// Update screen
		gfx_SwapDraw();
	}

	// End
	gfx_End();
	return 0;
}
