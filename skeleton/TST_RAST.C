#include <osbind.h>
#include "raster.h"

int main()
{
	void *base = Physbase();

	plot_bitmap_1(base, 100, 100);
	plot_bitmap_2(base, 200, 200);

	return 0;
}
