/*
  Author: Aidan & Jacky
*/
#ifndef PSG_H
#define PSG_H

#include <osbind.h>
#include "types.h"

/*SSG (Software-controlled Sound Generator) 
is the YM2149's PSG(Programmable sound generator)*/

/*according to page 7 of YM2149 documentation*/

#define CHANNEL_A 0
#define CHANNEL_B 1
#define CHANNEL_C 2

/*fine tune registers*/
#define A_FINE 0x0
#define B_FINE 0x2
#define C_FINE 0x4

/*coarse tune registers*/
#define A_COARSE 0x1
#define B_COARSE 0x3
#define C_COARSE 0x5

/*volume registers*/
#define A_VOL 0x8
#define B_VOL 0x9
#define C_VOL 0xA

/*mixer and noise*/
#define NOISE_FREQ_REG 0x6
#define MIXER_REG 0x7
/*
enable channels on mixer (to mix tone and noise include &'s)

Details of the YM2149 Mixer Register (pg.20):

if noise bit = 0 AND tone bit = 0 then output is combined by the mixer
if noise bit = 0 AND tone bit = 1 then output noise signal
if noise bit = 1 AND tone bit = 0 then output tone signal
if noise bit = 1 AND tone bit = 1 then output nothing
*/
#define MIXER_NONE 0x3F         

#define TONE_A 0x3E    
#define TONE_B 0x3D    
#define TONE_C 0x3B    

#define NOISE_A 0x37   
#define NOISE_B 0x2F   
#define NOISE_C 0x1F 

/*envelopes*/
/*page 34 talks about how sound effects can be made using noise. */
#define ENV_FINE 0xB
#define ENV_ROUGH 0xC
#define ENV_SHAPE_CONTROL 0xD

/**
 * Function Name: write_psg
 * Purpose: Writes the given byte value to the given PSG register (0-15)
 *          This helper function used by other functions in the psg module
 * Inputs: reg - PSG register (0 - 15)
 *         val - value to write (0 - 255)
 */
void write_psg(int reg, UINT8 val);

/**
 * Function Name : read_psg
 * Purpose: Read value of a register (for testing purposes)
 * Input: reg - PSG register (0 - 15)
 * Outputs: UINT8 - value stored in the given register
 */
UINT8 read_psg(int reg);

/**
 * Function Name: set_tone 
 * Purpose: Loads the tone registers (coarse and fine) for the given channel 
 *          (0 = A, 1 = B, 2 = C) with the given 12-bit tuning
 * Inputs: channel - channel being modified
 *         tuning  - fine and coarse tuning values to load into the given channel
 */
void set_tone(int channel, int tuning);

/**
 * Function Name: set_volume
 * Purpose: Loads the volume register for the given channel
 * 
 * Inputs: channel - channel being modified
 *         vol     - volume to load into the given channel
 */
void set_volume(int channel, int vol);

/**
 * Function Name: set_noise
 * Purpose: Load the noise register with the given tuning
 * 
 * Inputs: tuning - tuning to load into the noise register
 */
void set_noise(int tuning);

/**
 * Function Name: set_envelope
 * Purpose: Loads the PSG envelope control registers with the given envelope
 *          shape and 16-bit sustain
 * 
 * Inputs: shape - hold bits to load into the shape
 *                 control register
 *         sustain - fine and rough sustain values to load into the envelope
 */
void set_envelope(int shape, UINT16 sustain);

/**
 * Function Name: enable_channel
 * Purpose: Turns the given channel's tone and noise signals on/off
 * 
 * Inputs: channel - channel being modified
 *         tone_on - if true, to turn on, otherwise false
 *         noise_on - if true, to turn on, otherwise false
 */
void enable_channel(int channel, int tone_on, int noise_on);

/**
 * Function Name: stop_sound
 * Purpose: Silences all PSG sound production
 */
void stop_sound();

#endif
