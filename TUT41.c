#include <osbind.h>

#define INVADER_HEIGHT 16
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400

typedef unsigned int UINT16;

void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, unsigned int height);


int main()
{
	UINT16 *base = Physbase();
	
	int x = 0;
	
	int invader_bitmap[INVADER_HEIGHT] =
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
	
		plot_bitmap_16(base, 0, 0, invader_bitmap, INVADER_HEIGHT);
		
	return 0;
}

void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, unsigned int height)
{
	int i=0;
	
	while(i<height)
	{
		*(base + i*40) = bitmap[i];
		i++;
	}
}