#include <stdio.h>
#include <ctype.h>
#include <tice.h>
#include <graphx.h>
#include <sys/timers.h>

int main(void) {

	gfx_Begin();
	int count = 0;

	// Main loop
	while (true) {

		// Get keyboard input
		uint8_t key = os_GetCSC();

		// Check for if they want to exit
		if (key == sk_Clear) break;



		// Turn the int to a string
		char number[10];
		real_t temp = os_Int24ToReal(count);
		os_RealToStr(number, &temp, 10, 1, 0);

		char input[6] = "stray";

		// Clear screen for drawing next frame
		gfx_FillScreen(255);

		// TODO: Draw a title of some sorts
		// TODO: Instructions and information

		// Draw the 6x5 boxes for the words to go into
		short x = 0, y = 0;
		short letterIndex = 0;

		for (short i = 0; i < 6; i++)
		{
			y += 30;
			for (short j = 0; j < 5; j++)
			{
				// Draw the box
				gfx_Rectangle(x, y, 25, 25);

				// Draw the current letter
				gfx_SetTextXY((x + 8), (y + 8));
				gfx_PrintChar(toupper(input[letterIndex]));

				x += 30;
				letterIndex++;
			}

			// Reset for a new column
			x = 0;
			letterIndex = 0;
		}


		// Update screen
		gfx_SwapDraw();
	}

	// End
	gfx_End();
	return 0;
}
