#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "fighter.h"
#include "bullet.h"
#include "score.h"
#include "constant.h"

extern char screen[YSIZE][XSIZE];

static void clear_buffer();	// ȭ�� ���� �ʱ�ȭ
int show_screen_whole();	// ��ũ�� ��ü ���
int start_screen();			// ȭ�� �ʱ�ȭ
int render_screen();		// Ű �Է½� ���