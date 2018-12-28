#include "AStar.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void pushback(wave_t *wave, int x, int y) {
	wave->realsize++;
	if (wave->current>=wave->size) {
		wave->x = realloc(wave->x,wave->size * 2 * sizeof(int));
		if (wave->x == NULL) {
			exit(-1);
		}
		wave->y = realloc(wave->y, wave->size * 2 * sizeof(int));
		if (wave->y == NULL) {
			exit(-1);
		}
		wave->size *= 2;
	}
	wave->x[wave->current] = x;
	wave->y[wave->current] = y;
	wave->current++;
}
void createwave(wave_t *wave) {
	wave->size = 10;
	wave->realsize = 0;
	wave->current = 0;
	wave->x = malloc(10*sizeof(int));
	if (wave->x == NULL) {
		exit(-1);
	}
	wave->y = malloc(10*sizeof(int)) ;
	if (wave->y == NULL) {
		exit(-1);
	}
}
int find_min_h(wave_t *open) {
	int min = 0;
	for (int i = 0; i < open->current; i++) {
		if (open->x[i] == BAD_WAY) {
			if (i == min) {
				min++;
			}
			continue;
		}
		if (field[open->x[min]][open->y[min]].h - field[open->x[i]][open->y[i]].h >= 0) {
			min = i;
		}
	}
	return min;
}
int hfunc(int x1, int y1,int fx,int fy) {
	field[x1][y1].h = pow(pow(x1 - fx, 2) + pow(y1 - fy, 2), 0.5);
}
void delete_from_wave(wave_t * wave, int i) {
	wave->x[i] = BAD_WAY;
	wave->y[i] = BAD_WAY;
	wave->realsize--;
}
int findinpath(int x, int y, path_t* path) {
	for (int i = 0; i < path->size; i += 2) {
		if (x == path->path[i] && y == path->path[i + 1]) {
			return 1;
		}
	}
	return 0;

}
void clearoldpath(path_t *path) {
	for (int i = 0; i < path->size; i += 2) {
		field[path->path[i]][path->path[i + 1]].colored = 0;
		field[path->path[i]][path->path[i + 1]].open = 0;
		field[path->path[i]][path->path[i + 1]].stepcounter = 99999;
		painter(-1, path->path[i], path->path[i + 1], ' ');
	}
	path->size = 0;
}
void clearwave(wave_t* wave) {
	for (int i = 0; i < wave->realsize; i++) {
		if (wave->x[i] != 999) {
			field[wave->x[i]][wave->y[i]].open = 0;
			field[wave->x[i]][wave->y[i]].colored = 0;
			field[wave->x[i]][wave->y[i]].stepcounter = 99999;
		}
	}
	free(wave->x);
	free(wave->y);
}
int astar(path_t *path,int* points) {
	int step = 0;
	int closed = -1;
	int current = 0;
	int path_exist = 0;
	field[points[0]][points[1]].stepcounter = step;
	field[points[0]][points[1]].open = 1;
	field[points[2]][points[3]].obj = 666;
	painter(7, points[0], points[1], field[points[0]][points[1]].char_field);
	painter(7, points[2], points[3], field[points[2]][points[3]].char_field);
	int dx[] = { 1,0,-1,0 };
	int dy[] = { 0,1,0,-1 };
	wave_t openwave, closedwave;
	createwave(&openwave);
	createwave(&closedwave);
	pushback(&openwave, points[0], points[1]);
	hfunc(points[0], points[1],points[2],points[3]);
	while (openwave.realsize > 0) {
		current = find_min_h(&openwave);
		pushback(&closedwave, openwave.x[current], openwave.y[current]);
		delete_from_wave(&openwave, current);
		closed++;
		//for (int i = 0; i < DELAY; i++);
		//painter(5, closedwave.x[closed], closedwave.y[closed], field[closedwave.x[closed]][closedwave.y[closed]].char_field);
		step = field[closedwave.x[closed]][closedwave.y[closed]].stepcounter + 1;
		field[closedwave.x[closed]][closedwave.y[closed]].colored = 1;
		for (int j = 0; j < 4; j++) {
			int nx = closedwave.x[closed] + dx[j];
			int ny = closedwave.y[closed] + dy[j];

			if (field[nx][ny].open==0 && (field[nx][ny].obj == 0 || field[nx][ny].obj == 666)) {
				hfunc(nx, ny, points[2], points[3]);
				pushback(&openwave, nx, ny);
				field[nx][ny].open = 1;
				field[nx][ny].stepcounter = step;
				if (field[nx][ny].obj == FINISH) {
					path_exist = 1;
					goto END;

				}
			}
			else {
				continue;
			}

		}
	}

END:;
	if (path_exist == 0) {
		return 0;
	}
	int current_x = points[2];
	int current_y = points[3];
	int i = 2;
	int nx = current_x;
	int ny = current_y;
	path_t path_current;
	path_current.allocsize = 100;
	path_current.size = 2;
	path_current.path = malloc(sizeof(int) * 100);
	if (path_current.path == NULL) {
		exit(-1);
	}
	path_current.path[i-2] = nx;
	path_current.path[i -1] = ny;

	while (step != 0&&path_exist == 1 && (current_x != points[0] || current_y != points[1])) {
		for (int g = 0; g < 4; g++) {
			 nx = current_x + dx[g];
			 ny = current_y + dy[g];
			if (field[nx][ny].stepcounter == (step - 1) && field[nx][ny].colored==1) {
				if (path_current.size >= path_current.allocsize - 2) {
					path_current.path = realloc(path_current.path, (path_current.allocsize + 100)*sizeof(int));
					if (path_current.path == NULL) {
						exit(-1);
					}
					path_current.allocsize += 100;
				}
				path_current.path[i] = nx;
				path_current.path[i + 1] = ny;
				path_current.size += 2;
				if(step!=1)
					//for (int i = 0; i < DELAY; i++);
				painter(6, nx, ny, field[nx][ny].char_field);
				current_x = nx;
				current_y = ny;
				step--;
				i+=2;
				break;
				
			}
		}
		
	}
	path->allocsize = path_current.size;
	path->size = path_current.size;
	path->path = malloc(sizeof(int)*path->size);
	if (path->path == NULL) {
		exit(-1);
	}
	memcpy(path->path, path_current.path, path_current.size * sizeof(int));
	free(path_current.path);
	clearwave(&openwave);
	clearwave(&closedwave);
	painter(7, points[0], points[1], field[points[0]][points[1]].char_field);
	painter(7, points[2], points[3], field[points[2]][points[3]].char_field);
	return 1;
}