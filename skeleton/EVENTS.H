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
*/

#ifndef EVENTS_H
#define EVENTS_H

#include "model.h"

void press_key(Doodle *character, char key);
int check_collision_doodle_platform(Doodle *doodle, Platform *platform);

#endif

