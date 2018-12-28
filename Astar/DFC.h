#pragma once
#include <stdio.h>
#define SIZE_X 200
#define SIZE_Y 45
#define FIELD          ' '  
#define OBJ          ' '
#define EVERY 5
#define COLOR_WALL	1
#define COLOR_FIELD	2
#define COLOR_OBJ   3
#define COLOR_WAVE	4
#define COLOR_PATH	5
#define COLOR_RES	6
#define COLOR_CAR	7
#define COLOR_TEXT  8
#define FIELD_X        0
#define FIELD_Y        0

struct field
{
	char char_field;
	int obj;
	int stepcounter;
	int open;
	float h;
	int colored;
}field[SIZE_X][SIZE_Y];

typedef struct {
	int* path;
	int size;
	int allocsize;
}path_t;

static void init_colors();
void random_draw();
void painter(int type, int x1, int y1,char ch);
static void con_charAt(int ch, int color, int x, int y);
void game_field();
void user_draw(FILE* file);
void clearmap();