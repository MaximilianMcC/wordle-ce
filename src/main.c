#include <ti/screen.h>
#include <ti/getcsc.h>
#include <stdlib.h>

int main(void)
{
	// Clear the screen
	os_ClrHome();
	
	
	// Hello world
	os_PutStrFull("Hello, world!");

	// Wait for a key to be pressed before exiting
    while (!os_GetCSC());
	return 0;
}