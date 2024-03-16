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
