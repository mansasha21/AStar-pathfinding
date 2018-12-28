#define _CRT_SECURE_NO_WARNINGS
#include "Astar.h"
#include "moving.h"
#include <stdio.h>
#include <stdlib.h>
#include "console.h"
#include "DFC.h"

static void init_colors() {
	con_initPair(COLOR_WALL, CON_COLOR_BLUE, CON_COLOR_BLUE);
	con_initPair(COLOR_FIELD, CON_COLOR_WHITE, CON_COLOR_WHITE);
	con_initPair(COLOR_OBJ, CON_COLOR_RED, CON_COLOR_RED);
	con_initPair(COLOR_WAVE, CON_COLOR_WHITE, CON_COLOR_CYAN);
	con_initPair(COLOR_PATH, CON_COLOR_WHITE, CON_COLOR_GREEN);
	con_initPair(COLOR_RES, CON_COLOR_MY1, CON_COLOR_MY1);
	con_initPair(COLOR_CAR, CON_COLOR_MY1, CON_COLOR_WHITE);
	con_initPair(COLOR_TEXT, CON_COLOR_WHITE, CON_COLOR_BLACK);
}
int right_input(int ans,char* input,int num) {
	int badway = 1 ;
	while (badway) {
		fgets(input, 100, stdin);
		sscanf(input, "%d", &ans);
		switch (num)
		{ 
		case 1:
			if (ans != 1 && ans != 2) {
				puts("\tTRY AGAIN, INCORRECT ANSWER");
				break;
			}
			else {
				badway = 0;
				break;
			}
		case 2:
			if (ans < 1 || ans >199) {
				puts("\tTRY AGAIN, INCORRECT ANSWER");
				break;
			}
			else {
				badway = 0;
				break;
			}
		case 3:
			if (ans < 1 || ans > 44) {
				puts("\tTRY AGAIN, INCORRECT ANSWER");
				break;
			}
			else {
				badway = 0;
				break;
			}
		default:
			break;
		}
	}
	return ans;
}
void UI(void) {
	int points[4];
	int ans = 0,checker=1;
	char text[100];
	FILE* file = fopen("map.txt", "r");
	if (file == NULL) {
		exit(-2);
	}
	while (checker == 1) {
		FILE* file = fopen("map.txt", "r");
		con_gotoXY(0, 0);
		puts("A* PATHFINDING by MANSASHA\n");
		puts("THIS APP IS A SIMPLE EMULATION OF NAVIGATOR IN CAR");
		puts("USE WASD FOR MOVING AND Q FOR QUIT");
		puts("RANDOM MAP OR USER MAP (1 OR 2)");
		ans = right_input(ans, text, 1);
		puts("YOU SHOULD ENTER START AND FINISH POINTS IN FORM (X,Y)");
		puts("0<X<199 0<Y<44 \n");
		puts("ENTER start x y : ");
		points[0] = right_input(points[0], text, 2);
		points[1] = right_input(points[1], text, 3);
		puts("ENTER finish x y : ");
		points[2] = right_input(points[2], text, 2);
		points[3] = right_input(points[3], text, 3);
		if (ans == 1) {
			random_draw();
			ans = 0;
		}
		else {
			user_draw(file);
			ans = 0;
		}
		if (test(points) == 0) { 
			painter(2, 0, 48, ' ');
			con_gotoXY(100, 48);
			puts("WAY DOESN`T EXIST"); 
		}
		else {
			painter(2, 0, 48, ' ');
			con_gotoXY(100, 48);
			puts("GOT IT!");
		}
		con_gotoXY(100, 49);
		puts("NEW MAP OR QUIT?(1 OR 2)");
		con_gotoXY(100, 50);
		ans = right_input(ans, text, 1);
		if (ans == 2) {
			checker = 0;
		}
		con_clearScr();
		ans = 0;
		fclose(file);
	}
	
}


int main(void) {
	srand(time(NULL));
	con_hideCursor();
	init_colors();
	game_field();
	UI();
}