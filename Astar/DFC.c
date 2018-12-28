#include "DFC.h"
#include "console.h"
#include <stdio.h>
#include <stdlib.h>
void game_field(){
	for (int i = 0; i < SIZE_X; i++){
		for (int j = 0; j < SIZE_Y; j++){
			field[i][j].char_field = ' ';
		}
	}
}

static void con_charAt(int ch, int color, int x, int y) {
	con_gotoXY(x, y);
	con_setColor(color);
	con_outTxt("%c", ch);
}

void painter(int type, int x1, int y1,char ch){
	switch (type) {
	case -1:
		con_charAt(FIELD, COLOR_FIELD, FIELD_X + x1, FIELD_Y + y1);
		break;

	case 0:
		con_charAt(FIELD, COLOR_WALL, FIELD_X + x1, FIELD_Y + y1);
		break;

	case 1:
		con_charAt(FIELD, COLOR_OBJ, FIELD_X + x1, FIELD_Y  + y1);
		break;
	case 2:
		con_charAt(FIELD, COLOR_TEXT, FIELD_X + x1, FIELD_Y + y1);
		break;
	case 5:
		con_charAt(FIELD, COLOR_WAVE, FIELD_X  + x1, FIELD_Y + y1);
		break;
	case 6:
		con_charAt(ch, COLOR_PATH, FIELD_X  + x1, FIELD_Y  + y1 );
		break;
	case 7:
		con_charAt(ch, COLOR_RES, FIELD_X + x1, FIELD_Y  + y1);
		break;
	case 8:
		con_charAt(ch, COLOR_CAR, FIELD_X + x1, FIELD_Y + y1);
		break;

	}
}

void random_draw(){
	con_clearScr();

	for (int i = 0; i < SIZE_X ; i++){
		for (int j = 0; j < SIZE_Y; j++){
			if (i == 0 || j == 0 || j == SIZE_Y-1  || i == SIZE_X-1 ) {
				field[i][j].char_field = FIELD;
				painter(0, i, j, 0, field[i][j].char_field);
				field[i][j].obj = 1;
			}
			else
				if (rand() % EVERY == 0) {
					field[i][j].char_field = OBJ;
					painter(1, i, j, 0, field[i][j].char_field);
					field[i][j].obj =1;
				}
				else {
					field[i][j].char_field = FIELD;
					painter(-1, i, j, 0, field[i][j].char_field);
					field[i][j].obj = 0;
				}
			field[i][j].open = 0;
			field[i][j].stepcounter = 99999;
			field[i][j].colored = 0;
		}
	}
}
void user_draw(FILE* file) {								//2-wall 1-obj 0-field
	con_clearScr();
	char buf[SIZE_X+2];
	for (int i = 0; i < SIZE_Y; i++){
		fgets(buf, SIZE_X + 2, file);
		for (int j = 0; j < SIZE_X; j++){
			if(buf[j]=='2'){	
				field[j][i].char_field = OBJ;
				painter(0, j, i, 0, field[j][i].char_field);
				field[j][i].obj = 1;
			}
			else if (buf[j] == '1') {
				field[j][i].char_field = OBJ;
				painter(1, j, i, 0, field[j][i].char_field);
				field[j][i].obj = 1;
			}
			else {
				field[j][i].char_field = FIELD;
				painter(-1, j, i, 0, field[j][i].char_field);
				field[j][i].obj = 0;
			}
			field[j][i].open = 0;
			field[j][i].stepcounter = 99999;
			field[j][i].colored = 0;
		}
	}
}
void clearmap() {
	for (int i = 1; i < SIZE_X; i++)
	{
		for (int j = 1; j < SIZE_Y; j++)
		{
			field[i][j].open = 0;
			field[i][j].stepcounter = 99999;
			field[i][j].colored = 0;
		}
	}
}




