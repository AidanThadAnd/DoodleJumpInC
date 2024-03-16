#include <osbind.h>
#include "psg.h"
#include "music.h"

int main() {
    long old_ssp = Super(0);
        
    start_music();

    while (!Cconis())		/* tone now playing, await key */
		; 

    stop_sound();
    
    Cnecin();

    Super(old_ssp);
    return 0;
}
