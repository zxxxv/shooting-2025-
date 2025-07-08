#pragma once
//#include <windows.h>
#include <time.h>
#include "constant.h"
#include "input.h"

typedef struct Bullet {
	int x, y;
	char shape;		// '+'
} Bullet;

extern Bullet bullets[YSIZE];

void draw_bullets();							// 버퍼에 모든 총알 찍기
int get_bullet_count();
char* get_bullet_speed();
char* get_bullet_level();
void init_bullet();								// 총알 초기화
unsigned long get_time_ms();					//
