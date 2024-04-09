#include "psg.h"

volatile char *PSG_reg_select = 0xFF8800;
volatile char *PSG_reg_write  = 0xFF8802;

void write_psg(int reg, UINT8 val)
{
    /*check if register and value to write are both valid*/
    if(reg >= 0 && reg <= 15 && val >= 0 && val <= 255)
    {    
        *PSG_reg_select = reg;
        *PSG_reg_write  = val;
    }
}

UINT8 read_psg(int reg)
{
    UINT8 val;  

    if(reg >= 0 && reg <= 15)
    {   
        *PSG_reg_select = reg;
        val = *PSG_reg_select;
    }
    return val;
}

void set_tone(int channel, int tuning)
{
    /*separate 12-bit tuning into individual 8-bit and 4-bit values*/
    UINT8 fine_tuning = tuning & 0x00FF;           /*LSB*/
    UINT8 coarse_tuning = (tuning & 0x0F00) >> 8;  /*MSB*/

    switch(channel)
    {
        case CHANNEL_A:
            write_psg(A_FINE, fine_tuning);
            write_psg(A_COARSE, coarse_tuning);
            break;

        case CHANNEL_B:
            write_psg(B_FINE, fine_tuning);
            write_psg(B_COARSE, coarse_tuning);
            break;

        case CHANNEL_C:
            write_psg(C_FINE, fine_tuning);
            write_psg(C_COARSE, coarse_tuning);
            break;

        default:
            break;
    }
}

void set_volume(int channel, int vol)
{
    /*get the 5-bit value from the int*/
    UINT8 volume = vol & 0x001F;

    switch(channel)
    {
        case CHANNEL_A:
            write_psg(A_VOL, volume);
            break;

        case CHANNEL_B:
            write_psg(B_VOL, volume);
            break;

        case CHANNEL_C:
            write_psg(C_VOL, volume);
            break;

        default:
            break;  
    }
}

void set_noise(int tuning)
{
    /*get the 5-bit value from the int*/
    UINT8 freq = tuning & 0x001F;
    write_psg(NOISE_FREQ_REG, freq);
}

void set_envelope(int shape, UINT16 sustain)
{
    UINT8 sustain_fine, sustain_rough, shape_bits;

    /*separate 16-bit sustain into 2 individual 8-bit values*/
    sustain_fine = sustain & 0x00FF;           /*LSB*/
    sustain_rough = (sustain & 0xFF00) >> 8;   /*MSB*/

    write_psg(ENV_FINE, sustain_fine);
    write_psg(ENV_ROUGH, sustain_rough);

    shape_bits = shape & 0x000F;

    write_psg(ENV_SHAPE_CONTROL, shape_bits);
}

void enable_channel(int channel, int tone_on, int noise_on)
{
    UINT8 mixer_val = read_psg(MIXER_REG);

    switch (channel)
    {
        case CHANNEL_A:

            if(tone_on == 1 && noise_on == 1){
                mixer_val &= TONE_A & NOISE_A;
            }
            else if(tone_on == 1 && noise_on == 0){
                mixer_val &= TONE_A;
            }
            else if(tone_on == 0 && noise_on == 1){
                mixer_val &= NOISE_A;
            }
            break;

        case CHANNEL_B:

            if(tone_on == 1 && noise_on == 1){
                mixer_val &= TONE_B & NOISE_B;
            }
            else if(tone_on == 1 && noise_on == 0){
                mixer_val &= TONE_B;
            }
            else if(tone_on == 0 && noise_on == 1){
                mixer_val &= NOISE_B;
            }
            break;

        case CHANNEL_C:

            if(tone_on == 1 && noise_on == 1){
                mixer_val &= TONE_C & NOISE_C;
            }
            else if(tone_on == 1 && noise_on == 0){
                mixer_val &= TONE_C;
            }
            else if(tone_on == 0 && noise_on == 1){
                mixer_val &= NOISE_C;
            }
            break;

        default:
            break;
    }

    write_psg(MIXER_REG, mixer_val);
}

void stop_sound()
{
    long oldssp = Super(0);
    /*turn all channels off in the mixer*/
    write_psg(MIXER_REG, MIXER_NONE);  

    /*disable noise bits*/
    write_psg(NOISE_FREQ_REG, 0x00);

    /*disable envelope bits*/
    write_psg(ENV_FINE, 0x00);
    write_psg(ENV_ROUGH, 0x00);
    write_psg(ENV_SHAPE_CONTROL, 0x00);

    /*disable the volume of all channels*/
    set_volume(CHANNEL_A, 0);
    set_volume(CHANNEL_B, 0);
    set_volume(CHANNEL_C, 0);

    Super(oldssp);
}
