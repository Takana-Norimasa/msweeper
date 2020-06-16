#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<string.h>
#include<termio.h>
#include<curses.h>

typedef struct{
	bool is_opend;
	int hint;
	enum {NONE, HINT, MINE} state;
}Block;

typedef struct{
	int size;
	int mine_num;
	Block **matrix;
}Field;

Field *field;

// setup.c
void create_field();
void get_field_size();

// display.c
void display_field();
void display_block(Block *block);

// playgame.c
void playgame();
void get_open_block(int *x,int *y);
