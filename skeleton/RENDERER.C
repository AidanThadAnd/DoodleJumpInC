#include "MODEL.H"
#include "RASTER.H"
#include "BITMAP.H"
#include "RENDERER.H"

#include <stdio.h>

void render(const Model *model, UINT32 *base)
{

    /*Comparing to previous state so that stationary objects are not redrawn*/
    /*if(model->doodle.prevX != model->doodle.x && model->doodle.prevY != model->doodle.y)*/
        render_doodle(&(model->doodle), base); 


    /*if(model->monster.prevX != model->monster.x && model->monster.prevY != model->monster.y) */    
        render_monster(&(model->monster), base);


    render_platform(model->platforms, base);
    
}


void render_doodle(const Doodle *doodle, UINT32 *base)
{

    plot_bitmap_32(base, doodle->x, doodle->y, doodle_bitmap, DOODLE_HEIGHT);

}


void render_monster(const Monster *monster, UINT32 *base)
{

    plot_bitmap_32(base, monster->x, monster->y, monster_bitmap, MONSTER_HEIGHT);

}


/*Note this may need to change as we plan on using decreasing amount of platforms not always the max platforms*/
void render_platform(Platform *platform, UINT32 *base)
{
    int total_platform = sizeof(*platform);
    int i;

    for(i = 0; i < MAX_PLATFORMS; i++){
        /*
        if(platform->prevX != platform->x && platform->prevY != platform->y)
        */
            plot_bitmap_32(base, platform->x, platform->y, platform_bitmap, PLATFORM_HEIGHT);
        platform++;
    }
}