#ifndef MODEL_H
#define MODEL_H

typedef struct 
{
  unsigned int x, y; 
  int delta_x, delta_y; 
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

void move_doodle(Doodle *doodle, int displacement_x, int displacement_y);

#endif

