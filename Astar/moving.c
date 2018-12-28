#include "moving.h"
#include "AStar.h"
void moving(car_t* car,int dx,int dy) {
	if (field[car->x + dx][car->y + dy].obj == 0|| field[car->x + dx][car->y + dy].obj == 666) {
		painter(-1, car->x, car->y, FIELD);
		painter(car->color, car->x + dx, car->y + dy, car->texture);
		car->x += dx;
		car->y += dy;
	}
}
int control(car_t* player) {
	switch (con_getKey())
	{
	case 'w':
		moving(player, 0, -1);
		break;
	case 's':
		moving(player, 0, 1);
		break;
	case 'd':
		moving(player, 1, 0);
		break;
	case 'a':
		moving(player, -1, 0);
		break;
	case 'q':
		return -1;
		
	default:
		return 0;
		break;
	}
}
int test(int*points) {
	car_t player;
	player.color = 8;
	player.x = points[0];
	player.y = points[1];
	if (player.x == points[2] && player.y == points[3]) {
		return 1;
	}
	player.texture = 'O';
	path_t* path=malloc(sizeof(path_t));
	if (path == NULL) {
		exit(-1);
	}
	if (astar(path, points) == 0) {
		free(path);
		return 0;
	};
	painter(player.color, player.x, player.y,player.texture);
	for (int i = 0;; i++) {
		if (control(&player) == -1) {
			free(path->path);
			free(path);
			exit(0);
		}
		if (findinpath(player.x, player.y, path) != 1) {
			points[0] = player.x;
			points[1] = player.y;
			clearoldpath(path);
			clearmap();
			astar(path, points);
		}
		if (player.x == points[2] && player.y == points[3]) {
			free(path->path);
			free(path);
			return 1;
		}
	}
}