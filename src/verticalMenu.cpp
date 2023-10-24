#include <stdio.h>
#include <tice.h>
#include <graphx.h>
#include <debug.h>
#include "object.cpp"

class VerticalMenu {

	public:

		VerticalMenu(Object menuItems[], uint8_t menuItemsLength) {

			// Set up menu items
			items = menuItems;
			itemsLength = menuItemsLength;
			dbg_printf("Loaded %d items.", menuItemsLength);
		}

		// Update the menu logic
		void Update(uint8_t key) {

			// Check for if the user "scrolls"
			if (key == sk_Up) index++;
			else if (key == sk_Down) index--;

			// Clamp the index to how many menu items there are
			if (index == 255) index = 0;
			else if (index > itemsLength) index = itemsLength;
		}

		// Draw the menu
		void Render() {
			
			// green
			gfx_SetTextFGColor(167);



			//! debug
			// Draw the menu index
			char indexString[4];
			sprintf(indexString, "%d", index);
			gfx_PrintStringXY(indexString, 0, 0);
		}



	private:
		uint8_t index = 1;

		Object* items;
		uint8_t itemsLength;
};