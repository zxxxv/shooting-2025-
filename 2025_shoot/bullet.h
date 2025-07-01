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
void draw_bullets();		                    // ���ۿ� ��� �Ѿ� ���
int get_bullet_count();
enum BULLET_LEV set_bullet_lev(int score);
char* get_bullet_lev();
void init_bullet();
void init_bullet_lev();

extern Bullet bullets[YSIZE];
