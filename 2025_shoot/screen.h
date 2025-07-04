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

int init();
int end();
int start_screen();			// 화면 초기화
int render_screen();		// 키 입력시 사용
void hideConsoleCursor();	// 커서 지우기
void showConsoleCursor();	// 커서 보이기
void (*show_screen[])();