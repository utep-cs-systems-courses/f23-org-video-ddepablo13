#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "maze.h"
#include "player.h"
#include "stateMachines.h"

u_char player_row = 0;
u_char player_col = 0;

u_char prev_row = 0;
u_char prev_col = 0;

u_int player_color = COLOR_ORANGE;

void clear_last();
//Directions
//0000 rldu
void move_player(u_char dir) {
  u_char tile_dat = maze_data[maze_num][player_row][player_col];
  //See if can move
  if (dir & tile_dat) {
    prev_row = player_row;
    prev_col = player_col;
    switch(dir) {
    case 0x01:
      player_row -= 1;
      break;
    case 0x02:
      player_row += 1;
      break;
    case 0x04:
      player_col -= 1;
      break;
    case 0x08:
      player_col += 1;
      break;
    }
    clear_last();
    draw_player();

    if (player_col == 9 && player_row == 10) {
      maze_warp();
    }
  }
}

void draw_player() {
  u_char player_row_start = player_row * 10 + 2 + mazeStartRow;
  u_char player_col_start = player_col * 10 + 2 + mazeStartCol;
  u_char player_width = 6;
  u_char player_height = 6;

  fillRectangle(player_col_start, player_row_start, player_width, player_height, player_color);
}

void clear_last() {
  u_char prev_row_start = prev_row * 10 + 2 + mazeStartRow;
  u_char prev_col_start = prev_col * 10 + 2 + mazeStartCol;
  u_char player_width = 6;
  u_char player_height = 6;

  fillRectangle(prev_col_start, prev_row_start, player_width, player_height, maze_bg_c);
}
