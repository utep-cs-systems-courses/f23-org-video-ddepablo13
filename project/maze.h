#ifndef MAZE_DATA
#define MAZE_DATA

#include "lcdutils.h"
extern char maze_count;
//Current number of the maze the player is in
extern char maze_num;
//stored as 0000 rldu
extern const u_char maze_data[13][11][10];

extern const u_char mazeStartRow;
extern const u_char mazeStartCol;

extern u_int maze_bg_c;
extern u_int maze_wall_c;

/*
  row and col refer to position within the maze.
  automatically reads maze data to determine where to draw walls.
 */
void draw_tile(u_char row, u_char col);
void draw_maze();
void draw_tiles();
void draw_buffer();
void draw_directions();
void next_maze();
#endif
