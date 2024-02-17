#include "model.h"

void initialize_model(Model *model) {
    // Initialize Doodle character in the middle of the screen
    model->doodle.x = SCREEN_WIDTH / 2;
    model->doodle.y = SCREEN_HEIGHT / 2;
    model->doodle.delta_x = 0;
    model->doodle.delta_y = 0;
    model->doodle.facing = 1; // Assuming initially facing right
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
