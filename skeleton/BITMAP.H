#ifndef BITMAP_H
#define BITMAP_H

#include "types.h"

#define DOODLE_BITMAP_HEIGHT 64
#define MONSTER_BITMAP_HEIGHT 64
#define PLATFORM_BITMAP_HEIGHT 24

extern const UINT32 doodle_bitmap []; 
extern const UINT32 monster_bitmap []; 
extern const UINT32 platform_bitmap []; 
extern const UINT32 broken_platform_bitmap []; 
extern const UINT32 clear_bitmap[];

#endif