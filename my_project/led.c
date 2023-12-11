#include <msp430.h>
#include "led.h"

void led_init() {
    P1DIR |= LEDS;
    led_update();
}

void led_update() {
    P1OUT &= ~LEDS;   // Clear bits for off leds
    P1OUT |= LED_RED; // Set bit for red on
}
