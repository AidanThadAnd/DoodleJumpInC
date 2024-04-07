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

    /*default value if register is invalid; this way, if it
    is combined with another value using bitwise &, the 
    result won't be affected by this value*/
    val = 0xFF;

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
        case 0:
            write_psg(A_FINE, fine_tuning);
            write_psg(A_COARSE, coarse_tuning);
            break;

        case 1:
            write_psg(B_FINE, fine_tuning);
            write_psg(B_COARSE, coarse_tuning);
            break;

        case 2:
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
        case 0:
            write_psg(A_VOL, volume);
            break;

        case 1:
            write_psg(B_VOL, volume);
            break;

        case 2:
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

    /*get the cont, att, alt, and hold bits to control shape*/
    shape_bits = shape & 0x000F;

    write_psg(ENV_SHAPE_CONTROL, shape_bits);
}

void enable_channel(int channel, int tone_on, int noise_on)
{
    /*by default, keep the value that is currently in the mixer*/
    UINT8 mixer_val = read_psg(MIXER_REG);

    switch (channel)
    {
        case 0:

            if(tone_on == 1 && noise_on == 1){
                mixer_val &= TONE_A & NOISE_A;
            }
            else if(tone_on == 1 && noise_on == 0){
                mixer_val &= TONE_A;
            }
            else if(tone_on == 0 && noise_on == 1){
                mixer_val &= NOISE_A;
            }
            /*if both are false, do nothing since neither bit is set*/
            break;

        case 1:

            if(tone_on == 1 && noise_on == 1){
                mixer_val &= TONE_B & NOISE_B;
            }
            else if(tone_on == 1 && noise_on == 0){
                mixer_val &= TONE_B;
            }
            else if(tone_on == 0 && noise_on == 1){
                mixer_val &= NOISE_B;
            }
            /*if both are false, do nothing since neither bit is set*/
            break;

        case 2:

            if(tone_on == 1 && noise_on == 1){
                mixer_val &= TONE_C & NOISE_C;
            }
            else if(tone_on == 1 && noise_on == 0){
                mixer_val &= TONE_C;
            }
            else if(tone_on == 0 && noise_on == 1){
                mixer_val &= NOISE_C;
            }
            /*if both are false, do nothing since neither bit is set*/
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
    write_psg(MIXER_REG, MIXER_NONE);     /*should this be MIXER_NONE since 0's mean on*/

    /*disable noise bits*/
    write_psg(NOISE_FREQ_REG, 0x00);

    /*disable envelope bits*/
    write_psg(ENV_FINE, 0x00);
    write_psg(ENV_ROUGH, 0x00);
    write_psg(ENV_SHAPE_CONTROL, 0x00);

    /*disable the volume of all channels*/
    set_volume(0, 0);
    set_volume(1, 0);
    set_volume(2, 0);

    Super(oldssp);
}
