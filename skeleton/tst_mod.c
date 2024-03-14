#include <stdio.h>
#include "model.h"
#include "events.h"
#include "system.h"

void print_state(Model *gameModel) {
  
    int i;

    printf("Doodle - X: %d, Y: %d, Facing: %d\n", gameModel->doodle.x, 
        	gameModel->doodle.y, gameModel->doodle.facing);
    for (i = 0; i < 7; ++i) {
        printf("Platform %d - X: %d, Y: %d\n", i + 1, gameModel->platforms[i].x, gameModel->platforms[i].y);
    }

    printf("Monster - X: %d, Y: %d\n", gameModel->monster.x, gameModel->monster.y);
}

int main() {
    Model gameModel;
    initialize_model(&gameModel);

    printf("Initial state:\n");
    print_state(&gameModel);

    printf("\nPerforming actions:\n");

    press_key(&gameModel.doodle, 'd');  
    printf("After moving right:\n");
    print_state(&gameModel);

    press_key(&gameModel.doodle, 'a');  
    printf("After moving left:\n");
    print_state(&gameModel);
    
    if (check_collision_monster(&gameModel.doodle, &gameModel.monster)) {
        printf("Collision with Monster detected!\n");
    } else {
        printf("No collision with Monster.\n");
    }

    return 0;
}
