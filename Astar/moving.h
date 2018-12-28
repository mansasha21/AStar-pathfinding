#pragma once
typedef struct{
	int x;
	int y;
	char texture;
	int color;
}car_t;
int control(car_t* player);
int test(int*points);