/*
*   Author(s):   Aiden & Jacky
*/
#include "IKBD.H"
bool key_repeat = false;
UINT8 ikbdSM = 0;

struct KeyQueue key_buff_enqueue = {
    {0}, /*array of key buffers*/
    0,   /*tail*/
    0,   /*head*/
    0,   /*fill level*/
    MSE_X_DEFAULT,
    MSE_Y_DEFAULT};

/*  
scancode that is passed in is simply the key number,
since this table is sorted in order it will parse to
the correct corresponding ascii
*/
const UINT8 ASCII_TABLE[TABLE_SIZE] = {
    0x00,
    0x1B,
    0x31,
    0x32,
    0x33,
    0x34,
    0x35,
    0x36,
    0x37,
    0x38,
    0x39,
    0x30,
    0x2D,
    0x3D,
    0x08,
    0x09,
    0x71,
    0x77,
    0x65,
    0x72,
    0x74,
    0x79,
    0x75,
    0x69,
    0x6F,
    0x70,
    0x5B,
    0x5D,
    0x0D,
    0x00,
    0x61,
    0x73,
    0x64,
    0x66,
    0x67,
    0x68,
    0x6A,
    0x6B,
    0x6C,
    0x3B,
    0x27,
    0x60,
    0x00,
    0x5C,
    0x7A,
    0x78,
    0x63,
    0x76,
    0x62,
    0x6E,
    0x6D,
    0x2C,
    0x2E,
    0x2F,
    0x00,
    0x00,
    0x00,
    0x20,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x2D,
    0x00,
    0x00,
    0x00,
    0x2B,
    0x00,
    0x00,
    0x00,
    0x00,
    0x7F,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x28,
    0x29,
    0x2F,
    0x2A,
    0x37,
    0x38,
    0x39,
    0x34,
    0x35,
    0x36,
    0x31,
    0x32,
    0x33,
    0x30,
    0x2E,
    0x0D};

/***********************************************************************
* Name: do_ikbd_isr
*
* Purpose: This function is the interrupt service routine for the
*          keyboard. 
*
* Details: Reads the keyboard (IKBD_RDR) converts the scan
*          code to ascii and enqueues the ascii value to the key board
*          buffer. Mouse movement is also handled here
***********************************************************************/    
void do_ikbd_isr()
{
    UINT8 ascii;
    UINT8 key_packet;

    *IKBD_CONTROL = 0x16;

    key_packet = getScanCode();

    if (ikbdSM == 0)
    {
        if (key_packet < IKBD_MOUSE_MOVE) /*if the key is not a mouse move*/
        {
            if ((key_packet & 0x80) != BREAK_CODE) /*if the key is not released (make code)*/
            {
                ascii = getAscii(key_packet);
                key_buff_enqueue(ascii); /*enqueue*/

                /*TODO: make sure the current key is the same as the prev key*/
                /*key_repeat = (ascii == key_buff_enqueue.buffer[key_buff_enqueue.head]) ? true : false;*/
                key_repeat = true;
            }
            else if ((key_packet & 0x80) == BREAK_CODE) /*if the key is released (break code)*/
            {
                key_repeat = false;
            }
        }
        else
        {
            key_buff_enqueue(key_packet); /*there is no ascii ?, throw the scancode on the queue*/
            ikbdSM++;
        }
    }
    else
    {
        ikbdSM >= 2
            ? (key_buff_enqueue.mY = min(max(key_buff_enqueue.mY + (char)key_packet, 0), 400), ikbdSM = 0)
            : (key_buff_enqueue.mX = min(max(key_buff_enqueue.mX + (char)key_packet, 0), 640), ikbdSM++);
    }

    *IKBD_CONTROL = 0x96;

    return;
}

/***********************************************************************
 * Name: key_buff_nqueue
 * 
 * Purpose: This function enqueues the key buffer
 * 
 * Inputs: ascii value of a key
 ***********************************************************************/
void key_buff_enqueue(UINT8 ascii)
{
    key_buff_enqueue.tail += 1;
    key_buff_enqueue.buffer[key_buff_enqueue.tail] = ascii;
    key_buff_enqueue.fillLevel += 1;
}


/***********************************************************************
 * Name: key_buff_dequeue
 * 
 * Purpose: This function dequeues the key buffer
 * 
 * Returns: ascii value of the key of size UINT8
 ***********************************************************************/
UINT8 key_buff_dequeue()
{
    UINT8 ascii;
    int oldIpl;
    long oldSsp;

    /*see lab 9 + notes and lecture notes 11 pg18*/
    oldSsp = Super(0);
    oldIpl = set_ipl(7);
    Super(oldSsp);

    key_buff_enqueue.head += 1;
    ascii = key_buff_enqueue.buffer[key_buff_enqueue.head];
    key_buff_enqueue.fillLevel -= 1;

    /*see lab 9 + notes and lecture notes 11 pg18*/
    oldSsp = Super(0);
    set_ipl(oldIpl);
    Super(oldSsp);

    return ascii;
}

/***********************************************************************
 * Name: getAscii
 * 
 * Purpose: Converts a scan code to an ascii value
 * 
 * Inputs: scan code
 * 
 * Returns: ascii value
 ***********************************************************************/
UINT8 getAscii(SCANCODE scancode)
{
    UINT8 ascii;
    ascii = ASCII_TABLE[scancode]; /*pass in the "key number"*/
    return ascii;
}

/***********************************************************************
 * Name: getScanCode
 * 
 * Purpose: Reads the IKDB
 * 
 * Returns: scan code
 ***********************************************************************/
UINT8 getScanCode()
{
    if (*IKBD_SR & 0x01)
        return *IKBD_RDR;
}

/***********************************************************************
 * Name: key_pending
 * 
 * Purpose: Checks if there is a key in the buffer
 * 
 * Returns: true if there is a key in the buffer, false otherwise
 ***********************************************************************/
bool key_pending()
{
    return key_buff_enqueue.fillLevel > 0 ? true : false;
}

UINT8 getPrev()
{
    UINT8 ascii;
    int oldIpl;
    long oldSsp;

    /*see lab 9 + notes*/
    oldSsp = Super(0);
    oldIpl = set_ipl(7);
    Super(oldSsp);

    ascii = key_buff_enqueue.buffer[key_buff_enqueue.head + 1];

    /*see lab 9 + notes*/
    oldSsp = Super(0);
    set_ipl(oldIpl);
    Super(oldSsp);

    return ascii;
}
