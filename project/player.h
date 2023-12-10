#ifndef PLAYER_HEAD
#define PLAYER_HEAD

//Player data
extern u_char player_row;
extern u_char player_col;
extern u_char prev_row;
extern u_char prev_col;

extern u_int player_color;

//Directions
//0000 rldu
void move_player(u_char dir);

void draw_player();

#endif
