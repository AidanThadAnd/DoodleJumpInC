#include "RENDERER.H"
/***********************************************************************
* Name: render
*
* Purpose: Renders the game objects onto the screen buffer.
*
* Details: Renders the platforms, doodle, and monster onto the screen
*          buffer based on the provided game model. Clears previous
*          positions of moving objects before rendering new positions.
*
* Parameters:
*     - model: Pointer to the game model containing object positions.
*     - base: Pointer to the base address of the screen buffer.
***********************************************************************/
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

/***********************************************************************
* Name: double_buffer_render
*
* Purpose: Renders game objects optimized for double buffering.
*
* Details: Renders the platforms, doodle, and monster onto the screen
*          buffer using double buffering to avoid flickering. Clears
*          previous positions of moving objects before rendering new
*          positions.
*
* Parameters:
*     - model: Pointer to the new game model containing updated
*                 object positions.
*     - base: Pointer to the base address of the screen buffer.
***********************************************************************/
void double_buffer_render(Model *model, UINT32 *base)
{
    UINT8 i;
    Platform *modelPlatforms= model->platforms;


    for(i = 0; i < MAX_PLATFORMS; i++){
        if(modelPlatforms->prev_x != modelPlatforms->x || modelPlatforms->prev_y != modelPlatforms->y)
        {
            clear_bitmap_32(base, modelPlatforms->prev_x, modelPlatforms->prev_y, clear_bitmap, DOODLE_HEIGHT);
            modelPlatforms->prev_x = modelPlatforms->x;
            modelPlatforms->prev_y = modelPlatforms->y;
            render_platform(modelPlatforms, base);
        }
            modelPlatforms++;
    }

    if(model->monster.prev_x != model->monster.x || model->monster.prev_y != model->monster.y)
    {
        clear_bitmap_32(base, model->monster.prev_x, model->monster.prev_y, clear_bitmap, DOODLE_HEIGHT);
        model->monster.prev_x = model->monster.x;
        model->monster.prev_y = model->monster.y;

        render_monster(&(model->monster), base);
    }

    /*Comparing to previous state so that stationary objects are not redrawn*/
    if(model->doodle.prev_x != model->doodle.x || model->doodle.prev_y != model->doodle.y)
    {
        clear_bitmap_32(base, model->doodle.prev_x, model->doodle.prev_y, clear_bitmap, DOODLE_HEIGHT);
        model->doodle.prev_x = model->doodle.x;
        model->doodle.prev_y = model->doodle.y;

        render_doodle(&(model->doodle), base);
    }

    if(model->score.prev_total != model->score.total)
        render_score(&(model->score), base);
}
/***********************************************************************
* Name: render_score
*
* Purpose: Renders the game score onto the screen buffer.
*
* Details: Renders the score onto the screen buffer using bitmap
*          plotting. Clears previous digits before rendering new ones.
*
* Parameters:
*     - score: Pointer to the game score structure.
*     - base: Pointer to the base address of the screen buffer.
***********************************************************************/

void render_score(Score *score, UINT32 *base)
{
    UINT8 i;
    int temp;
    int currentDigits = countDigits(score->total);
    
    temp = score->total;
    for(i=0; i < currentDigits; currentDigits-=1)
    {
        clear_bitmap_8((UINT16*)base, currentDigits<<4, 8, char_delete, FONT_HEIGHT);
        plot_bitmap_8((UINT16*)base, currentDigits<<4, 8, GLYPH_START(temp%10+'0'), FONT_HEIGHT);
        temp = temp/10;
    }
}

/***********************************************************************
* Name: render_doodle
*
* Purpose: Renders the doodle onto the screen buffer.
*
* Details: Renders the doodle onto the screen buffer based on its
*          position and facing direction using bitmap plotting.
*
* Parameters:
*     - doodle: Pointer to the doodle object.
*     - base: Pointer to the base address of the screen buffer.
***********************************************************************/

void render_doodle(Doodle *doodle, UINT32 *base)
{
    if(doodle->facing == 1)
        plot_bitmap_32(base, doodle->x, doodle->y, doodle_bitmap_right, DOODLE_HEIGHT);
    else
        plot_bitmap_32(base, doodle->x, doodle->y, doodle_bitmap_left, DOODLE_HEIGHT);
}

/***********************************************************************
* Name: render_monster
*
* Purpose: Renders the monster onto the screen buffer.
*
* Details: Renders the monster onto the screen buffer based on its
*          position using bitmap plotting.
*
* Parameters:
*     - monster: Pointer to the monster object.
*     - base: Pointer to the base address of the screen buffer.
***********************************************************************/
void render_monster(Monster *monster, UINT32 *base)
{
    if(monster->y > 0)
        plot_bitmap_32(base, monster->x, monster->y, monster_bitmap, MONSTER_HEIGHT);
}

/***********************************************************************
* Name: render_platform
*
* Purpose: Renders a platform onto the screen buffer.
*
* Details: Renders a platform onto the screen buffer based on its
*          position using bitmap plotting.
*
* Parameters:
*     - platforms: Pointer to the platform object.
*     - base: Pointer to the base address of the screen buffer.
***********************************************************************/
void render_platform(Platform *platforms, UINT32 *base)
{
    if(!(platforms->is_broken))
        plot_bitmap_32(base, platforms->x, platforms->y, platform_bitmap, PLATFORM_HEIGHT); 
    else
        plot_bitmap_32(base, platforms->x, platforms->y, broken_platform_bitmap, PLATFORM_HEIGHT); 
            
}
