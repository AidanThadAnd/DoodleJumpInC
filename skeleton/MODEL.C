#include "model.h"
#include "system.h"

void initialize_model(Model *model) {
    /* Initialize Doodle character */
    model->doodle.x = SCREEN_WIDTH / 2;
    model->doodle.y = SCREEN_HEIGHT / 2;
    model->doodle.delta_x = 0;
    model->doodle.delta_y = 0;
    model->doodle.facing = 1; /* Assuming initially facing right */

    /* Initialize platforms */
    for (int i = 0; i < 7; ++i) {
        model->platforms[i].x = i * 100;
        model->platforms[i].y = SCREEN_HEIGHT - (i * 80);
    }

    /* Initialize monster */
    model->monster.x = SCREEN_WIDTH / 2;
    model->monster.y = SCREEN_HEIGHT - 100;
}
void move_doodle(Doodle *doodle, int displacement_x, int displacement_y)
{
    doodle->y += displacement_y;
    doodle->x += displacement_x;
}

void move_platform(Platform *platform)
{
    platform->x += platform->delta_x;
}
