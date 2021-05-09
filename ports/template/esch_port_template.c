#include "esch.h"

void esch_port_init()
{
    /*
    * Init timer with 1 kHz for esch_config_template.h example
    * Or with any other interval and match it to ESCH_TICK_FREQ
    *
    */

    /* 
    * Enable timer and interrupts 
    * Interrupt for this timer should be of highest priority
    * Add esch_tick_advance() call inside corresponding ISR
    * update event
    */
}