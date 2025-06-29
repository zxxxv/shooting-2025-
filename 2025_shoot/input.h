#pragma once
#include <stdio.h>
#include <conio.h>
#include <signal.h>
#include "fighter.h"

int handle_input();		// 방향키, 종료, 재시작
void skill();			// 스킬 발동
int pause();			// pause 버튼
int resume();			// resume 버튼

extern int game_over;
