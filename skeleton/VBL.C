#include "VBL.H"

/*init timers*/
int TIMER_MUSIC = 0;
int TIMER_SNDFX = 0;
int TIMER_LANDED = 0;

int seconds;
UINT32 ticks;
int vbl_flag;

void do_vbl_isr()
{
    int sndfx_on;

    ticks += 1;

    /*increment timers*/
    TIMER_MUSIC++;
    TIMER_SNDFX++;

    sndfx_on = update_sndfx();
    update_music(sndfx_on);

    /*increment seconds every 70 invocations of this function*/
    if (ticks % 70 == 0)
    {
        seconds++;
    }
    vbl_flag = 1;
}

UINT32 getTime()
{
    return ticks;
}

void set_vbl_flag() {
    vbl_flag = 0;
}

void set_ticks() {
    ticks = 0;
}

void set_seconds() {
    seconds = 0;
}
