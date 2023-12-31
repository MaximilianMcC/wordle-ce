#include <stdio.h>
#include <tice.h>
#include <ctype.h>
#include <graphx.h>
#include <time.h>
#include <string.h>
#include <debug.h>
#include "words.h"


// Game settings
#define MAX_TURNS 6
#define WORD_LENGTH 5

// Drawing dimensions
#define BOX_SIZE 25
#define PADDING 10
#define TEXT_OFFSET 5
#define NOTIFICATION_DURATION 2 //? Measured in seconds
#define NOTIFICATION_HEIGHT 16

// Colors
#define BACKGROUND 0
#define FOREGROUND 223 //! 255 is transparent, so using 245
#define NOTIFICATION_BACKGROUND 223
#define NOTIFICATION_FOREGROUND 0
#define OUTLINE 10
#define CORRECT 67
#define WRONG_PLACE 229
#define NOT_IN_WORD 74


// Clamp a number between a lower and upper value
short clamp(short value, short min, short max)
{
	if (value > max) return max;
	if (value < min) return min;
	return value;
}

// Check for if a word contains a character
short letterInWord(char letter, char word[5])
{
	// Loop through every character in the word
	for (short i = 0; i < WORD_LENGTH; i++)
	{
		if (letter == word[i]) return true;
	}

	return false;
}

// Check for if the word is in the word list
bool wordInList(char word[6])
{
	// Loop through each word in the word list
	for (int i = 0; i < wordCount; i++)
	{
		if (strcmp(words[i], word) == 0) return true;
	}
	
	// Wasn't found
	return false;
}

// Notification timing systems and other notification stuff
// TODO: Don't make these variables public and stuff
char notificationText[30];
bool showNotification = false;
unsigned int notificationStartTime;

// Set the notification
void SetNotification(char text[30])
{
    // Set the notification text
    strncpy(notificationText, text, sizeof(notificationText) - 1);

	// Setup the notification timing
	notificationStartTime = rtc_Time();
	showNotification = true;
}

// Show a notification in the top of the screen if its possible
void displayNotification()
{
	if (showNotification)
	{
		// Get the elapsed time
		unsigned int currentTime = rtc_Time();
		unsigned int elapsedTime = currentTime - notificationStartTime;

		// Check for if the time is up or not
		if (elapsedTime >= NOTIFICATION_DURATION)
		{
			// Reset everything
			showNotification = false;
			notificationStartTime = 0;
			return;
		}
	}
	else return;

	// Calculate the width based on the text width and padding
	gfx_SetTextScale(1, 1);
	short width = 0, textWidth = 0;
	for (unsigned int i = 0; i < strlen(notificationText); i++)
	{
		textWidth += gfx_GetCharWidth(notificationText[i]);
	}
	width = PADDING + textWidth + PADDING;

	// Get the draw positions
	short x = (LCD_WIDTH - width) / 2;
	short y = 15;

	// Draw the background
	gfx_SetColor(NOTIFICATION_BACKGROUND);

	// Rounded corners (circles)
	gfx_FillCircle(x, (y + (NOTIFICATION_HEIGHT / 2)), (NOTIFICATION_HEIGHT / 2) - 1);
	gfx_FillCircle((x + width), (y + (NOTIFICATION_HEIGHT / 2)), (NOTIFICATION_HEIGHT / 2) - 1);

	// Main background 
	gfx_FillRectangle(x, y, width, NOTIFICATION_HEIGHT);
	
	// Draw the text
	gfx_SetTextFGColor(NOTIFICATION_FOREGROUND);
	gfx_PrintStringXY(notificationText, (x + PADDING), (y + TEXT_OFFSET));
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
	dbg_printf("[Wordle] Loaded %d words.\n", wordCount);
	gfx_Begin();



	// Handle all of the words and stuff
	short turn = 0;
	short inputIndex = 0;
	struct Word inputs[MAX_TURNS];

	// Game state stuff
	bool won = false;
	bool gameOver = false;


	
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
	

	// Set the random seed as the current time
	srand(time(NULL));

	// Get a random word from the word array
	char word[6];
	int index = rand() % wordCount;
	snprintf(word, 6, "%s", words[index]);
	dbg_printf("[Wordle] Selected word \"%s\"\n", word);


	// Main loop
	while (true) {

		// Get keyboard input
		uint8_t key = os_GetCSC();
		if (key == sk_Clear) break;

		// Stop doing stuff if the game is over
		if (gameOver == false)
		{
			// Convert the key to c char using the index of a string
			const char *chars = "\0\0\0\0\0\0\0\0\0\0\0wrmh\0\0\0\0vqlg\0\0\0zupkfc\0\0ytojeb\0\0xsnida\0\0\0\0\0\0\0\0";
			char letter = chars[key];

			// Add or remove a character from the current word
			if (letter != '\0' && inputIndex < WORD_LENGTH)
			{		
				// Add the new letter at the current index
				inputs[turn].input[inputIndex] = letter;

				// Increase the index for the next letter
				inputIndex = clamp((inputIndex + 1), 0, WORD_LENGTH);
			}
			else if (key == sk_Del && inputIndex >= 0)
			{
				// Decrease the index to get back to the previous letter
				inputIndex = clamp((inputIndex - 1), 0, WORD_LENGTH);

				// Make the letter at the new index nothing
				inputs[turn].input[inputIndex] = '\0';
			}

			// Submit the current guess 
			if (key == sk_Enter && inputIndex >= WORD_LENGTH)
			{
				// Check for if the word is in the word list
				if (wordInList(inputs[turn].input) == true)
				{
					dbg_printf("[Wordle] Valid word entered.\n");
					// Loop through each character in the word and check its status
					for (short i = 0; i < WORD_LENGTH; i++)
					{
						if (inputs[turn].input[i] == word[i]) inputs[turn].correct[i] = true;
						else if (letterInWord(inputs[turn].input[i], word)) inputs[turn].wrongPlace[i] = true;
						else inputs[turn].notInWord[i] = true;
					}
					

					// Check for if they won
					won = (inputs[turn].correct[0] == true && inputs[turn].correct[1] == true && inputs[turn].correct[2] == true && inputs[turn].correct[3] == true && inputs[turn].correct[4] == true);
					if (won)
					{
						gameOver = true;
						SetNotification("Correct!");
					}

					// Increase the turn
					turn++;
					inputIndex= 0;
				}
				else
				{
					dbg_printf("[Wordle] Incorrect word entered.\n");
					// Reset the current input for the turn
					strncpy(inputs[turn].input, "\0", 6);
					inputIndex = 0;

					// Show a notification saying that the word is wong
					SetNotification("Word not in list!");
				}
			}

			// Check for if the game has ended by running out of turns
			if (turn >= MAX_TURNS) 
			{
				dbg_printf("[Wordle] Game over. (Ran out of turns)");
				gameOver = true;
				SetNotification(word);
			}
		}

		// Clear screen for drawing the next frame
		gfx_FillScreen(BACKGROUND);

		// Draw a title and a line under it
		gfx_SetTextScale(2, 2);
		gfx_SetTextFGColor(FOREGROUND);
		gfx_PrintStringXY("Wordle", 115, 5);
		gfx_SetColor(OUTLINE);
		gfx_Line(0, BOX_SIZE, LCD_WIDTH, BOX_SIZE);

		// Get dimensions and stuff
		short x = 78; //? origin to start in the middle
		short y = 30;

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
				gfx_SetTextFGColor(FOREGROUND);
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

		// Show the notifications if there are any
		displayNotification();
		
		// Update the screen
		gfx_SwapDraw();
	}



	// End
	gfx_End();
	return 0;
}
