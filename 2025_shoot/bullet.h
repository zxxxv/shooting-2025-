#pragma once
#include <windows.h>
#include <time.h>
#include "constant.h"
#include "input.h"

typedef struct Bullet {
	int x, y;
	char shape;		// '+'
} Bullet;

int update_bullets(enum BULLET_LEV level);		// 총알 한칸 올라가기 → y좌표-- → 화면 밖으로 나간 총알 제거
void draw_bullets();		// 버퍼에 모든 총알 찍기
void hit_bullets();
int get_bullet_count();
enum BULLET_LEV set_bullet_lev();

extern DWORD last_spawn_ms;
extern DWORD last_move_ms;
extern Bullet bullets[YSIZE];
