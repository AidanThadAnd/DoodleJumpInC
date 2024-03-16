/*
  Author: Aidan & Jacky
  Date: March 15, 2024
 
  Purpose:
    - This header file defines functions related to managing the Programmable Sound Generator (PSG) in the game.
 
  Functions:
    Function Name: write_psg
      Purpose:
        - Writes a value to a PSG register.
      Input:
        - reg: The register address to write to.
        - val: The value to write.
 
    Function Name: read_psg
      Purpose:
        - Reads a value from a PSG register.
      Input:
        - reg: The register address to read from.
      Output:
        - Returns the value read from the register.
 
    Function Name: set_tone
      Purpose:
        - Sets the tuning of a specific channel in the PSG.
      Input:
        - channel: The channel number (0-2).
        - tuning: The tuning value to set.
 
    Function Name: set_volume
      Purpose:
        - Sets the volume of a specific channel in the PSG.
      Input:
        - channel: The channel number (0-2).
        - volume: The volume level to set. 
    Function Name: enable_channel
      Purpose:
        - Enables or disables a channel in the PSG.
      Input:
        - channel: The channel number (0-2).
        - tone_on: Flag indicating whether tone should be enabled (1) or disabled (0).
        - noise_on: Flag indicating whether noise should be enabled (1) or disabled (0).
 
    Function Name: stop_sound
      Purpose:
        - Stops all sound output from the PSG.
 
    Function Name: set_noise
      Purpose:
        - Sets the tuning of the noise generator in the PSG.
      Input:
        - tuning: The tuning value to set.
 
    Function Name: set_envelope
      Purpose:
        - Sets the envelope shape and sustain level for the PSG.
      Input:
        - shape: The shape of the envelope.
        - sustain: The sustain level of the envelope.
 */

#ifndef PSG_H
#define PSG_H

include "types.h"

void write_psg(int reg, unsigned char val);
UINT8 char read_psg(int reg);
void set_tone(int channel, int tuning);
void set_volume(int channel, int volume);
void enable_channel(int channel, int tone_on, int noise_on);
void stop_sound();
void set_noise(int tuning);
void set_envelope(int shape, unsigned int sustain);

#endif
