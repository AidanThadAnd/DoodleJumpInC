/*
Author: Aidan & Jacky
Date: Feb 5, 2024

Purpose:
    - Defines functions for initializing the game model, moving game objects, and checking object movements.

Functions:
    Function Name: initialize_model
        Purpose:
            - Initializes the game model with default values.
        Details:
            - Initializes the doodle character, platforms, and monster with their initial positions, velocities, and other attributes.
        Parameters:
            - model: Pointer to the game model to be initialized.
            - seed: Random seed for generating platform positions.

    Function Name: move_doodle
        Purpose:
            - Moves the doodle character.
        Details:
            - Moves the doodle character horizontally and vertically based on the given displacement. Updates the previous position and facing direction.
        Parameters:
            - doodle: Pointer to the doodle object to be moved.
            - displacement_x: Horizontal displacement.
            - displacement_y: Vertical displacement.
            - newFacing: New facing direction of the doodle.

    Function Name: move_platform_relative
        Purpose:
            - Moves a platform relative to its current position.
        Details:
            - Moves the platform horizontally and vertically relative to its current position. Updates the off-screen flag if the platform moves below the screen.
        Parameters:
            - platform: Pointer to the platform object to be moved.
            - displacement_x: Horizontal displacement.
            - displacement_y: Vertical displacement.
            - selected_platform: Index of the platform to be moved.

    Function Name: move_monster_relative
        Purpose:
            - Moves the monster relative to its current position.
        Details:
            - Moves the monster horizontally and vertically relative to its current position. Updates the off-screen flag if the monster moves below the screen.
        Parameters:
            - monster: Pointer to the monster object to be moved.
            - displacement_x: Horizontal displacement.
            - displacement_y: Vertical displacement.

    Function Name: move_monster_absolute
        Purpose:
            - Moves the monster to an absolute position.
        Details:
            - Moves the monster to the specified coordinates. Adjusts the position if it goes beyond the screen boundaries.
        Parameters:
            - monster: Pointer to the monster object to be moved.
            - x: X-coordinate of the new position.
            - y: Y-coordinate of the new position.

    Function Name: move_platform_absolute
        Purpose:
            - Moves a platform to an absolute position.
        Details:
            - Moves the platform to the specified coordinates. Adjusts the position if it goes beyond the screen boundaries.
        Parameters:
            - platforms: Pointer to the platform object to be moved.
            - x: X-coordinate of the new position.
            - y: Y-coordinate of the new position.

    Function Name: has_doodle_moved
        Purpose:
            - Checks if the doodle has moved.
        Details:
            - Compares the current doodle position and facing direction with the previous state to determine if there's movement.
        Parameters:
            - doodle: Pointer to the doodle object.
        Returns:
            - bool: True if the doodle has moved, false otherwise.

    Function Name: has_monster_moved
        Purpose:
            - Checks if the monster has moved.
        Details:
            - Compares the current monster position with the previous state to determine if there's movement.
        Parameters:
            - monster: Pointer to the monster object.
        Returns:
            - bool: True if the monster has moved, false otherwise.

    Function Name: has_platform_moved
        Purpose:
            - Checks if a platform has moved.
        Details:
            - Compares the current platform position with the previous state to determine if there's movement.
        Parameters:
            - platform: Pointer to the platform object.
        Returns:
            - bool: True if the platform has moved, false otherwise.
 */

#ifndef MODEL_H
#define MODEL_H

#include "TYPES.H"
#include "system.h"
#include "BITMAP.H"
#include <osbind.h>

#define MAX_PLATFORMS 9
#define DOODLE_HORIZONTAL_MOVEMENT 32
typedef struct 
{
    int x, y; 
    int prev_x, prev_y;
    int velocity;
    int max_y;
    bool isFalling;
    bool dead;
    UINT16 facing;
    UINT16 prev_facing;
} Doodle;

typedef struct 
{
    int prev_x, prev_y;
    int x, y; 
    bool off_screen;
} Monster;

typedef struct 
{
    int prev_x, prev_y;
    int x, y; 
    bool off_screen;
    bool is_broken;
} Platform;

typedef struct
{
  int total;
  int digits;
  int prev_total;
} Score;


typedef struct {
    Doodle doodle;
    Monster monster;
    Platform platforms[MAX_PLATFORMS];  
    Score score;
} Model;

void initialize_model(Model *model, int seed);

void move_doodle(Doodle *doodle, int displacement_x, int displacement_y, UINT16 newFacing);
void move_monster_relative(Monster *monster, int displacement_x, int displacement_y);
void move_monster_absolute(Monster *monster, int x, int y);
void move_platform_relative(Platform *platform, int displacement_x, int displacement_y, UINT8 selected_platform);
void move_platform_absolute(Platform *platforms, UINT16 x, UINT16 y);

bool has_doodle_moved(Doodle *doodle);
bool has_monster_moved(Monster *monster);
bool has_platform_moved(Platform *platform);

#endif

