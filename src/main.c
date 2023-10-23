#include <stdio.h>
#include <tice.h>
#include <graphx.h>
#include <debug.h>


// Colors
#define BACKGROUND 0
#define FOREGROUND 223 //! 255 is transparent so use this


int main(void) {
	dbg_printf("[Converter] Running\n");
	gfx_Begin();

	// Main loop
	while (true) {

		// Get keyboard input
		uint8_t key = os_GetCSC();
		if (key == sk_Clear) break;


		// Clear screen for drawing the next frame
		gfx_FillScreen(BACKGROUND);

		gfx_SetTextFGColor(FOREGROUND);
		gfx_PrintStringXY("Converter", 10, 10);

		
		// Update the screen
		gfx_SwapDraw();
	}



	// End
	gfx_End();
	return 0;
}
