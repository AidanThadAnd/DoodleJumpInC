#include "RENDERER.H"

void render(Model *model, UINT32 *base)
{
    int multipleDoodleDeletions;
    render_platform(model->platforms, base);

    if(has_monster_moved(&(model->monster)))
    {     
        clear_bitmap_32(base, model->monster.prev_x, model->monster.prev_y, clear_bitmap, MONSTER_HEIGHT);
        render_monster(&(model->monster), base);
    }

    /*Comparing to previous state so that stationary objects are not redrawn*/
    if(has_doodle_moved(&(model->doodle)))
    {   
        clear_bitmap_32(base, model->doodle.prev_x, model->doodle.prev_y, clear_bitmap, DOODLE_HEIGHT);

        render_doodle(&(model->doodle), base);
    }
}

void double_buffer_render(Model *modelOld, Model *modelNew, UINT32 *base)
{
    UINT8 i;
    Platform *oldModelPlatforms = &(modelOld->platforms);
    Platform *newModelPlatforms= &(modelNew->platforms);


    for(i = 0; i < MAX_PLATFORMS; i++){
        if(newModelPlatforms->x != oldModelPlatforms->x || newModelPlatforms->y != oldModelPlatforms->y)
        {
            clear_bitmap_32(base, oldModelPlatforms->x, oldModelPlatforms->y, clear_bitmap, PLATFORM_HEIGHT);
            plot_bitmap_32(base, newModelPlatforms->x, newModelPlatforms->y, platform_bitmap, PLATFORM_HEIGHT);
        }
            newModelPlatforms++;
            oldModelPlatforms++;
    }

    if(modelOld->monster.x != modelNew->monster.x || modelOld->monster.y != modelNew->monster.y)
    {
        clear_bitmap_32(base, modelOld->monster.x, modelOld->monster.y, clear_bitmap, MONSTER_HEIGHT);
        render_monster(&(modelNew->monster), base);
    }

    /*Comparing to previous state so that stationary objects are not redrawn*/
    if(modelOld->doodle.x != modelNew->doodle.x || modelOld->doodle.y != modelNew->doodle.y)
    {
        clear_bitmap_32(base, modelOld->doodle.x, modelOld->doodle.y, clear_bitmap, DOODLE_HEIGHT);
        render_doodle(&(modelNew->doodle), base);
    }
}


void render_doodle(Doodle *doodle, UINT32 *base)
{
    if(doodle->facing == 1)
        plot_bitmap_32(base, doodle->x, doodle->y, doodle_bitmap_right, DOODLE_HEIGHT);
    else
        plot_bitmap_32(base, doodle->x, doodle->y, doodle_bitmap_left, DOODLE_HEIGHT);
}


void render_monster(Monster *monster, UINT32 *base)
{

    plot_bitmap_32(base, monster->x, monster->y, monster_bitmap, MONSTER_HEIGHT);


}


/*Note this may need to change as we plan on using decreasing amount of platforms not always the max platforms*/
void render_platform(Platform *platforms, UINT32 *base)
{
    int i;

    for(i = 0; i <= MAX_PLATFORMS; i++){
        if(has_platform_moved(platforms))
        {
            clear_bitmap_32(base, platforms->prev_x, platforms->prev_y, clear_bitmap, PLATFORM_HEIGHT);
            plot_bitmap_32(base, platforms->x, platforms->y, platform_bitmap, PLATFORM_HEIGHT);

        }
            platforms ++;
    }
}