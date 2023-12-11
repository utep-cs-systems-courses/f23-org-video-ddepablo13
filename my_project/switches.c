#include <msp430.h>
#include "switches.h"

char switch_state_down_1 = 0, switch_state_down_2 = 0;
char switch_state_down_3 = 0, switch_state_down_4 = 0;

static char switch_update_interrupt_sense() {
    char p2val = P2IN;
    // Update switch interrupt to detect changes from current buttons
    P2IES |= (p2val & SWITCHES); // If switch up, sense down
    P2IES &= (p2val | ~SWITCHES); // If switch down, sense up
    return p2val;
}

void switch_init() {
    P2REN |= SWITCHES; // Enables resistors for switches
    P2IE |= SWITCHES; // Enable interrupts from switches
    P2OUT |= SWITCHES; // Pull-ups for switches
    P2DIR &= ~SWITCHES; // Set switches' bits for input
    switch_update_interrupt_sense();
}

void switch_interrupt_handler() {
    char p2val = switch_update_interrupt_sense();
    switch_state_down_1 = (p2val & SW1) ? 0 : 1; // 0 when SW1 is up
    switch_state_down_2 = (p2val & SW2) ? 0 : 1; // 0 when SW2 is up
    switch_state_down_3 = (p2val & SW3) ? 0 : 1; // 0 when SW3 is up
    switch_state_down_4 = (p2val & SW4) ? 0 : 1; // 0 when SW4 is up
}
