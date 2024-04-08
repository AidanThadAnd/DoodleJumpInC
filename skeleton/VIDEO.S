; start and super are referenced from the suberlab folder, super.s
;
; 

; The GEMDOS call $20 (Page 161 of the Devpac manual) can be used to change
; the processor from user mode to supervisor mode, and then back again. 
; When switching modes, the first parameter is either the value of a new 
; system stack pointer, or 0 if you want to use the same stack after the
; switch.  When switching to supervisor mode, the old system stack 
; pointer is returned in D0    
    
        xdef    _get_video_base
        xdef    _set_video_base

_get_video_base:
        
    move.l  a0,-(sp)

    jsr     start

    lea     $FFFF8201,a0    ; video base register high
    movep.w (a0),d0
    lsl.l   #8,d0           ; multiply by 256.          

    jsr     super

    move.l  (sp)+,a0

    rts

_set_video_base:

    link    a6,#0
    movem.l d0/a0,-(sp)

    jsr start

    move.l  8(a6),d0        ; offset of 8
    lsr.l   #8,d0           ; divide by 256.
    lea     $FFFF8201,a0    ; video base register high
    movep.w d0,(a0)

    jsr super

    movem.l (sp)+,d0/a0
    unlk    a6
    rts

start:

    move.l d0,-(sp)

    nop
	clr.l	-(sp)		; set up GEMDOS call to enter supervisor
	move.w	#$20,-(sp)	; mode and to use the user stack
	trap	#1		; until toggling back to user mode
	addq.l	#6,sp		; clean up stack
	move.l	d0,old_ssp	; save old system stack pointer
    move.l  (sp)+,d0
    rts

super:

    move.l  d0,-(sp)
    move.l  (old_ssp),-(sp)     ; return to user mode, restoring
    move.w  #$20,-(sp)      	; system stack pointer
    trap    #1
    addq.l  #6,sp

    move.l  (sp)+,d0        
    rts

old_ssp:     ds.l    1
