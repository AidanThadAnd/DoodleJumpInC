#ifndef RENDERER_H
#define RENDERER_H

#include "MODEL.H"
#include "RASTER.H"
#include "BITMAP.H"

void render(const Model *model, UINT32 *base);
void render_doodle(const Doodle *doodle, UINT32 *base);
void render_monster(const Monster *monster, UINT32 *base);
void render_platform(const Platform *platform, UINT32 *base);

#endif