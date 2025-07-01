#pragma once
#include <stdio.h>
#include <conio.h>
#include <signal.h>
#include "fighter.h"
#include "screen.h"
#include "skill.h"

int handle_input();		// 방향키, 종료, 재시작
int handle_quit();
void skill();			// 스킬 발동
int pause();			// pause 버튼
int resume();			// resume 버튼
void quit_game();
void init_game();
int (*input[])();

extern int game_over;
extern int quit;
