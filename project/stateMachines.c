#include <msp430.h>
#include "lcdutils.h"
#include "maze.h"
#include "player.h"
#include "stateMachines.h"

void maze_warp() {
  player_row = 0;
  player_col = 0;
  maze_num+= 1;
  if (maze_num == maze_count) maze_num = 0;
  draw_maze();
  draw_player();
}