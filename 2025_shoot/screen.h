#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "fighter.h"
#include "bullet.h"
#include "score.h"
#include "constant.h"
#include "skill.h"

extern char screen[YSIZE][XSIZE];

int start_screen();			// ȭ�� �ʱ�ȭ
int render_screen();		// Ű �Է½� ���
