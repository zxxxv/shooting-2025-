#pragma once
#include <windows.h>
#include <time.h>
#include "constant.h"
#include "input.h"

typedef struct Bullet {
	int x, y;
	char shape;		// '+'
} Bullet;

int update_bullets(enum BULLET_LEV level);		// �Ѿ� ��ĭ �ö󰡱� �� y��ǥ-- �� ȭ�� ������ ���� �Ѿ� ����
void draw_bullets();		// ���ۿ� ��� �Ѿ� ���
void hit_bullets();
int get_bullet_count();
enum BULLET_LEV set_bullet_lev();

extern DWORD last_spawn_ms;
extern DWORD last_move_ms;
extern Bullet bullets[YSIZE];
