#include "VBL.H"

/*init timers*/
int TIMER_MUSIC = 0;
int TIMER_SNDFX = 0;
int TIMER_LANDED = 0;

int seconds = 0;
UINT32 ticks = 0;
int vbl_flag = 0;

void do_vbl_isr()
{
    ticks += 1;

    /*increment timers*/
    TIMER_MUSIC++;
    TIMER_SNDFX++;

    update_music();

    /*increment seconds every 70 invocations of this function*/
    if (ticks % 70 == 0)
    {
        seconds++;
    }
    vbl_flag = 1;
}
