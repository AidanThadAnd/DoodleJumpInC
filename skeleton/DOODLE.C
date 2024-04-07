#include "model.h"
#include "events.h"
#include "renderer.h"
#include <stdio.h>
#include <osbind.h>

UINT8 double_buffer[448][80] = {0};

UINT32 get_time();
void input(Model *model, char *pressedKey);
void syncModel(Model *modelSrc, Model *modelDst);
void process_synchronous_events(Model *model, bool *endGame, int seed);

int main() {
    UINT8 *page1 = Physbase();
    UINT8 *page2 = &double_buffer[0][0];
    UINT8 i;
    UINT8 confirmedInput;
    int seed;

    bool useDoubleBuffer = true;
    bool endGame = false;

    UINT32 timeThen, timeNow, timeElapsed;

    Model modelOne, modelTwo, modelThree;
    Model *modelPtr = &modelOne;
    Model *modelSnapshotOne = &modelTwo;
    Model *modelSnapshotTwo = &modelThree;

    char pressedKey = 0;


    seed = Random();

    initialize_model(modelPtr, seed);
    initialize_model(modelSnapshotOne, seed);
    initialize_model(modelSnapshotTwo, seed);

    page2 = (UINT8*)((size_t)page2 | 0xff ) + 1; /* finding page aligned address for second page*/

    /*slight movement to all objects are required as the rendering optimzation requires some movement from initlization of objects 
    to prevent redrawing of still objects  */
    for(i=0; i<MAX_PLATFORMS;i++)
    {
        move_platform_relative(modelPtr->platforms, 1, -60, i);
    }
    move_monster_relative(&(modelPtr->monster), 8, 8);


    /* prepering pages and models for main game loop*/
    clear_screen(page1);
    clear_screen(page2);
    syncModel(modelPtr, modelSnapshotOne);
    syncModel(modelPtr, modelSnapshotTwo);

    render(modelPtr, (UINT32*)page1);  /* Render the initial state of the model */
   
    render(modelPtr, (UINT32*)page2);

    
    

    timeThen = get_time();
    while (pressedKey != 'q' && !endGame) { /* Main game loop */

        input(modelPtr, &pressedKey);

        timeNow = get_time();
        timeElapsed = timeNow - timeThen;

        if(timeElapsed > 0)
        {
            Vsync();
            if(useDoubleBuffer)
                {
                    process_synchronous_events(modelPtr, &endGame, seed);
                    
                    syncModel(modelPtr, modelSnapshotOne);
                    double_buffer_render(modelSnapshotOne, modelSnapshotTwo, (UINT32*)page1);
                    
                    Setscreen(-1, page1, -1);
                    
                    useDoubleBuffer = false;
                }
                else
                {
                    process_synchronous_events(modelPtr, &endGame, seed);
                    syncModel(modelPtr, modelSnapshotTwo);
                    double_buffer_render(modelSnapshotTwo, modelSnapshotOne,(UINT32*)page2);
                    
                    Setscreen(-1, page2, -1);
                    
                    useDoubleBuffer = true;
                }
                seed = seed*3;
                Vsync();
        }
        timeThen = get_time();
    }
    Setscreen(-1, page1, -1);
    Vsync();
    return 0;
}

void syncModel(Model *modelSrc, Model *modelDst)
{
    UINT8 i;
    Platform *srcPlatform, *dstPlatform;

    modelDst->doodle.x = modelSrc->doodle.x;
    modelDst->doodle.y = modelSrc->doodle.y;

    modelDst->doodle.facing = modelSrc->doodle.facing;
    modelDst->doodle.prev_facing = modelSrc->doodle.prev_facing;

    modelDst->doodle.velocity = modelSrc->doodle.velocity;
    modelDst->doodle.isFalling = modelSrc->doodle.isFalling;
    modelDst->doodle.max_y = modelSrc->doodle.max_y;
    modelDst->doodle.dead = modelSrc->doodle.dead;

    modelDst->score.total = modelSrc->score.total;
    modelDst->score.prev_total = modelSrc->score.prev_total;
    modelDst->score.digits = modelSrc->score.digits;
    

    modelDst->monster.x = modelSrc->monster.x;
    modelDst->monster.y = modelSrc->monster.y;


    srcPlatform = (modelSrc->platforms);
    dstPlatform = (modelDst->platforms);

    for(i=0; i < MAX_PLATFORMS;i++)
    {
        dstPlatform->x = srcPlatform->x;
        dstPlatform->y = srcPlatform->y;

        srcPlatform++;
        dstPlatform++;     
    }
}


void input(Model *model, char *pressedKey)
{
    if (Cconis()) /* Check if keyboard input is available */
    { 
        char key = (char)Cnecin(); /* Read keyboard input */
        if (key == 'a' || key == 'd' || key == 'q')
            *pressedKey = key;
    } 
        else 
            *pressedKey = 0; /* Reset pressedKey if no key is pressed */


    doodle_input(&(model->doodle), *pressedKey);
    
}

void process_synchronous_events(Model *model, bool *endGame, int seed)
{
    doodle_vertical_movement(model);
    shift_screen_to_doodle(model);
    replace_off_screen(model, seed);
    check_doodle_death(model, endGame);
}

/*

TODO: Investigate the weird slowdown issue with using Cconis in a wrapper function

bool isKeyPressed()
{
    if(Cconis())
        return true;
    return false;
}
*/

UINT32 get_time() {
    UINT32 time;
    long old_ssp = Super(0); 
    time = *((UINT32 *)0x462);
    Super(old_ssp); 
    return time;
}
