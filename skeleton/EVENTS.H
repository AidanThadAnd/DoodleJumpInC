/*
Author: Aidan & Jacky
Date: Feb 5, 2024

Purpose:
    - Defines functions related to handling events in the game.

Functions:
    Function Name: press_key
        Purpose:
            - Update the state of the Doodle character based on a key press.
        Input:
            - character: Pointer to the Doodle structure.
            - key: The character representing the pressed key.
        Output:
            - The state of the Doodle character is updated based on the key press.

    Function Name: check_collision_doodle_platform
        Purpose:
            - Check for collision between the Doodle and a Platform.
        Input:
            - doodle: Pointer to the Doodle structure.
            - platform: Pointer to the Platform structure.
        Output:
            - Returns 1 if a collision is detected, 0 otherwise.

    Function Name: check_collision_monster
        Purpose:
            - Determine if there is a collision between the Doodle and a Monster.
        Input:
            - d: Pointer to the Doodle structure.
            - m: Pointer to the Monster structure.
        Output:
            - Returns 1 if a collision is detected, 0 otherwise.
*/

#ifndef EVENTS_H
#define EVENTS_H

#include "MODEL.H"
#include "system.h"
#include "TYPES.H"
#include "BITMAP.H"


void doodle_input(Doodle *character, char key);
bool check_collision_doodle_platform(Doodle *d, Platform *p);
bool check_collision_monster(Doodle *d, Monster *m);
void doodle_vertical_movement(Doodle *doodle);
bool is_doodle_falling(Doodle *doodle);

#endif

