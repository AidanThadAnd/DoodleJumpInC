#include "ISR.H"

/***********************************************************************
 * Name: installVector
 * 
 * Purpose: Installs a new interrupt vector
 * 
 * Inputs: num - the interrupt vector number
 *         vector - the new interrupt vector
 * 
 * Returns: The original interrupt vector
 ***********************************************************************/
Vector installVector(int num, Vector vector)
{
    Vector original;    
    Vector *vectp = (Vector *)((long)num << 2); /* convert to addr. */
    long old_ssp = Super(0); 

    original = *vectp; /* save original vector */
    *vectp = vector; /* install new vector */
    
    Super(old_ssp); 
    return original;    
}
