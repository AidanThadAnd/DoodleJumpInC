/*
  Author: Aidan & Jacky
  Date: March 15, 2024
 
  Purpose:
    - This header file defines functions related to managing music in the game.
 
  Functions:
    Function Name: start_music
      Purpose:
        - Starts playing the game music.
 
    Function Name: update_music
      Purpose:
        - Advances to the next note of the song as determined by the amount of time
          that a note lasts.

    Function Name: stop_music
      Purpose:
        - Stop all sounds that the music is playing
 */
#ifndef MUSIC_H
#define MUSIC_H

#include "psg.h"
#include "vbl.h"
#include "types.h"

#define WHOLE_NOTE 128     
#define HALF_NOTE 64        
#define QUARTER_NOTE 32     

/*no sound*/
#define REST 0

#define C_FLAT 478
#define C_SHARP 451
#define D_FLAT 426
#define D_SHARP 402
#define E_FLAT 379
#define F_FLAT 358
#define F_SHARP 338
#define G_FLAT 319
#define G_SHARP 301
#define A_FLAT 284
#define A_SHARP 268
#define B_FLAT 253

void start_music();
void update_music();
void stop_music();

#endif
