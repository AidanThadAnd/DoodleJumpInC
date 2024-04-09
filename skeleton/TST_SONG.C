#include <osbind.h>
#include <stdio.h>
#include "isr.h"
#include "vbl.h"
#include "effects.h"
#include "music.h"

int main() {
    Vector origVBL = installVector(VBL_ISR, vbl_isr);

    start_music();
    update_music();
     /*uninstall vectors for IKBD and VBL*/
    installVector(VBL_ISR, origVBL);

    return 0;
}
