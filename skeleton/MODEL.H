#ifndef MODEL_H
#define MODEL_H

typedef struct 
{
  unsigned int x, y; 
  int delta_x, delta_y; 
  int facing;
} Doodle;

typedef struct 
{
  unsigned int x, y; 
} Monster;

typedef struct 
{
  unsigned int x, y; 
  int delta_x;
} Platform;

typedef struct {
    Doodle doodle;
    Monster monster;
    Platform platforms[7];  
} Model;

void initialize_model(Model *model);
void move_doodle(Doodle *doodle, int displacement_x, int displacement_y);
void move_platform(Platform *platform);

#endif

