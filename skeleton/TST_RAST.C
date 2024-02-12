#include <osbind.h>
#include "raster.h"
#include "font.h"

#define SCREEN_HEIGHT 400
#define SCREEN_WIDTH 640
#define TEST_BITMAP_HEIGHT 13

int main()
{
	UINT16 *base = Physbase();

	int testBitmap[TEST_BITMAP_HEIGHT] =
	{
		0x0000,
		0x0810,
		0x0810,
		0x0420,
		0x0240,
		0x1FF8,
		0x2004,
		0x4662,
		0x4002,
		0x43C2,
		0x2424,
		0x1008,
		0x0FF0,
	};

	/*Plots "Space" in the top left corner*/
	plot_bitmap_8(base, 0, 0, font, FONT_HEIGHT);

	plot_bitmap_16(base, 320, 200, testBitmap, TEST_BITMAP_HEIGHT);

	return 0;
}
