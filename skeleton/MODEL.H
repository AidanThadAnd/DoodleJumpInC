/*
Author: Aidan & Jacky
Date: Feb 5, 2024

Purpose:
    - Defines structures for game objects in the model, including Doodle, Monster, Platform, and the overall Model.
    - Provides functions to initialize and manipulate the game model.
 
  Functions:
    Function Name: initialize_model
      Purpose:
        - Initializes the game model with default values.
      Output:
        - Returns a pointer to the initialized Model structure.
 
    Function Name: move_doodle
      Purpose:
        - Moves the doodle entity by the specified displacements.
      Input:
        - doodle: Pointer to the Doodle structure to be moved.
        - displacement_x: The displacement along the x-axis.
        - displacement_y: The displacement along the y-axis.
 
    Function Name: move_platform_relative
      Purpose:
        - Moves the specified platform entity relative to its current position.
      Input:
        - platform: Pointer to the Platform structure to be moved.
        - displacement_x: The displacement along the x-axis.
        - displacement_y: The displacement along the y-axis.
        - selected_platform: Index of the platform to be moved.
 
    Function Name: move_monster
      Purpose:
        - Moves the monster entity by the specified displacements.
      Input:
        - monster: Pointer to the Monster structure to be moved.
        - displacement_x: The displacement along the x-axis.
        - displacement_y: The displacement along the y-axis.
 
    Function Name: move_platform_absolute
      Purpose:
        - Moves the specified platform entity to the specified absolute position.
      Input:
        - platforms: Array of Platform structures.
        - x: The new x-coordinate of the platform.
        - y: The new y-coordinate of the platform.
        - selected_platform: Index of the platform to be moved.
 
    Function Name: has_doodle_moved
      Purpose:
        - Checks if the doodle has moved from its previous position.
      Input:
        - doodle: Pointer to the Doodle structure to be checked.
      Output:
        - Returns 1 if the doodle has moved, 0 otherwise.
 
    Function Name: has_monster_moved
      Purpose:
        - Checks if the monster has moved from its previous position.
      Input:
        - monster: Pointer to the Monster structure to be checked.
      Output:
        - Returns 1 if the monster has moved, 0 otherwise.
 
    Function Name: has_platform_moved
      Purpose:
        - Checks if the specified platform has moved from its previous position.
      Input:
        - platform: Pointer to the Platform structure to be checked.
      Output:
        - Returns 1 if the platform has moved, 0 otherwise.
 */

#ifndef MODEL_H
#define MODEL_H

#include "TYPES.H"
#include "system.h"

#define MAX_PLATFORMS 15
#define DOODLE_HORIZONTAL_MOVEMENT 32
typedef struct 
{
    int x, y; 
    int prev_x, prev_y;
    int velocity;
    bool isFalling;
    UINT16 facing;
    UINT16 prev_facing;
} Doodle;

typedef struct 
{
    int prev_x, prev_y;
    int x, y; 
} Monster;

typedef struct 
{
    int prev_x, prev_y;
    int x, y; 
} Platform;

typedef struct {
    Doodle doodle;
    Monster monster;
    Platform platforms[MAX_PLATFORMS];  
} Model;

void initialize_model(Model *model);

void move_doodle(Doodle *doodle, int displacement_x, int displacement_y, UINT16 newFacing);
void move_monster(Monster *monster, int displacement_x, int displacement_y);
void move_platform_relative(Platform *platform, int displacement_x, int displacement_y, UINT8 selected_platform);
void move_platform_absolute(Platform *platforms, UINT16 x, UINT16 y, UINT8 selected_platform);

bool has_doodle_moved(Doodle *doodle);
bool has_monster_moved(Monster *monster);
bool has_platform_moved(Platform *platform);

#endif

