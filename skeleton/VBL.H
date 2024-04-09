#ifndef VBL_H
#define VBL_H

#include "ISR.H"
#include "types.h"
#include "effects.h"
#include "music.h"

/*--------- { Timers } ----------*/
extern int TIMER_LANDED; 

/*sound*/
extern int TIMER_MUSIC;
extern int TIMER_SNDFX;

void do_vbl_isr();

#endif
