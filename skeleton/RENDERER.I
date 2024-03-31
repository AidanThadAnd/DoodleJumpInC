# 1 "renderer.c" 1
# 1 "./RENDERER.H" 1
# 1 "./MODEL.H" 1
# 1 "./TYPES.H" 1



typedef unsigned char UINT8;
typedef unsigned int  UINT16;
typedef unsigned long UINT32;

typedef unsigned char bool;
# 78 "./MODEL.H" 2
# 1 "./system.h" 1
# 79 "./MODEL.H" 2
# 85 "./MODEL.H"
typedef struct
{
    UINT16 x, y;
    UINT16 prev_x, prev_y;
    int velocity;
    UINT16 facing;
    UINT16 prev_facing;
} Doodle;

typedef struct
{
    UINT16 prev_x, prev_y;
    UINT16 x, y;
} Monster;

typedef struct
{
    UINT16 prev_x, prev_y;
    UINT16 x, y;
} Platform;

typedef struct {
    Doodle doodle;
    Monster monster;
    Platform platforms[15 ];
} Model;

void initialize_model(Model *model);

void move_doodle(Doodle *doodle, UINT16 displacement_x, UINT16 displacement_y, UINT16 newFacing);
void move_monster(Monster *monster, UINT16 displacement_x, UINT16 displacement_y);
void move_platform_relative(Platform *platform, UINT16 displacement_x, UINT16 displacement_y, UINT8 selected_platform);
void move_platform_absolute(Platform *platforms, UINT16 x, UINT16 y, UINT8 selected_platform);

UINT8 has_doodle_moved(Doodle *doodle);
UINT8 has_monster_moved(Monster *monster);
UINT8 has_platform_moved(Platform *platform);
# 41 "./RENDERER.H" 2
# 1 "./RASTER.H" 1
# 1 "./types.h" 1
# 107 "./RASTER.H" 2
# 1 "./system.h" 1
# 108 "./RASTER.H" 2


void plot_bitmap_8(UINT16 *base, int x, int y, const UINT8 *bitmap, unsigned int height);
void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, unsigned int height);
void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, int height);
void clear_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, int height);
void plot_horizontal_line(UINT8 *base, int y);
void clear_screen(UINT8 *base);
void clear_horizontal_line_8(UINT8* base, int x, int y, int length);
# 42 "./RENDERER.H" 2
# 1 "./BITMAP.H" 1
# 1 "./types.h" 1
# 4 "./BITMAP.H" 2
# 18 "./BITMAP.H"
extern const UINT32 doodle_bitmap_right [];
extern UINT32 doodle_bitmap_left[];
extern const UINT32 monster_bitmap [];
extern const UINT32 platform_bitmap [];
extern const UINT32 broken_platform_bitmap [];
extern const UINT32 clear_bitmap[];
# 43 "./RENDERER.H" 2


void render(const Model *model, UINT32 *base);
void render_doodle(const Doodle *doodle, UINT32 *base);
void render_monster(const Monster *monster, UINT32 *base);
void render_platform(Platform *platform, UINT32 *base);
void double_buffer_render(Model *modelOld, Model *modelNew, UINT32 *baseCurr);
# 1 "renderer.c" 2


void render(Model *model, UINT32 *base)
{
    int multipleDoodleDeletions;
    render_platform(model->platforms, base);

    if(has_monster_moved(&(model->monster)))
    {
        clear_bitmap_32(base, model->monster.prev_x, model->monster.prev_y, clear_bitmap, 35 );
        render_monster(&(model->monster), base);
    }


    if(has_doodle_moved(&(model->doodle)))
    {
        clear_bitmap_32(base, model->doodle.prev_x, model->doodle.prev_y, clear_bitmap, 55 );

        render_doodle(&(model->doodle), base);
    }
}

void double_buffer_render(Model *modelOld, Model *modelNew, UINT32 *baseCurr)
{
    render_platform(modelNew->platforms, baseCurr);

    if(modelOld->monster.x != modelNew->monster.x || modelOld->monster.y != modelNew->monster.y)
    {
        clear_bitmap_32(baseCurr, modelOld->monster.x, modelOld->monster.y, clear_bitmap, 35 );
        render_monster(&(modelNew->monster), baseCurr);
    }


    if(modelOld->doodle.x != modelNew->doodle.x || modelOld->doodle.y != modelNew->doodle.y)
    {
        clear_bitmap_32(baseCurr, modelOld->doodle.x, modelOld->doodle.y, clear_bitmap, 55 );
        render_doodle(&(modelNew->doodle), baseCurr);
    }
}


void render_doodle(Doodle *doodle, UINT32 *base)
{
    if(doodle->facing == 1)
        plot_bitmap_32(base, doodle->x, doodle->y, doodle_bitmap_right, 55 );
    else
        plot_bitmap_32(base, doodle->x, doodle->y, doodle_bitmap_left, 55 );
}


void render_monster(Monster *monster, UINT32 *base)
{

    plot_bitmap_32(base, monster->x, monster->y, monster_bitmap, 35 );


}



void render_platform(Platform *platforms, UINT32 *base)
{
    int i;

    for(i = 0; i < 15 ; i++){
        if(has_platform_moved(platforms) == 1)
        {
            clear_bitmap_32(base, platforms->prev_x, platforms->prev_y, clear_bitmap, 22 );
            plot_bitmap_32(base, platforms->x, platforms->y, platform_bitmap, 22 );

        }
            platforms ++;
    }
}
