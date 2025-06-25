#pragma once
#include "screen.h"
#include <time.h>
//#include <stdbool.h>
#include "input.h"

typedef struct Bullet {
	int x, y;
	char shape;		// '+'
} Bullet;

int update_bullets();		// �Ѿ� ��ĭ �ö󰡱� �� y��ǥ-- �� ȭ�� ������ ���� �Ѿ� ����
void draw_bullets();		// ���ۿ� ��� �Ѿ� ���

extern DWORD last_spawn_ms;
extern DWORD last_move_ms;
