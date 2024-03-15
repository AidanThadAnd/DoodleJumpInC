/*
Author: Aidan & Jacky
Date: Feb 5, 2024

Purpose:
    - Defines structures for game objects in the model, including Doodle, Monster, Platform, and the overall Model.
    - Provides functions to initialize and manipulate the game model.

Structures:
    Structure Name: Doodle
        Fields:
            - x: X-coordinate of the Doodle.
            - y: Y-coordinate of the Doodle.
            - delta_x: Change in X-coordinate for movement.
            - delta_y: Change in Y-coordinate for movement.
            - facing: Direction the Doodle is facing.

    Structure Name: Monster
        Fields:
            - x: X-coordinate of the Monster.
            - y: Y-coordinate of the Monster.

    Structure Name: Platform
        Fields:
            - x: X-coordinate of the Platform.
            - y: Y-coordinate of the Platform.
            - delta_x: Change in X-coordinate for movement.

    Structure Name: Model
        Fields:
            - doodle: Instance of the Doodle structure.
            - monster: Instance of the Monster structure.
            - platforms: Array of Platform structures representing the game platforms.

Functions:
        Function Name: initialize_model
        Purpose:
            - Initializes the Model structure with default values.
        Input:
            - model: Pointer to the Model structure to be initialized.
    
        Function Name: move_doodle
        Purpose:
            - Moves the Doodle's position based on the specified displacements.
        Input:
            - doodle: Pointer to the Doodle structure to be moved.
            - displacement_x: Change in X-coordinate for movement.
            - displacement_y: Change in Y-coordinate for movement.

        Function Name: move_platform
        Purpose:
            - Moves the Platform's position based on its delta_x.
        Input:
            - platform: Pointer to the Platform structure to be moved.
*/

#ifndef MODEL_H
#define MODEL_H

#include "TYPES.H"

#define MAX_PLATFORMS 15

typedef struct 
{
    UINT16 prev_x, prev_y;  
    UINT16 x, y; 
    int delta_x, delta_y; 
    UINT16 facing;
} Doodle;

typedef struct 
{
    UINT16 prev_x, prev_y;
    int delta_x, delta_y;
    UINT16 x, y; 
} Monster;

typedef struct 
{
    UINT16 prev_x, prev_y;
    UINT16 x, y; 
    int delta_x, delta_y;
} Platform;

typedef struct {
    Doodle doodle;
    Monster monster;
    Platform platforms[MAX_PLATFORMS];  
} Model;

Model* initialize_model();

/* Changed as I don't think we'll be using displacment and instead we'll be relying on delta_x/y to move characters around, im assuming you just had this for testing
void move_doodle(Doodle *doodle);
*/
void move_doodle(Doodle *doodle, UINT16 displacement_x, UINT16 displacement_y);

void move_platform(Platform *platform);

UINT8 has_doodle_moved(Doodle *doodle);
UINT8 has_monster_moved(Monster *monster);
UINT8 has_platform_moved(Platform *platform);

#endif

