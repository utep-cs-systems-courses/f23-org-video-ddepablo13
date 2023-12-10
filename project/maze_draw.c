#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "maze.h"

u_int maze_bg_c = 0x7bef;
u_int maze_wall_c = 0x000f;

void draw_tile(u_char row, u_char col) {
  //Get pixel positions to draw at from position of cell in maze.
  //cellPos * cellSize + offset
  u_char draw_pos_row = row * 10 + mazeStartRow;
  u_char draw_pos_col = col * 10 + mazeStartCol;
  fillRectangle(draw_pos_col, draw_pos_row, 10, 10, maze_bg_c);
  //Draw corners
  fillRectangle(draw_pos_col, draw_pos_row, 2, 2, maze_wall_c);
  fillRectangle(draw_pos_col + 8, draw_pos_row, 2, 2, maze_wall_c);
  fillRectangle(draw_pos_col, draw_pos_row + 8, 2, 2, maze_wall_c);
  fillRectangle(draw_pos_col + 8, draw_pos_row + 8, 2, 2, maze_wall_c);

  u_char cell_data = maze_data[maze_num][row][col];
  if (!(cell_data & 1)) { // can't go up
    fillRectangle(draw_pos_col + 2, draw_pos_row, 6, 2, maze_wall_c);
  }
  if (!(cell_data & 2)) {//can't go down
    fillRectangle(draw_pos_col + 2, draw_pos_row + 8, 6, 2, maze_wall_c);
  }
  if (!(cell_data & 4)) {//can't go left
    fillRectangle(draw_pos_col, draw_pos_row + 2, 2, 6, maze_wall_c);
  }
  if (!(cell_data & 8)) {//can't go right
    fillRectangle(draw_pos_col + 8, draw_pos_row + 2, 2, 6, maze_wall_c);
  }
}


void draw_tiles() {
  for(char r = 0; r < 11; r++) {
    for (char c = 0; c < 10; c++) {
      draw_tile(r,c);
    }
  }
}

void draw_maze() {
  /*128 wide
    10 pixel cells?
    12 cells on a screen
    1 cell + 4 pixels on each side as border
    10 wide maze max
    160 tall
    want 7 pixels on top
    using bottom 15 for controls
    leaves me with 138 usable pixels
    use 14 pixels top and bottom buffer
    110 pixels for maze
    11 cells
    buffer is from
    col 0 to 13 and 114 to 127
    row 7 to 20 and 132 to 144
    maze can be rendered from
    col 14 to 113
    row 21 to 131
  */
  //use void fillRectangle(u_char colMin, u_char rowMin, u_char width, u_char height, u_int colorBGR);
  draw_buffer();
  //draw maze
  u_char mazeHeight = 110, mazeWidth = 100;
  fillRectangle(mazeStartCol, mazeStartRow, mazeWidth, mazeHeight, COLOR_GOLD);

  for (u_char row_iter = 0; row_iter < 11; row_iter++) {
    for (u_char col_iter = 0; col_iter < 10; col_iter++) {
      draw_tile(row_iter, col_iter);
    }
  }
}

void draw_buffer() {
  //draw buffer first
  u_char bufferStartCol = 0, bufferStartRow = 7, bufferEndCol = 127, bufferEndRow = 144;
  u_char bufferWidth = bufferEndCol - bufferStartCol + 1; //128
  u_char bufferHeight = bufferEndRow - bufferStartRow + 1; //138
  fillRectangle(bufferStartCol, bufferStartRow, bufferWidth, bufferHeight, COLOR_BROWN);
  fillRectangle(mazeStartCol-2, mazeStartRow - 2, 104, 114, 0x4a69);
  //four squares: (11,18) (111,18) (11,128) (111,128)
  fillRectangle(11,18,6,6,COLOR_GOLD);
  fillRectangle(111,18,6,6,COLOR_GOLD);
  fillRectangle(11,128,6,6,COLOR_GOLD);
  fillRectangle(111,128,6,6,COLOR_GOLD);

}

void draw_directions() {
  u_int bg = COLOR_BLACK;
  u_char width = screenWidth, height = screenHeight;
  char *arrow_test = "SW1";
  drawString5x7(8, 145, arrow_test, COLOR_CYAN, bg);
  drawChar5x7(14, screenHeight - 7, 0x80, COLOR_CYAN, bg);
  arrow_test = "SW2";
  drawString5x7(40, 145, arrow_test, COLOR_CYAN, bg);
  drawChar5x7(46, screenHeight - 7, 0x81, COLOR_WHITE, bg);
  arrow_test = "SW3";
  drawString5x7(71, 145, arrow_test, COLOR_CYAN, bg);
  drawChar5x7(77, screenHeight - 7, 0x82, COLOR_GREEN, bg);
  arrow_test = "SW4";
  drawString5x7(103, 145, arrow_test, COLOR_CYAN, bg);
  drawChar5x7(109, screenHeight - 7, 0x83, COLOR_RED, bg);
}
