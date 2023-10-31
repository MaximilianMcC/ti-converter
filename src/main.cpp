#include <stdio.h>
#include <tice.h>
#include <graphx.h>
#include <debug.h>
#include "verticalMenu.cpp"


// Colors
#define BACKGROUND 223
#define FOREGROUND 0


int main(void) {
	dbg_printf("[Converter] Running\n");
	gfx_Begin();



	// Different measurement
	Object measurements[] = {
		{ "Distance", "d" },
		{ "Time", "t" },
		{ "Speed", "s" },
		{ "Electricity", "e" }
	};
	uint8_t measurementsLength = sizeof(measurements) / sizeof(measurements[0]);
	VerticalMenu measurementsMenuTo(measurements, measurementsLength, VerticalMenu::LEFT, 100);
	VerticalMenu measurementsMenuFrom(measurements, measurementsLength, VerticalMenu::RIGHT, 100);


	// Main loop
	while (true) {

		// Get keyboard input
		uint8_t key = os_GetCSC();
		if (key == sk_Clear) break;

		// TODO: Make a way to toggle between left and right
		uint8_t selectionTo = measurementsMenuTo.Update(key);
		uint8_t selectionFrom = measurementsMenuFrom.Update(key);
		
		if (selectionTo != 0) dbg_printf("to %d\n", selection);
		if (selectionFrom != 0) dbg_printf("from %d\n", selection);

		// Clear screen for drawing the next frame
		gfx_FillScreen(BACKGROUND);

		measurementsMenuTo.Render();
		measurementsMenuFrom.Render();

		// Update the screen
		gfx_SwapDraw();
	}



	// End
	gfx_End();
	return 0;
}
