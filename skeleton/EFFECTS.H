#ifndef EFFECTS_H
#define EFFECTS_H

#include "psg.h"
#include "types.h"
#include "vbl.h"
#include "isr.h"

/*asynchronously activated effects*/
void doodle_lands();
void doodle_attacked();

/*synchronous controller*/
int update_sndfx();

/*helper methods*/
void stop_effects();

#endif
