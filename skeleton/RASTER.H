#ifndef RASTER_H
#define RASTER_H

#include "stdio.h"
#include "linea.h"
#include "osbind.h"

/* [TO DO] the functions below are examples. Replace them! */

void plot_bitmap_1(UINT16 *base, int x, int y, ...);
void plot_bitmap_2(UINT32 *base, int x, int y, ...);
void plotHorizontalLine(UINT8 *base, int y);
void clearHorizontalLine8(UINT8* base, int x, int y, int length);
void clearScreen(UINT8 *base);

#endif
