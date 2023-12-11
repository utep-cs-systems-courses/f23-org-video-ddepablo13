#include <msp430.h>
#include "input.h"
#include "switches.h"

extern int paddle1Y, paddle2Y;
extern char switch_state_down;

void initializeInput() {
    switch_init();
}

void updatePaddles() {
    if (switch_state_down) {
        paddle1Y++; // Move paddle down
        // Add bounds checking
    } else {
        paddle1Y--; // Move paddle up
        // Add bounds checking
    }
}
