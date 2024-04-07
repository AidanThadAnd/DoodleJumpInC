/************************************************************************
*   File:       IKBD.H
*
*   Author(s):  Aidan & Jacky
*
*   Purpose:    This module contains the IKBD interrupt service routine
*               and the keyboard buffer queue.
***********************************************************************/
#ifndef IKBD_H
#define IKBD_H

#include "types.h"
#include "isr.h"
#include "vbl.h"
#include <osbind.h>

#define RDR_FULL ((UINT8)0x01)
#define IKBD_MOUSE_MOVE 0xF8 
#define IKBD_BUFFER_SIZE 256
#define TABLE_SIZE 0x73
#define BREAK_CODE 0x80
/*default pos of cusrsor is the center of the screen*/
#define MSE_X_DEFAULT 0x320 
#define MSE_Y_DEFAULT 0x200
#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))

extern volatile UINT8 *const IKBD_CONTROL = 0xFFFC00; /*contregister (write only)*/
extern volatile UINT8 *const IKBD_SR = 0xFFFC00;      /*status register (read only)*/
extern volatile SCANCODE *const IKBD_RDR = 0xFFFC02;  /*data register (read only)*/
extern bool key_repeat;

extern const UINT8 ASCII_TABLE[TABLE_SIZE];


struct Key_queue
{
    UINT8 buffer[256];
    UINT8 tail;
    UINT8 head;
    UINT16 fillLevel;
    int mse_x; /*mouse x*/
    int mse_y; /*mouse y*/
};

extern UINT8  ikbdSM;  
extern struct Key_queue key_buffer_queue;

void do_ikbd_isr();
void key_buff_enqueue(UINT8 );
UINT8 key_buff_dequeue();
UINT8 getScanCode();
bool key_pending();
UINT8 getAscii(SCANCODE scancode);
UINT8 getPrev();

#endif
