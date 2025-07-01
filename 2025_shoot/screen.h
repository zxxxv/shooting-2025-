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

int start_screen();			// 화면 초기화
int render_screen();		// 키 입력시 사용
//int show_screen_whole();	// 스크린 전체 출력
//void clear_buffer();
