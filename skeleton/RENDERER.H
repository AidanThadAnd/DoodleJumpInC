/*
  Author: Aidan & Jacky
  Date: Feb 5, 2024
 
Purpose:
    - Defines functions for rendering game objects onto the screen buffer.

Functions:
    Function Name: render
        Purpose:
            - Renders the game objects onto the screen buffer.
        Details:
            - Renders the platforms, doodle, and monster onto the screen buffer based on the provided game model. Clears previous positions of moving objects before rendering new positions.
        Parameters:
            - model: Pointer to the game model containing object positions.
            - base: Pointer to the base address of the screen buffer.

    Function Name: double_buffer_render
        Purpose:
            - Renders game objects optimized for double buffering.
        Details:
            - Renders the platforms, doodle, and monster onto the screen buffer using double buffering to avoid flickering. Clears previous positions of moving objects before rendering new positions.
        Parameters:
            - model: Pointer to the new game model containing updated object positions.
            - base: Pointer to the base address of the screen buffer.

    Function Name: render_score
        Purpose:
            - Renders the game score onto the screen buffer.
        Details:
            - Renders the score onto the screen buffer using bitmap plotting. Clears previous digits before rendering new ones.
        Parameters:
            - score: Pointer to the game score structure.
            - base: Pointer to the base address of the screen buffer.

    Function Name: render_doodle
        Purpose:
            - Renders the doodle onto the screen buffer.
        Details:
            - Renders the doodle onto the screen buffer based on its position and facing direction using bitmap plotting.
        Parameters:
            - doodle: Pointer to the doodle object.
            - base: Pointer to the base address of the screen buffer.

    Function Name: render_monster
        Purpose:
            - Renders the monster onto the screen buffer.
        Details:
            - Renders the monster onto the screen buffer based on its position using bitmap plotting.
        Parameters:
            - monster: Pointer to the monster object.
            - base: Pointer to the base address of the screen buffer.

    Function Name: render_platform
        Purpose:
            - Renders a platform onto the screen buffer.
        Details:
            - Renders a platform onto the screen buffer based on its position using bitmap plotting.
        Parameters:
            - platforms: Pointer to the platform object.
            - base: Pointer to the base address of the screen buffer.
 */

#ifndef RENDERER_H
#define RENDERER_H

#include "MODEL.H"
#include "RASTER.H"
#include "BITMAP.H"
#include "font.h"
#include "MY_MATH.h"

void render(const Model *model, UINT32 *base);
void render_doodle(const Doodle *doodle, UINT32 *base);
void render_monster(const Monster *monster, UINT32 *base);
void render_platform(Platform *platform, UINT32 *base);
void render_score(Score *score, UINT32 *base);
void double_buffer_render(Model *modelNew, UINT32 *baseNew);


#endif
