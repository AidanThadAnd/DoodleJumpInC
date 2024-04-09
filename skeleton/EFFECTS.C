#include "effects.h"

int effects = 0;

/***********************************************************************
 * Name: doodle_lands
 * 
 * Purpose: sound effect is played when the doodle lands on the platform
 * Details: This function uses a combination of noise and envelope control
 *          to create a short ding sound
 * 
 * Inputs: None
 * Outputs: N/A
 * Returns: None
 ***********************************************************************/
void doodle_lands() 
{
    int oldIpl;
    long oldSsp;

    /*interrupt masking*/
    oldSsp = Super(0);
    oldIpl = set_ipl(7);
    Super(oldSsp);

    oldSsp = Super(0);

    set_noise(16);

    write_psg(MIXER_REG, MIXER_NONE);

    enable_channel(CHANNEL_A, 0, 1);
    enable_channel(CHANNEL_B, 0, 1);

    set_envelope(CHANNEL_A, 0x1000);
    
    TIMER_SNDFX = 0;    /*start timer*/
    effects = 1;

    Super(oldSsp);

    oldSsp = Super(0);
    set_ipl(oldIpl);
    Super(oldSsp);
}

/***********************************************************************
 * Name: platform_breaks
 * 
 * Purpose: sound effect is played when doodle lands on broken platform
 * 
 * Details: This function uses a combination of noise, tone, and 
 *          envelope control to create a short breaking sound
 * 
 * Inputs: None
 * Outputs: N/A
 * Returns: None
 ***********************************************************************/
void platform_breaks() 
{
    int oldIpl;
    long oldSsp;

    /*interrupt masking*/
    oldSsp = Super(0);
    oldIpl = set_ipl(7);
    Super(oldSsp);

    oldSsp = Super(0);

    set_tone(2, 4);
    set_noise(16);

    write_psg(MIXER_REG, MIXER_NONE);

    enable_channel(CHANNEL_A, 1, 1);
    enable_channel(CHANNEL_B, 1, 1);
    enable_channel(CHANNEL_C, 1, 1);

    set_envelope(CHANNEL_B, 0x1000);
    
    TIMER_SNDFX = 0;    /*start timer*/
    effects = 1;

    Super(oldSsp);

    oldSsp = Super(0);
    set_ipl(oldIpl);
    Super(oldSsp);
}

/***********************************************************************
 * Name: monster_near
 * 
 * Purpose: Sound effect for a monster attack, creating a buzz noise.
 * 
 * Details: This function utilizes the noise generator of the PSG to create
 *          a buzzing sound effect resembling a monster nearby.
 * 
 * Inputs: None
 * Outputs: N/A
 * Returns: None
 ***********************************************************************/

void monster_near() 
{
    int oldIpl;
    long oldSsp;

    oldSsp = Super(0);
    oldIpl = set_ipl(7);
    Super(oldSsp);

    oldSsp = Super(0);

    set_tone(1, 4);
    set_noise(16);

    enable_channel(CHANNEL_B, 1, 1);
    enable_channel(CHANNEL_C, 1, 1);

    write_psg(MIXER_REG, MIXER_NONE);

    set_envelope(CHANNEL_B, 0x1000);

    TIMER_SNDFX = 0;
    effects = 1;

    Super(oldSsp);

    oldSsp = Super(0);
    set_ipl(oldIpl);
    Super(oldSsp);
}

/***********************************************************************
 * Name: stop_effects
 * 
 * Purpose: clears psg registers to stop effects
 * 
 * Details: all sound effects are disabled
 *
 * Inputs: None
 * Outputs: N/A
 * Returns: None
 ***********************************************************************/
void stop_effects()
{
    /*disable b&c in mixer*/
    set_volume(CHANNEL_B, 0);
    set_volume(CHANNEL_C, 0);

    /*disable noise bits*/
    write_psg(NOISE_FREQ_REG, 0x00);

    /*disable envelope bits remove*/
    write_psg(ENV_FINE, 0x00);
    write_psg(ENV_ROUGH, 0x00);
    write_psg(ENV_SHAPE_CONTROL, 0x00);
}
