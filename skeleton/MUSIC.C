#include "music.h"

int curr_note_a = 0;

const Note song[] = {
    {D_SHARP, QUARTER_NOTE},
    {D_SHARP, QUARTER_NOTE},
    {F_FLAT, QUARTER_NOTE},
    {D_SHARP, QUARTER_NOTE},
    {F_FLAT, QUARTER_NOTE},
    {C_SHARP, QUARTER_NOTE},
    {D_SHARP, QUARTER_NOTE},
    {F_FLAT, QUARTER_NOTE},
    {A_SHARP, QUARTER_NOTE},
    {C_SHARP, QUARTER_NOTE},
    {G_SHARP, QUARTER_NOTE},
    {F_FLAT, QUARTER_NOTE},
    {A_SHARP, QUARTER_NOTE},
    {G_SHARP, QUARTER_NOTE},
    {A_SHARP, QUARTER_NOTE},
};

int SONG_A = sizeof(song) / sizeof(song[0]);

void start_music()
{
    long oldssp = Super(0);

    write_psg(MIXER_REG, MIXER_NONE);   /*put mixer into default state*/
    
    /*first note of the song*/
    set_tone(0, song[curr_note_a].tuning);
     
    enable_channel(0, 1, 0);

    set_volume(0, 0x0C);
   
    Super(oldssp);
}

void update_music()
{
    int new_note_a = 0;
    /*Move to the next note on each channel where applicable*/
    if(TIMER_MUSIC >= song[curr_note_a].duration) {
        /*restart from the first note when the song finishes; otherwise, move on to the next note*/
    if (curr_note_a >= SONG_A - 1)
        curr_note_a = 0;
    else
        curr_note_a += 1;
        
        TIMER_MUSIC = 0;
        new_note_a = 1;
    }
    
    /* get the tone of the current note on each channel*/
    /*only use channel C for music if it is not currently being used for sound effects*/
      set_tone(0, song[curr_note_a].tuning);

    /*only turn volume back on if a new note has begun*/
        if(new_note_a == 1){
            enable_channel(CHANNEL_A, 1, 0);
    }
}

void stop_music(){
	long old_ssp = Super(0);
    
	stop_sound();
    
	Super(old_ssp);
}
