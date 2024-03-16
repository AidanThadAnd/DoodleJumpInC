#include "music.h"
#include "psg.h"

#define MELODY_LENGTH 5
int melody[MELODY_LENGTH] = {451,402,379,319,301};

int current_note_index = 0;
unsigned int time_since_last_note = 0;

void start_music() {
    set_tone(0, melody[0]); 
    enable_channel(0, 1, 0); 
    set_volume(0,10);
}

void update_music(unsigned int time_elapsed) {

    }
