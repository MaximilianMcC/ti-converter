#include <stdio.h>
#include <tice.h>
#include <graphx.h>
#include <debug.h>
#include "verticalMenu.cpp"


// Colors
#define BACKGROUND 0
#define FOREGROUND 223 //! 255 is transparent so use this


int main(void) {
	dbg_printf("[Converter] Running\n");
	gfx_Begin();


	//! test stuff
	Object testItems[] = {
		{ "Milliseconds", "ms" },
		{ "Seconds", "s" },
		{ "Minutes", "m" },
		{ "Hours", "h" },
		{ "Days", "d" }
	};
	uint8_t testItemsLength = sizeof(testItems) / sizeof(testItems[0]);
	VerticalMenu testMenu(testItems, testItemsLength);



	// Main loop
	while (true) {

		// Get keyboard input
		uint8_t key = os_GetCSC();
		if (key == sk_Clear) break;


		testMenu.Update(key);


		// Clear screen for drawing the next frame
		gfx_FillScreen(BACKGROUND);

		testMenu.Render();
		
		// Update the screen
		gfx_SwapDraw();
	}



	// End
	gfx_End();
	return 0;
}
