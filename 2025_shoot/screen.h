#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fighter.h"
#include "bullet.h"
#include "score.h"
#include "constant.h"
#include "skill.h"
#include <windows.h>

extern char screen[YSIZE][XSIZE];

int init();
int end();
int start_screen();			// ȭ�� �ʱ�ȭ
int render_screen();		// Ű �Է½� ���
void hide_console_cursor(); // Ŀ�� �����
void show_console_cursor(); // Ŀ�� ���̱�
void (*show_screen[])();