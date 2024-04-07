#ifndef ISR_H
#define ISR_H

#include <osbind.h>

#define VBL_ISR 28
#define IKBD_ISR 70

typedef void (*Vector)(); /* a Vector is a function start addr. */
Vector installVector(int num, Vector vector);

void vbl_isr();
void ikbd_isr();
int set_ipl(int mask);

#endif
