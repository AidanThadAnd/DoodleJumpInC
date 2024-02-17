# 1 "events.c" 1
# 1 "./events.h" 1



void press_key(Doodle *character, char key);
int check_collision_doodle_platform(Doodle *doodle, Platform *platform);
# 1 "events.c" 2


void press_key(Doodle *character, char key)
{
    switch(key)
    {
        case 'a':
            move_doodle(character, -1, 0)
            character->facing = 0;
            break;
        case 'd':
            move_doodle(character, 1, 0)
            character->facing = 1;
            break;
        default:
            break:
    }
}





int check_collision_doodle_platform(Doodle *d, Platform *p)
{
    if (d->y + doodle_height > p->y &&
        d->y < p->y + platform_height &&
        d->x + doodle_width > p->x &&
        d->x < p->x + platform_width)
    {
        return 1;
    }
        return 0;
}
