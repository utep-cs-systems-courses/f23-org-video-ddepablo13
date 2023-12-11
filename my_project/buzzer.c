#include <msp430.h>
#include "buzzer.h"

void buzzer_init() {
  /* Setup buzzer to PWM output */
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6; // enable output to buzzer (P2.6)

  // Timer configuration (PWM)
  TA1CCR0 = 1000; // PWM period
  TA1CCTL1 = OUTMOD_3; // TA1CCR1 reset/set
  buzzer_set_period(0); // Start with buzzer off
}

void buzzer_set_period(short cycles) {
  TA1CCR1 = cycles; // TA1CCR1 PWM duty cycle
  TA1CTL = TASSEL_2 + MC_1; // SMCLK, Up mode
}

void buzzer_stop() {
  buzzer_set_period(0); // stop the buzzer
}
