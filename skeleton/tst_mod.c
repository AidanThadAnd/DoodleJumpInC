#include <stdio.h>
#include "model.h"
#include "events.h"
#include "system.h"

int main() {
    Model model;

    initialize_model(&model);

    int initialDoodleX = model.doodle.x;
    int initialPlatformX = model.platforms[0].x;

    press_key(&model.doodle, 'a');

    if (initialDoodleX != model.doodle.x) {
        printf("Doodle has moved.\n");
    } else {
        printf("Doodle has not moved.\n");
    }

    move_platform(&model.platforms[0]);

    if (initialPlatformX != model.platforms[0].x) {
        printf("Platform has moved.\n");
    } else {
        printf("Platform has not moved.\n");
    }

    if (check_collision_doodle_platform(&model.doodle, &model.platforms[1])) {
        printf("Collision: Doodle collided with a platform!\n");
    }

    if (check_collision_monster(&model.doodle, &model.monster[1])) {
        printf("Collision: Doodle collided with a monster!\n");
    }

    return 0;
}
