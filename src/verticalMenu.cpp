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
			dbg_printf("%d\n", itemsLength);
		}

		// Update the menu logic
		void Update(uint8_t key) {

			// Check for if the user "scrolls"
			if (key == sk_Up) index--;
			else if (key == sk_Down) index++;

			// Clamp the index to how many menu items there are
			if (index == 255) index = 0;
			else if (index > itemsLength - 1) index = itemsLength - 1;
		}

		// Draw the menu
		void Render() {
			
			uint8_t scale = 1;
			
			// Render the 3 elements above around the index
			// (one above, and one below)
			for (uint8_t i = 0; i < itemsLength; i++) {

				// Choose how each of the 3 elements should be rendered
				if (i == index - 1 || i == index + 1) {

					// Top/bottom items
					scale = 1;
				}
				else if (i == index) scale = 2;
				else continue;

				// Render the text
				gfx_SetTextScale(scale, scale);
				gfx_PrintStringXY(items[i].displayName, x, y + (i - index) * 20);
			}
			



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

		uint8_t x = 20;
		uint8_t y = 20;

		// Linear interpolation
		uint8_t lerp(uint8_t start, uint8_t end, uint8_t percentage) {

			return start + (end - start) * percentage;
		}
};