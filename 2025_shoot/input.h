#pragma once
#include <stdio.h>
#include <conio.h>
#include <signal.h>
#include "fighter.h"
#include "screen.h"
#include "skill.h"

extern int game_over;
extern int quit;
extern int game_clear;

void quit_game();
void init_game();
int (*input[])();
