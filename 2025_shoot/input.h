#pragma once
#include <stdio.h>
#include <conio.h>
#include <signal.h>
#include "fighter.h"

int handle_input();		// ����Ű, ����, �����
void skill();			// ��ų �ߵ�
int pause();			// pause ��ư
int resume();			// resume ��ư

extern int game_over;
