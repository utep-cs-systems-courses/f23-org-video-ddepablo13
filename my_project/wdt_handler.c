#include <msp430.h>
#include "stateMachines.h"
#include "switches.h"

__interrupt_vec(WDT_VECTOR) WDT() {
    static char count = 0;
    if (++count == /* suitable value for game speed */) {
        count = 0;
        state_advance(); // Update game state
    }
}
