#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"
#include "maze.h"
#include "player.h"

u_int bg = COLOR_BLACK;
short redrawScreen = 1;

void wdt_c_handler() {

}

int main() {
  configureClocks();
  lcd_init();
  switch_init();

  clearScreen(bg);

  draw_maze();
  draw_directions();
  draw_player();

  or_sr(0x18);

  return 0;
}
