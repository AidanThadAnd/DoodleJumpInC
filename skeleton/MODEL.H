#ifndef MODEL_H
#define MODEL_H

typedef struct 
{
  unsigned int x, y; 
  int delta_x, delta_y; 
} doodle;

typedef struct 
{
  unsigned int x, y; 
} monster;

typedef struct 
{
  unsigned int x, y; 
  int delta_x;
} platform;

#endif

