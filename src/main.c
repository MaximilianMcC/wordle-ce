#include <ti/screen.h>
#include <ti/getcsc.h>
#include <graphx.h>
#include <stdlib.h>

#include "words.h"



int main(void)
{
	// Setup
	os_ClrHome();
	gfx_Begin();
	




	// Get the list of words
	gfx_PrintString(words[0]);




	

	// Wait for a key to be pressed before exiting
    while (!os_GetCSC());
	gfx_End();
	return 0;
}