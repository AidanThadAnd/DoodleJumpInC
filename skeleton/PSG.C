#include "psg.h"
#include "types.h"

void write_psg(int reg, unsigned char val) {
    volatile char *PSG_reg_select = 0xFF8800;
    volatile char *PSG_reg_write = 0xFF8802;

    *PSG_reg_select = reg;
    *PSG_reg_write = val;
}

UINT8 read_psg(int reg) {
    volatile char *PSG_reg_select = 0xFF8800;
    volatile char *PSG_reg_read = 0xFF8802;

    *PSG_reg_select = reg;
    return *PSG_reg_read;
}

void set_tone(int channel, int tuning) {
    if (channel >= 0 && channel <= 2) {
        write_psg(channel, tuning);
        write_psg(channel + 1, 0);
    }
}

void set_volume(int channel, int volume) {
    if (channel >= 0 && channel <= 2 && volume >= 0 && volume <= 15) {
        write_psg(8 + channel, volume);
    }
}

void enable_channel(int channel, int tone_on, int noise_on) {
    if (channel >= 0 && channel <= 2) {
        unsigned char val = read_psg(7);
        if (tone_on)
            val |= (1 << channel);
        else
            val &= ~(1 << channel);
        if (noise_on)
            val |= 0x3E;
        else
            val &= ~0x3E;
        write_psg(7, val);
    }
}

void stop_sound() {
    write_psg(8, 0);
}

