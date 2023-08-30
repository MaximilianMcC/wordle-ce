#include <stdio.h>
#include <tice.h>
#include <graphx.h>
#include <sys/timers.h>

int main(void) {

	gfx_Begin();
	int count = 0;

	// Main loop
	while (os_GetCSC() != sk_Clear) {

		// Get keyboard input
		uint8_t key = os_GetCSC();

		// Check for what key was pressed
		if (key == sk_Add) count++;
		else if (key == sk_Sub) count--;


		// Clear screen for drawing next frame
		gfx_FillScreen(255);

		// Turn the int to a string
		char number[10];
		real_t temp = os_Int24ToReal(count);
		os_RealToStr(number, &temp, 10, 1, 0);

		// Print the value
		gfx_SetTextScale(2, 2);
		gfx_PrintStringXY(number, 25, 25);

		// Update screen
		gfx_SwapDraw();

		// Wait to avoid skipping input
		sleep(50);
	}

	// End
	gfx_End();
	return 0;
}
