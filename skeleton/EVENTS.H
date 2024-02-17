#ifndef EVENTS_H
#define EVENTS_H

#include "model.h"

void press_key(Doodle *character, char key);
int check_collision_doodle_platform(Doodle *doodle, Platform *platform);

#endif

