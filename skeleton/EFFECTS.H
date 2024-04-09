#ifndef EFFECTS_H
#define EFFECTS_H

#include "psg.h"
#include "types.h"
#include "vbl.h"
#include "isr.h"

/*asynchronously activated effects*/
void doodle_lands();
void platform_breaks();
void monster_near();

void stop_effects();

#endif
