#include <stdio.h>
#include <tice.h>
#include <graphx.h>
#include <time.h>
#include <string.h>
#include <debug.h>
#include "object.cpp"

class VerticalMenu {

	// Colors
	#define SELECTED_COLOR 0
	#define NOT_SELECTED_COLOR 53

	public:

		enum MenuPosition {
			LEFT,
			RIGHT,
			CENTRE
		};

		VerticalMenu(Object menuItems[], uint8_t menuItemsLength, MenuPosition menuPosition) {

			// Set up menu items
			items = menuItems;
			itemsLength = menuItemsLength;
			position = menuPosition;

			// Setup graphics stuff
			// TODO: Change color and stuff to fit more with the default calculator UI
			gfx_SetTextFGColor(167); //? green
		}

		// Update the menu logic
		void Update(uint8_t key) {

			// Check for if the user "scrolls"
			if (key == sk_Up) {

				index--;
				lastTimeIndexUpdated = rtc_Time();

			} else if (key == sk_Down) {

				index++;
				lastTimeIndexUpdated = rtc_Time();
			}

			// Clamp the index to how many menu items there are
			if (index == 255) index = 0;
			else if (index > itemsLength - 1) index = itemsLength - 1;
		}

		//todo: final y then the initial y as a and b then use time make it 4 seconds or smth idk for the lerping

		// Draw the menu
		void Render() {
			
			uint8_t scale = 1;
			
			// Render the 3 elements above around the index
			// (one above, and one below)
			for (uint8_t i = 0; i < itemsLength; i++) {

				// Choose how each of the 3 elements should be rendered
				if (i == index - 1 || i == index + 1) {

					// Top/bottom items
					gfx_SetTextFGColor(NOT_SELECTED_COLOR);
					scale = 1;
				}
				else if (i == index) {

					// Middle/selected item
					gfx_SetTextFGColor(SELECTED_COLOR);
					scale = 2;
				}
				else continue;

				// Get the length of the current text for rendering
				gfx_SetTextScale(scale, scale);
				uint8_t textWidth = 0;
				for (uint8_t j = 0; j < strlen(items[i].displayName); j++)
				{
					textWidth += gfx_GetCharWidth(items[i].displayName[j]);
				}
				

				// Check for where the menu needs to be rendered
				uint8_t x = 0;
				uint8_t y = 50;
				if (position == CENTRE) x = (LCD_WIDTH - textWidth) / 2;
				else if (position == LEFT) x = ((LCD_WIDTH / 2) - textWidth) / 2;
				// else if (position == RIGHT) x = ((LCD_WIDTH / 2) - textWidth) / 2;
				// else if (position == RIGHT) x = ();


				// Render the text
				// TODO: Lerp it to make it look like its sliding/scrolling smoothly
				gfx_PrintStringXY(items[i].displayName, x, (y + (i - index) * 20));
			}
		}



	private:
		uint8_t index = 0;
		uint16_t lastTimeIndexUpdated;

		Object* items;
		uint8_t itemsLength;

		MenuPosition position;

		// Linear interpolation
		uint8_t lerp(uint8_t start, uint8_t end, uint8_t percentage) {

			return start + (end - start) * percentage;
		}
};