#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<sys/time.h>
#include<string.h>
#include<termio.h>
#include<curses.h>

typedef struct{
	bool is_opened;
	bool raise_flag;
	int hint;
	enum {NONE, HINT, MINE, FLAG} state;
}Block;

typedef struct{
	int size_x;
	int size_y;
	int cursor_x;
	int cursor_y;
	int mine_num;
	int remain_flag;
	int opened_block;
	Block **matrix;
}Field;

Field *field;

// setup.c
void create_field();
void get_field_size();
void set_hint();
void set_mine(int first_x,int first_y);
int check_around(int x,int y);

// display.c
void display_prompt();
void display_field();
void display_block(Block *block,int x,int y);
void display_gameover();
void display_gameclear();

// playgame.c
bool gameover;
bool gameclear;
void playgame();
void get_command();
void block_open(int x,int y);
void raise_your_flag(Block *block);
void open_automatically(int x,int y);

// getChar.c
char getChar();
