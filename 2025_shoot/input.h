#pragma once
#include <stdio.h>
#include <conio.h>
#include <signal.h>
#include "fighter.h"
#include "screen.h"
#include "skill.h"

extern int game_over;
extern int quit;

void quit_game();
void init_game();
int (*input[])();
//int handle_input();		// 방향키, 종료, 재시작
//int handle_quit();
//void key_skill();			// 스킬 발동