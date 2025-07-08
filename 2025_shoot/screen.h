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
int start_screen();			// 화면 초기화
int render_screen();		// 키 입력시 사용
void hide_console_cursor(); // 커서 지우기
void show_console_cursor(); // 커서 보이기
void (*show_screen[])();