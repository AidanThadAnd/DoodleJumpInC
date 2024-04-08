/*
Author: Aidan & Jacky
Date: Feb 5, 2024

Purpose:
    - Defines functions related to game events, such as doodle movement, collision detection, and game state updates.

Functions:
    Function Name: check_doodle_death
        Purpose:
            - Checks if the doodle has died.
        Details:
            - Checks if the doodle has fallen below the screen height or collided with the monster. Updates the endGame flag accordingly if the doodle is dead.
        Parameters:
            - model: Pointer to the game model.
            - endGame: Pointer to a boolean indicating game end.

    Function Name: doodle_input
        Purpose:
            - Handles user input for doodle movement.
        Details:
            - Moves the doodle left or right based on the pressed key. If the doodle is dead, no movement is allowed.
        Parameters:
            - character: Pointer to the doodle object.
            - key: Character representing the pressed key.

    Function Name: replace_off_screen
        Purpose:
            - Replaces off-screen platforms and the monster.
        Details:
            - Moves off-screen platforms and the monster to a new position horizontally based on a random seed.
        Parameters:
            - model: Pointer to the game model.
            - seed: Random seed for platform replacement.

    Function Name: check_collision_doodle_platform
        Purpose:
            - Checks collision between doodle and platforms.
        Details:
            - Checks if the doodle collides with any of the platforms.
        Parameters:
            - doodle: Pointer to the doodle object.
            - platform: Pointer to the array of platform objects.
        Returns:
            - bool: True if collision occurs, false otherwise.

    Function Name: check_collision_monster
        Purpose:
            - Checks collision between doodle and monster.
        Details:
            - Checks if the doodle collides with the monster.
        Parameters:
            - doodle: Pointer to the doodle object.
            - monster: Pointer to the monster object.
        Returns:
            - bool: True if collision occurs, false otherwise.

    Function Name: shift_screen_to_doodle
        Purpose:
            - Shifts the screen based on doodle movement.
        Details:
            - Moves platforms and the monster vertically relative to the doodle's movement. Updates the game score accordingly.
        Parameters:
            - model: Pointer to the game model.

    Function Name: doodle_vertical_movement
        Purpose:
            - Handles vertical movement of the doodle.
        Details:
            - Handles doodle's vertical movement, including falling, jumping, and collision detection with platforms.
        Parameters:
            - model: Pointer to the game model.
*/

#ifndef EVENTS_H
#define EVENTS_H

#include "MODEL.H"
#include "system.h"
#include "TYPES.H"
#include "BITMAP.H"
#include <math.h>
#define MAX_VELOCITY 14


void doodle_input(Doodle *character, char key);
bool check_collision_doodle_platform(Doodle *d, Platform *p);
bool check_collision_monster(Doodle *d, Monster *m);
void doodle_vertical_movement(Model *model);
void shift_screen_to_doodle(Model *model);
void replace_off_screen(Model *model, int seed);
void check_doodle_death(Model *model, bool *endGame);

#endif

