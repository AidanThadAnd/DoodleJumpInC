#ifndef BITMAP_H
#define BITMAP_H

#include "types.h"

#define DOODLE_HEIGHT 55
#define DOODLE_WIDTH 32
#define DOODLE_LEG_WIDTH 48

#define MONSTER_HEIGHT 35
#define MONSTER_WIDTH 40

#define PLATFORM_HEIGHT 22
#define PLATFORM_WIDTH 30



extern const UINT32 doodle_bitmap_right []; 
extern UINT32 doodle_bitmap_left[];
extern const UINT32 monster_bitmap []; 
extern const UINT32 platform_bitmap []; 
extern const UINT32 broken_platform_bitmap []; 
extern const UINT32 clear_bitmap[];

#endif
