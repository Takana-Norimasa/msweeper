#include "msweeper.h"

void get_command(){
	char command;

	do{
		display_field();
		printf("[o:open f:flag or h,j,k,l]>>");
		command=getChar();

		switch(command){
			case 'o':
				block_open(field->cursor_x,field->cursor_y);
				break;
			case 'f':
				raise_your_flag(&(field->matrix[field->cursor_x][field->cursor_y]));
				break;
			case 'h':
				if(0 < field->cursor_x)
					(field->cursor_x)--;
				break;
			case 'j':
				if(field->cursor_y < field->size_x-1)
					(field->cursor_y)++;
				break;
			case 'k':
				if(0 < field->cursor_y)
					(field->cursor_y)--;
				break;
			case 'l':
				if(field->cursor_x < field->size_y-1)
					(field->cursor_x)++;
				break;
			default:
				command=0;
		}
	}while(!((0 < field->cursor_y && field->cursor_y < field->size_x-1) && (0 < field->cursor_x && field->cursor_x < field->size_y-1)) || command==0);
}

void raise_your_flag(Block *block){
	if(block->is_opened==false)
		block->raise_flag=!(block->raise_flag);
}

void open_automatically(int x,int y){
	int i,j;

	if(field->matrix[x][y].state==HINT && !(field->matrix[x][y].is_opened)){
		field->matrix[x][y].is_opened=true;
		field->opened_block++;
		return;
	}

	if(field->matrix[x][y].is_opened==false){
		field->matrix[x][y].is_opened=true;
		field->opened_block++;
	}

	if(0<=x-1 && field->matrix[x-1][y].is_opened==false)
		open_automatically(x-1,y);
	if(x+1<field->size_y && field->matrix[x+1][y].is_opened==false)
		open_automatically(x+1,y);
	if(0<=y-1 && field->matrix[x][y-1].is_opened==false)
		open_automatically(x,y-1);
	if(y+1<field->size_x && field->matrix[x][y+1].is_opened==false)
		open_automatically(x,y+1);
}

void block_open(int x,int y){
	Block *block=&(field->matrix[x][y]);
	int to_clear=(field->size_y*field->size_x)-field->mine_num;

	if(block->is_opened || block->raise_flag)
		return;

	block->is_opened=true;
	field->opened_block++;

	if(block->state==NONE)
		open_automatically(x,y);


	if(block->state==MINE)
		gameover=true;

	if(field->opened_block==to_clear)
		gameclear=true;

	printf("\nto_clear:%d\n",to_clear);
	printf("opened_block:%d\n",field->opened_block);
}

void playgame(){
	int x,y;
	gameover=false;
	gameclear=false;

	while(1){
		get_command();
		if(gameover | gameclear) break;
	}

	if(gameover) display_gameover();
	if(gameclear) display_gameclear();
}
