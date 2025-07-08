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

int update_bullets(enum BULLET_LEV level);		// �Ѿ� ��ĭ �ö󰡱�, y��ǥ--, ȭ�� ������ ���� �Ѿ� ����
void draw_bullets();		                    // ���ۿ� ��� �Ѿ� ���
int get_bullet_count();
enum BULLET_LEV set_bullet_lev(int score);		// �ӵ� ����
char* get_bullet_lev();
void init_bullet();								// �Ѿ� �ʱ�ȭ
unsigned long get_time_ms();					//
