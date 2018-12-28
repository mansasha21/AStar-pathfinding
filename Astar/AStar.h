#pragma once
#include "DFC.h"
#define FINISH 666
#define BAD_WAY 999
#define DELAY  1999999
typedef struct {
	int size;
	int realsize;
	int current;
	int* x;
	int* y;
} wave_t;

void pushback(wave_t* wave, int x, int y);
int astar(path_t*  path, int* points);
void createwave(wave_t *wave);
void delete_from_wave(wave_t * wave, int i);
int findinpath(int x, int y, path_t* path);
void clearoldpath(path_t *path);