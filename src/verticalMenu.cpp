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
		}

		// Update the menu logic
		uint8_t Update(uint8_t key) {

			// Check for if the user "scrolls"
			if (key == sk_Up) index--;
			else if (key == sk_Down) index++;

			// Clamp the index to how many menu items there are
			if (index == 255) index = 0;
			else if (index > itemsLength - 1) index = itemsLength - 1;

			// Check for if the user selects an option
			if (key == sk_Enter) return index;
			
			// Nothing was pressed
			return NULL;
		}

		//todo: final y then the initial y as a and b then use time make it 4 seconds or smth idk for the lerping (lerp it)

		// Draw the menu
		void Render() {
			
			// Render the 3 elements above around the index
			// (one above, and one below)
			for (uint8_t i = 0; i < itemsLength; i++) {

				// Default values
				uint8_t scale = 1;
				uint8_t color = NOT_SELECTED_COLOR;


				// Choose how the current element should be rendered
				if (i == index) {

					// Middle/selected item
					color = SELECTED_COLOR;
					scale = 2;
				}
				else if (i != index - 1 || i != index + 1) continue;
				
				// Apply the text decoration
				gfx_SetTextFGColor(color);
				gfx_SetTextScale(scale, scale);

				// Get the length of the current text for rendering
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
				else if (position == RIGHT) x = LCD_WIDTH - textWidth - ((LCD_WIDTH / 2) - textWidth) / 2;


				// Render the text
				// TODO: Lerp it to make it look like its sliding/scrolling smoothly
				gfx_PrintStringXY(items[i].displayName, x, (y + (i - index) * 20));
			}
		}



	private:
		uint8_t index = 0;

		Object* items;
		uint8_t itemsLength;

		MenuPosition position;

		// Linear interpolation
		uint8_t lerp(uint8_t start, uint8_t end, uint8_t percentage) {

			return start + (end - start) * percentage;
		}
};