#pragma once
#include <stdio.h>
#include <conio.h>
#include <signal.h>
#include "fighter.h"
#include "screen.h"
#include "skill.h"

int handle_input();		// ����Ű, ����, �����
int handle_quit();
void skill();			// ��ų �ߵ�
int pause();			// pause ��ư
int resume();			// resume ��ư
void quit_game();
void init_game();
int (*input[])();

extern int game_over;
extern int quit;
