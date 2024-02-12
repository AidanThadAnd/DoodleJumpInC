#include <osbind.h>
#include "raster.h"
#include "font.h"

int main()
{
	UINT16 *base = Physbase();

	plot_bitmap_8(base, 0, 0, font, FONT_HEIGHT);

	return 0;
}
