/*
  Author: Aidan & Jacky
  Date: Feb 5, 2024
 
  Purpose:
    - Defines functions related to rendering game entities.
 
  Functions:
    Function Name: render
      Purpose:
        - Render a model.
      Input:
        - model: Pointer to the Model structure to be rendered.
        - base: Base address for rendering.
 
    Function Name: render_doodle
      Purpose:
        - Render a doodle.
      Input:
        - doodle: Pointer to the Doodle structure to be rendered.
        - base: Base address for rendering.
 
    Function Name: render_monster
      Purpose:
        - Render a monster.
      Input:
        - monster: Pointer to the Monster structure to be rendered.
        - base: Base address for rendering.
 
    Function Name: render_platform
      Purpose:
        - Render a platform.
      Input:
        - platform: Pointer to the Platform structure to be rendered.
        - base: Base address for rendering.
 */

#ifndef RENDERER_H
#define RENDERER_H

#include "MODEL.H"
#include "RASTER.H"
#include "BITMAP.H"
#include "font.h"

void render(const Model *model, UINT32 *base);
void render_doodle(const Doodle *doodle, UINT32 *base);
void render_monster(const Monster *monster, UINT32 *base);
void render_platform(Platform *platform, UINT32 *base);
void render_score(Score *score, UINT32 *base);
void double_buffer_render(Model *modelOld, Model *modelNew, UINT32 *baseNew);

#endif
