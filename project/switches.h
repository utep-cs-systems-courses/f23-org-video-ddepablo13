#ifndef SWITCH_HEADER
#define SWITCH_HEADER

#define SW1 1
#define SW2 2
#define SW3 4
#define SW4 8

void switch_init();
void switch_interrupt_handler();
extern int switches;
char switch_update_interrupt_sense();
#define SWITCHES 15
char switch_update_interrupt_sense();

#endif
