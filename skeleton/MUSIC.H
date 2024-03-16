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
        - Updates the game music based on the elapsed time.
      Input:
        - time_elapsed: The time elapsed since the last update, in milliseconds.
 */

#ifndef MUSIC_H
#define MUSIC_H

void start_music();
void update_music(unsigned int time_elapsed);

#endif
