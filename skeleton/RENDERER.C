#include "MODEL.H"
#include "RASTER.H"
#include "BITMAP.H"
#include "RENDERER.H"

#include <stdio.h>

void render(const Model *model, UINT32 *base)
{
    render_platform(model->platforms, base);

    if(has_monster_moved(&(model->monster)) == 1)
    {     
        plot_bitmap_32(base, model->monster.prev_x, model->monster.prev_y, clear_bitmap, MONSTER_HEIGHT);
        render_monster(&(model->monster), base);
    }

    
    /*Comparing to previous state so that stationary objects are not redrawn*/
    if(has_doodle_moved(&(model->doodle)) == 1)
    {
        plot_bitmap_32(base, model->doodle.prev_x, model->doodle.prev_y, clear_bitmap, DOODLE_HEIGHT);
        render_doodle(&(model->doodle), base); 
    }
}


void render_doodle(const Doodle *doodle, UINT32 *base)
{

    if(doodle->facing == 1)
        plot_bitmap_32(base, doodle->x, doodle->y, doodle_bitmap_right, DOODLE_HEIGHT);
    else
        plot_bitmap_32(base, doodle->x, doodle->y, doodle_bitmap_left, DOODLE_HEIGHT);

}


void render_monster(const Monster *monster, UINT32 *base)
{

    plot_bitmap_32(base, monster->x, monster->y, monster_bitmap, MONSTER_HEIGHT);

}


/*Note this may need to change as we plan on using decreasing amount of platforms not always the max platforms*/
void render_platform(Platform *platforms, UINT32 *base)
{
    int i;

    for(i = 0; i < MAX_PLATFORMS; i++){
        if(has_platform_moved(platforms) == 1)
        {
            plot_bitmap_32(base, platforms->prev_x, platforms->prev_y, clear_bitmap, PLATFORM_HEIGHT);
            plot_bitmap_32(base, platforms->x, platforms->y, platform_bitmap, PLATFORM_HEIGHT);
        }
            platforms ++;
    }
}